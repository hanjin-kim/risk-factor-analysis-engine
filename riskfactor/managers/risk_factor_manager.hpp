#ifndef fre_riskfactor_risk_factor_manager_hpp
#define fre_riskfactor_risk_factor_manager_hpp

#include <unordered_map>

#include <riskfactor/types.hpp>
#include <riskfactor/patterns/singleton.hpp>
#include <riskfactor/risk_factor.hpp>

namespace fre
{
	namespace riskfactor
	{
		enum class CalendarTag;

		enum class RiskFactorType
		{
			None,
			EquityPrice,
			BondYield,
		};

		class RiskFactorManager : public Singleton<RiskFactorManager>
		{
		public :
			RiskFactor::Ptr GetRiskFactor(const Name& name);
			RiskFactor::Ptr Create(const Name&, const Desc&, const CalendarTag&, const Size size, const RiskFactorType& type = RiskFactorType::None);

		private :
			std::unordered_map<Name, RiskFactor::WPtr> cache;
		};
	}
}

#endif // !fre_riskfactor_risk_factor_manager_hpp
