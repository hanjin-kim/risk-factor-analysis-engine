#include <riskfactor/covariance_matrix.hpp>
#include <riskfactor/managers/covariance_manager.hpp>
#include <riskfactor/easylogging++/easylogging++.h>

namespace fre
{
	namespace riskfactor
	{
		CovarianceMatrix::CovarianceMatrix()
			: factor_list_updated(true)
		{}

		std::shared_ptr<Matrix> CovarianceMatrix::GetCovarianceMatrix(const Date& ref_date, const Option& opt)
		{
			// Default arguments
			Size ndays = 250;
			AverageType average_type = AverageType::EWMA;
			Lambda lambda = 0.94;

			// Option interpretation
			for (auto arg : GetMappedOptionList(opt))
			{
				String s = arg.first;
				if (s == "NDAYS")
					ndays = (Size)arg.second;
				if (s == "SMA")
					average_type = AverageType::SMA;
				if (s == "LAMBDA")
					lambda = arg.second;
			}

			QL_REQUIRE(ref_date != Date(),
				"Reference date should be given.");

			unsigned int size = MaskedSize();

			QL_REQUIRE(size > 0,
				"# of Masked Riskfactor is zero.");

			// 100% correlation assumed by default
			std::shared_ptr<Matrix> matrix(new Matrix(Matrix::Ones(size, size)));

			LOG(DEBUG) << size << "X" << size << " 상관계수 행렬 생성" << std::endl;

			CovarianceManager& mgr = CovarianceManager::GetInstance();

			unsigned int row = 0;
			for (auto it = factor_list.begin(); it != factor_list.end(); it++)
			{
				if (!it->second) // unmasked
					continue;

				unsigned int column = row;
				for (auto jt = it; jt != factor_list.end(); jt++)
				{
					if (!jt->second) // unmasked
						continue;

					Covariance::Ptr cov = mgr.GetCovariance(it->first, jt->first, average_type);
					Data cov_val = cov->Evaluate(ref_date, ndays, { Argument("LAMBDA", lambda) });

					LOG(DEBUG) << "공분산 객체(" << it->first->GetName() << ", " << jt->first->GetName() << ")가 로드 되었습니다" << std::endl;
					LOG(DEBUG) << "기준일 : " << ref_date << std::endl;
					LOG(DEBUG) << row << "행 " << column << "열 상관계수 : " << cov_val << std::endl;

					(*(matrix.get()))(row, column) = cov_val;
					if(row != column) (*(matrix.get()))(column, row) = cov_val;

					column++;
				}
				row++;
			}

			LOG(DEBUG) << "Covariance matrix generated : " << std::endl;
			LOG(DEBUG) << *(matrix.get()) << std::endl;

			return matrix;
		}

		void CovarianceMatrix::AddRiskFactor(const RiskFactor::Ptr factor, const Mask& mask)
		{
			if (factor_list.find(factor) == factor_list.end())
			{
				LOG(INFO) << factor->GetName() << " already exists." << std::endl;
				factor_list.insert(std::make_pair(factor, mask));
			}
		}

		void CovarianceMatrix::RemoveRiskFactor(const RiskFactor::Ptr factor)
		{
			factor_list.erase(factor);
		}

		void CovarianceMatrix::SetMask(const RiskFactor::Ptr factor, const Mask& mask)
		{
			auto it = factor_list.find(factor);
			if (it != factor_list.end())
			{
				it->second = mask;
			}
		}

		std::list<Option> CovarianceMatrix::TokenizeOptionString(const Option& s)
		{
			Option tmps = s;
			const Option delimiter = ";";

			Size pos = 0;
			Option token;
			std::list<Option> token_list;

			while ((pos = tmps.find(delimiter)) != Option::npos) {
				token = tmps.substr(0, pos);
				token_list.push_back(token);
				tmps.erase(0, pos + delimiter.length());
			}

			return token_list;
		}

		std::map<Option, Data> CovarianceMatrix::GetMappedOptionList(const Option& ss)
		{
			Option tmps = ss;
			std::map<Option, Data> map;

			for (auto s : TokenizeOptionString(tmps))
			{
				Size pos = s.find("=");
				Option key = s.substr(0, pos);
				s.erase(0, pos + 1);
				Double val = s.size() > 0 ? std::stod(s) : 1;
				map.insert(std::make_pair(key, val));
			}

			return map;
		}

		Size CovarianceMatrix::MaskedSize()
		{
			Size n = 0;
			for (auto pair : factor_list)
			{
				if (std::get<1>(pair))
					n++;
			}

			return n;
		}
	}
}