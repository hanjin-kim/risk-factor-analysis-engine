#include <riskfactor/instruments/linear_instrument.hpp>
#include <riskfactor/managers/covariance_manager.hpp>

namespace fre
{
	namespace riskfactor
	{
		LinearInstrument::LinearInstrument(const Name& name, const Desc& desc)
			: Named(name, desc), exposure(0) //, covariance_matrix(Matrix::Zero(1,1)), basis(Vector::Zero(1))
		{}

		LinearInstrument::~LinearInstrument()
		{}

		void LinearInstrument::SetClosingPrice(const Date& d, const Price& p)
		{
			closing_date = d;
			closing_price = p;
		}

		void LinearInstrument::PrintFactorList()
		{
			PrintFactorList(LOG(INFO));
		}

		void LinearInstrument::PrintFactorList(::el::base::Writer& os)
		{
			Size count = 0;
			for (auto factor : factor_list)
			{
				RiskFactor::Ptr ptr = factor.first;
				tuple_type& tuple = factor.second;

				os << "[" << count << "]" << " " << ptr->GetName();
				os << ", (" << ptr->begin()->first << " - " << ptr->rbegin()->first << ")";

				if (std::get<0>(tuple))
					os << ", ACTIVATED";
				else
					os << ", INACTIVATED";

				os << ", W = " << std::get<1>(tuple);
				os << ", Delta = " << std::get<2>(tuple) << "\n";

				++count;
			}

//			os << "-- Sum of weights = " << SumOfWeights() << "\n";
		}

		std::list<Option> LinearInstrument::TokenizeOptionString(const Option& s)
		{
			String tmps = s;
			const String delimiter = ";";

			Size pos = 0;
			String token;
			std::list<String> token_list;

			while (1) {
				pos = tmps.find(delimiter);
				token = tmps.substr(0, pos);
				token_list.push_back(token);
				tmps.erase(0, pos + delimiter.length());
				if (pos == String::npos) break;
			}

			return token_list;
		}

		std::map<Option, double> LinearInstrument::GetMappedOptionList(const Option& ss)
		{
			String tmps = ss;
			std::map<String, double> map;

			for (auto s : TokenizeOptionString(tmps))
			{
				Size pos = s.find("=");
				if (pos != String::npos)
				{
					String key = s.substr(0, pos);
					s.erase(0, pos + 1);
					Double val = s.size() > 0 ? std::stod(s) : 1;
					map.insert(std::make_pair(key, val));
				}
				else
				{
					String key = s.substr(0, pos);
					s.erase(0, pos + 1);
					map.insert(std::make_pair(key, 1));
				}
			}

			return map;
		}

		void LinearInstrument::RegisterRiskFactor(const RiskFactor::Ptr factor, const Delta& delta, const Weight& w)
		{
			factor_list.insert(std::make_pair(factor, std::make_tuple(true, w, delta)));
		}

		void LinearInstrument::RemoveRiskFactor(const RiskFactor::Ptr f)
		{
			auto it = factor_list.find(f);

			if (it != factor_list.end())
			{
				factor_list.erase(it);
			}
		}

		void LinearInstrument::SetMask(const RiskFactor::Ptr f, const bool mask)
		{

			auto it = factor_list.find(f);

			if (it != factor_list.end())
				std::get<0>(it->second) = mask;
		}

		void LinearInstrument::SetWeight(const RiskFactor::Ptr f, const Weight& weight)
		{
			auto it = factor_list.find(f);

			if (it != factor_list.end())
				std::get<1>(it->second) = weight;
		}

		void LinearInstrument::SetDelta(const RiskFactor::Ptr f, const Delta& delta)
		{
			auto it = factor_list.find(f);

			if (it != factor_list.end())
				std::get<2>(it->second) = delta;
		}

		Mask LinearInstrument::GetMask(const RiskFactor::Ptr f) const
		{
			auto it = factor_list.find(f);

			if (it != factor_list.end())
				return std::get<0>(it->second);

			return Mask();
		}

		Weight LinearInstrument::GetWeight(const RiskFactor::Ptr f) const
		{
			auto it = factor_list.find(f);

			if (it != factor_list.end())
				return std::get<1>(it->second);

			return Weight();
		}

		Delta LinearInstrument::GetDelta(const RiskFactor::Ptr f) const
		{
			auto it = factor_list.find(f);

			if (it != factor_list.end())
				return std::get<2>(it->second);

			return Delta();
		}

		Size LinearInstrument::MaskedSize()
		{
			Size n = 0;
			for (auto factor : factor_list)
			{
				tuple_type& tuple = factor.second;
				if (std::get<0>(tuple))
					n++;
			}

			return n;
		}

