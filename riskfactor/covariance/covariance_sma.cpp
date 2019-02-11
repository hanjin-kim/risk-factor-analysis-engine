#include <riskfactor/covariance/covariance_sma.hpp>
#include <riskfactor/easylogging++/easylogging++.h>

namespace fre
{
	namespace riskfactor
	{
		CovarianceSMA::CovarianceSMA(RiskFactor::Ptr f1, RiskFactor::Ptr f2)
			: Covariance(f1, f2)
		{}

		Data CovarianceSMA::Evaluate(const Date& ref_date, const Size& ndays, const ArgList)
		{
			/*
			cache_type::key_type key(ref_date, ndays);

			// 캐시 뒤지기
			auto it_cache = cache.find(key);

			if (it_cache != cache.end())
				return it_cache->second;
			*/

			// 새로 계산하기
			// 인풋 체크
			if (!GetCalendar()->isBusinessDay(ref_date))
			{
				LOG(ERROR) << "Reference Date, " << ref_date << ", is not a business day."
					<< "Evaluation Failed. Null results will be returned." << std::endl;
				return Data();
			}

			auto it0 = reference[0]->find(ref_date);
			auto it1 = reference[1]->find(ref_date);

			if (it0 == reference[0]->end())
			{
				LOG(ERROR) << reference[0]->GetName() << " >> No data exists on the reference date, " << ref_date << ", "
					<< "In the dataset0. "
					<< "Evaluation Failed. Null results will be returned." << std::endl;
				return Data();
			}

			if (it1 == reference[1]->end())
			{
				LOG(ERROR) << reference[1]->GetName() << " >> No data exists on the reference date, " << ref_date << ", "
					<< "In the dataset1. "
					<< "Evaluation Failed. Null results will be returned." << std::endl;
				return Data();
			}


			double sqsum = 0;
			Size n_sample = 1;
			while (1)
			{
				sqsum += (it0->second) * (it1->second);

				if (n_sample == ndays || it0 == reference[0]->begin() || it1 == reference[1]->begin())
					break;

				n_sample++;
				--it0; --it1;
			}

			Data cov_sma(sqsum / n_sample);
			//cache.insert(std::make_pair(key, cov_sma));

			LOG(DEBUG) << "Cov_sma for the day after " << ref_date << " = " << cov_sma << std::endl;

			return cov_sma;
		}
	}
}