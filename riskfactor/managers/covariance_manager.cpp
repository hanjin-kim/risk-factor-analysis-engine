#include <riskfactor/managers/covariance_manager.hpp>
#include <riskfactor/archive/archiver.hpp>
#include <riskfactor/easylogging++/easylogging++.h>

#include <riskfactor/covariance/covariance_sma.hpp>
#include <riskfactor/covariance/covariance_ewma.hpp>
#include <riskfactor/argument.hpp>

namespace fre
{
	namespace riskfactor
	{
		Covariance::Ptr CovarianceManager::GetCovariance(RiskFactor::Ptr f1, RiskFactor::Ptr f2, const AverageType& type)
		{
			key_type key = GetKey(f1, f2, type);

			// cache search
			auto ptr = cache[key].lock();

			if (!ptr)
			{
				LOG(DEBUG) << "Not cached.. Creating a new covariance" << std::endl;
				ptr = Create(f1, f2, type);
			}
			else
			{
				LOG(DEBUG) << "Covariance loaded from cache" << std::endl;
			}

			return ptr;
		}

		Covariance::Ptr CovarianceManager::Create(RiskFactor::Ptr f1, RiskFactor::Ptr f2, const AverageType& type)
		{
			Covariance::Ptr ptr;
			
			LOG(DEBUG) << "TYPE = " << int(type) << std::endl;

			switch (type)
			{
			case AverageType::SMA: ptr = std::make_shared <CovarianceSMA>(CovarianceSMA(f1, f2)); break;
			case AverageType::EWMA:ptr = std::make_shared<CovarianceEWMA>(CovarianceEWMA(f1, f2)); break;
			}

			if (!ptr)
			{
				LOG(ERROR) << "Wrong AverageType! Null Covariance::ptr returned." << std::endl;
			}
			else
			{
				key_type& key = GetKey(f1, f2, type);
				LOG(DEBUG) << "Adding created Covariance to cache" << std::endl;
				cache[key] = ptr;
			}

			return ptr;
		}

		CovarianceManager::key_type CovarianceManager::GetKey(RiskFactor::Ptr f1, RiskFactor::Ptr f2, const AverageType& type)
		{
			RiskFactor::Ptr key1, key2;

			if (f1 > f2)
			{
				key1 = f1;
				key2 = f2;
			}
			else
			{
				key1 = f2;
				key2 = f1;
			}

			return std::make_tuple(key1, key2, type);
		}

	}
}