		Matrix LinearInstrument::EvaluateCovarianceMatrix(Size size, const Option& opt)
		{
			// Default arguments
			Size ndays = 250;
			AverageType average_type = AverageType::EWMA;
			Lambda lambda = 0.94;
			Bool undiversified = false;

			// Option interpretation
			for (auto arg : GetMappedOptionList(opt))
			{
				String s = arg.first;
				if (s == "NDAYS")
				{
					ndays = (Size)arg.second;
				}
				if (s == "SMA")
				{
					VLOG(1) << "SMA option is on. But EWMA is recommanded.." << std::endl;
					average_type = AverageType::SMA;
				}

				if (s == "LAMBDA")
				{
					lambda = arg.second;
				}
				if (s == "UNDIV")
				{
					VLOG(1) << "Undiversified Exposure will be evaluated." << std::endl;
					undiversified = true;
				}
			}
			
			LOG(DEBUG) << size << "x" << size << " 상관계수 행렬 생성" << std::endl;

			Matrix covariance_matrix(size, size);

			CovarianceManager& mgr = CovarianceManager::GetInstance();

			// diagonal first
			unsigned int row = 0;
			for (auto it = factor_list.begin(); it != factor_list.end(); it++)
			{
				if (!std::get<0>(it->second)) // unmasked
					continue;

				Covariance::Ptr cov = mgr.GetCovariance(it->first, it->first, average_type);
				Data cov_val = cov->Evaluate(closing_date, ndays, { Argument("LAMBDA", lambda) });

				covariance_matrix(row, row) = cov_val;
				++row;
			}


			row = 0;
			for (auto it = factor_list.begin(); it != factor_list.end(); it++)
			{
				if (!std::get<0>(it->second)) // unmasked
					continue;

				unsigned int column = row + 1;
				for (auto jt = std::next(it); jt != factor_list.end(); jt++)
				{
					if (!std::get<0>(jt->second)) // unmasked
						continue;

					Data cov_val;
					if (undiversified)
					{
						cov_val = sqrt(covariance_matrix(row, row) * covariance_matrix(column, column));

						covariance_matrix(row, column) = cov_val;
						covariance_matrix(column, row) = cov_val;
					}
					else
					{
						Covariance::Ptr cov = mgr.GetCovariance(it->first, jt->first, average_type);
						cov_val = cov->Evaluate(closing_date, ndays, { Argument("LAMBDA", lambda) });

						covariance_matrix(row, column) = cov_val;
						covariance_matrix(column, row) = cov_val;
					}

					LOG(DEBUG) << "공분산 객체(" << it->first->GetName() << ", " << jt->first->GetName() << ")가 로드 되었습니다" << std::endl;
					LOG(DEBUG) << "마지막 참조 날짜 : " << closing_date << std::endl;
					LOG(DEBUG) << row << "행 " << column << "열 공분산 : " << cov_val << std::endl;

					column++;
				}
				row++;
			}

			LOG(DEBUG) << "Covariance matrix generated : " << std::endl
						<< covariance_matrix << std::endl;

			ptr_covariance_matrix = std::make_shared<Matrix>(covariance_matrix);

			return covariance_matrix;
		}

		Exposure LinearInstrument::DefaultEvaluateExposure(const Option& opt)
		{
			Size size = MaskedSize();
		
			if (size == 0) return 0;

			LOG(DEBUG) << size << " masked RiskFactors.." << GetName() << std::endl;
			
			Vector basis(size);


			//if (weight_vector) delete weight_vector;
			//if (delta_vector) delete delta_vector;

			Matrix& covariance_matrix = EvaluateCovarianceMatrix(size, opt);
			
			LOG(DEBUG) << basis.size() << "  basis.." << GetName() << std::endl;
			LOG(DEBUG) << covariance_matrix.size() << " cov.." << GetName() << std::endl;

			Size row = 0;
			for (auto factor : factor_list)
			{
				tuple_type& tuple = factor.second;

				if (!std::get<0>(tuple)) continue;
				
				Weight weight = std::get<1>(tuple);
				Delta delta = std::get<2>(tuple);

				basis(row) = weight * delta;

				++row;
			}

			ptr_basis = std::make_shared<Vector>(basis);

			LOG(DEBUG) << "basis vector generated : " << std::endl;
			LOG(DEBUG) << basis << std::endl;

			LOG(DEBUG) << "Diagonal of the covariance matrix : " << std::endl
				<< covariance_matrix.diagonal() << std::endl;

			Matrix UtT = basis.transpose() * covariance_matrix;

			Matrix UtTU = UtT * basis;

			Exposure ret = sqrt(UtTU(0));

			if (abs(ret) < 1.E-15) ret = 0;

			LOG(DEBUG) << "Exposure = " << ret << std::endl;

			return ret;
		}

	}	
}