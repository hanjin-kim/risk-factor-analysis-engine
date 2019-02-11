#ifndef fre_riskfactor_covariance_manager_hpp
#define fre_riskfactor_covariance_manager_hpp

#include <unordered_map>
#include <tuple>

#include <riskfactor/types.hpp>
#include <riskfactor/patterns/singleton.hpp>
#include <riskfactor/risk_factor.hpp>
#include <riskfactor/covariance.hpp>
#include <riskfactor/utils/hash.hpp>

namespace fre
{
	namespace riskfactor
	{
		class CovarianceManager : public Singleton<CovarianceManager>
		{
		public :
			Covariance::Ptr GetCovariance(RiskFactor::Ptr f1, RiskFactor::Ptr f2, const AverageType& type = AverageType::EWMA);
			Covariance::Ptr Create(RiskFactor::Ptr f1, RiskFactor::Ptr f2, const AverageType& type = AverageType::EWMA);

			typedef std::tuple <RiskFactor::Ptr, RiskFactor::Ptr, AverageType> key_type;

		private:
			std::unordered_map<key_type, Covariance::WPtr> cache;
			
			key_type GetKey(RiskFactor::Ptr f1, RiskFactor::Ptr f2, const AverageType& type);
		};
	}
}

#endif // !fre_riskfactor_covariance_manager_hpp
