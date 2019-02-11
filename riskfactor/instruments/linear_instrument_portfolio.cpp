#include <numeric>

#include <riskfactor/instruments/linear_instrument_portfolio.hpp>
#include <riskfactor/easylogging++/easylogging++.h>

namespace fre
{
	namespace riskfactor
	{
		LinearInstrumentPortfolio::LinearInstrumentPortfolio(const Name& name, const Desc& desc)
			: LinearInstrument(name, desc)
		{}

		LinearInstrumentPortfolio::~LinearInstrumentPortfolio()
		{
			//if(entry_weight_vector) delete entry_weight_vector;
		}

		int LinearInstrumentPortfolio::AddInstrument(const LinearInstrument::Ptr inst, const Weight& weight, const Mask& mask)
		{
			
			if (entry_list.empty())
			{
				if (closing_date == Date())
				{
					auto pair = inst->GetClosingPrice();
					closing_date = pair.first;
				}
			}

			if (!entry_list.empty())
			{
				
				if (inst->GetClosingPrice().first != closing_date)
				{
					LOG(ERROR) << "Reference date of the closing price is not coincide. Addition aborted." << std::endl;
					return 0;
				}
			}
			

			int ret = 1;
			auto it = entry_list.find(inst);

			if (it == entry_list.end())
			{
				entry_list.insert(std::make_pair(inst, std::make_pair(mask, weight)));
			}
			else
			{
				entry_list[inst] = std::make_pair(mask, weight);
				ret = 2;
			}
			
			return ret;
		}

		void LinearInstrumentPortfolio::RemoveInstrument(const LinearInstrument::Ptr inst)
		{
			auto it = entry_list.find(inst);

			if (it != entry_list.end())
			{
				entry_list.erase(it);
			}

		}

		void LinearInstrumentPortfolio::SetMask(const LinearInstrument::Ptr inst, const Mask& mask)
		{
			auto it = entry_list.find(inst);

			if (it != entry_list.end())
			{
				(it->second).first = mask;

				return;
			}

			LOG(ERROR) << "상품(" << inst->GetName() << ")이 포트폴리오에 없습니다." << std::endl;
		}

		void LinearInstrumentPortfolio::SetWeight(const LinearInstrument::Ptr inst, const Weight& weight)
		{
			auto it = entry_list.find(inst);

			if (it != entry_list.end())
			{
				(it->second).second = weight;

				return;
			}

			LOG(ERROR) << "상품(" << inst->GetName() << ")이 포트폴리오에 없습니다." << std::endl;

		}

		/*
		Vector LinearInstrumentPortfolio::EvaluateEntryWeights()
		{
			//if (!entry_weight_vector) delete entry_weight_vector;

			Size size = 0;			
			Price sum_of_capital = std::accumulate(entry_list.begin(), entry_list.end(), Data(0.),
				[&size](Data a, entry_map_type::value_type b) 
			{
				if (!b.second.first) return a;

				Price entry_price = abs(b.first->GetClosingPrice().second);
				Price entry_capital = b.second.second*entry_price;
				a += entry_capital;
				size++;
				LOG(DEBUG) << "종목(" << b.first->GetName() << ") 총액 : " << entry_capital << std::endl;

				return a;
			});

			closing_price = sum_of_capital;

			LOG(DEBUG) << "총 자산 금액 : " << sum_of_capital << std::endl;

			LOG(DEBUG) << size << " instruments.." << std::endl;

			if (size == 0) return Vector::Zero(0);

			Vector entry_weight_vector = Vector::Zero(size);

			Size n = 0;
			for (auto entry : entry_list)
			{
				if (!entry.second.first) continue;
				
				Price entry_price = entry.first->GetClosingPrice().second;
				Price entry_capital = entry.second.second*entry_price;
				Weight weight = entry_capital / sum_of_capital;
				entry_weight_vector(n) = weight;
				LOG(DEBUG) << entry.first->GetName() << " / price = " << entry_price << " / amount = " << entry.second.second
						<< " / weight = " << weight << std::endl;
				++n;
			}


			LOG(DEBUG) << "Instrument weight vector evaluated : " << std::endl
				<< entry_weight_vector << std::endl;

			return entry_weight_vector;
		}
		*/

		void LinearInstrumentPortfolio::EvaluateRiskFactorWeights()
		{
			// factor map initialization
			factor_list.swap(map_type());

			Size n = 0;
			for (auto entry : entry_list)
			{
				LinearInstrument::Ptr entry_ptr = entry.first;
				pair_type pair = entry.second;
				Weight entry_weight = pair.second;
				
				if (!pair.first) continue;

				for (auto factor : entry_ptr->GetFactorList())
				{
					RiskFactor::Ptr factor_ptr = factor.first;

					tuple_type factor_tuple = factor.second;

					if (!std::get<0>(factor_tuple)) continue;

					Weight weight = std::get<1>(factor_tuple);
					Delta delta = std::get<2>(factor_tuple);

					//Weight entry_delta = delta*weight;

					if (this->factor_list.find(factor_ptr) == this->factor_list.end())
					{
						factor_list[factor_ptr] = std::make_tuple(true, entry_weight*weight, delta);
					}
					else
					{
						std::get<1>(factor_list[factor_ptr]) += entry_weight*weight;
					}
				}
				++n;
			}

		}

		Exposure LinearInstrumentPortfolio::EvaluateExposure(const String& opt) 
		{
			EvaluateRiskFactorWeights();
			exposure = DefaultEvaluateExposure(opt);

			return exposure;
		}

		Exposure LinearInstrumentPortfolio::EvaluateContributionalExposure(const LinearInstrument::Ptr entry)
		{
			
			std::vector<int> rows; 
			for (auto factor : entry->GetFactorList())
			{
				Size row = 0;
				for (auto port_factor : factor_list)
				{
					if (port_factor.first == factor.first)
					{
						rows.push_back(row);
						break;
					}
					row++;
				}
			}

			// contributional exposure
			// Exp_i = w_i * sum{j}( w_j * cov_ij )
			Exposure sum = 0;
			for(auto row : rows)
			{
				Vector row_vector = ptr_covariance_matrix->row(row) * (*ptr_basis)(row);
				double d = row_vector.dot((*ptr_basis));

				sum += d;

			}

			//std::cout << exposure << " / " << sum << std::endl;

			return sum / exposure;
		}

		Exposure LinearInstrumentPortfolio::EvaluateIncrementalExposure(const LinearInstrument::Ptr entry)
		{
			Exposure sum = 0;
			for (auto factor : entry->GetFactorList())
			{
				Size i = 0;
				for (auto port_factor : factor_list)
				{
					if (port_factor.first == factor.first)
					{
						Weight w_i = (*ptr_basis)(i);

						// partial exposure
						// PartialExp_i = w_i * w_i + 2 * w_i * sum{j not i}( w_j * cov_ij )
						Exposure sum_i = 0;
						for (int j = 0; j < ptr_basis->size(); ++j)
						{
							Weight w_j = (*ptr_basis)(j);

							Exposure summon = w_i * w_j * ptr_covariance_matrix->col(i)(j);

							if (j == i) sum += summon;
							else sum += 2 * summon;
						}
						sum += sum_i;
					}
					i++;
				}
			}

			Exposure a = exposure*exposure - sum;

			if (abs(a) < 10E-20) a = 0;

			return exposure - sqrt(a);
		}
	}
}