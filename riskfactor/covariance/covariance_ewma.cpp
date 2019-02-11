#include <math.h>
#include <cstdarg>

#include <riskfactor/covariance/covariance_ewma.hpp>
#include <riskfactor/easylogging++/easylogging++.h>

namespace fre
{
	namespace riskfactor
	{
		CovarianceEWMA::CovarianceEWMA(RiskFactor::Ptr f1, RiskFactor::Ptr f2)
			: Covariance(f1, f2)
		{}

		Data CovarianceEWMA::Evaluate(const Date& ref_date, const Size& ndays, const ArgList args)
		{
			// default lambda is 0.94
			double lambda = 0.94;

			// Lambda 파라미터 찾기
			for (const Argument& arg : args)
			{
				if (arg.GetKey() == "LAMBDA")
				{
					Data lambda = arg.GetValue();
					Data nancheck = 1. / (1. - lambda);
					if (isnan(nancheck) || isinf(nancheck))
					{
						LOG(ERROR) << "LAMBDA provided is too close or equal to 1. It will be set with 0.999 instead" << std::endl;
						lambda = 0.999;
						break;
					}

				}
			}

			/*
			cache_type::key_type key(lambda, ref_date, ndays);

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
				LOG(ERROR) << "No data exists on the reference date, " << ref_date << ", "
					<< "In " << reference[0]->GetName() << ". "
					<< "Evaluation Failed. Null results will be returned." << std::endl;
				return Data();
			}

			if (it1 == reference[1]->end())
			{
				LOG(ERROR) << "No data exists on the reference date, " << ref_date << ", "
					<< "In " << reference[1]->GetName() << ". "
					<< "Evaluation Failed. Null results will be returned." << std::endl;
				return Data();
			}


			double sqsum = 0;
			Size n_sample = 1;
			while (1)
			{
				double weight = ::pow(lambda, n_sample -1);
				sqsum += weight * (it0->second) * (it1->second);
				
				if (n_sample == ndays || it0 == reference[0]->begin() || it1 == reference[1]->begin())
					break;

				++n_sample;
				--it0; --it1; 
			}

			double common_factor = (1 - lambda) / (1 - ::pow(lambda, n_sample));

			Data cov_ewma(sqsum*common_factor);

			LOG(DEBUG) << "Cov_ewma on for the day after " << ref_date << " = " << cov_ewma << std::endl;

			return cov_ewma;
		}
	}
}