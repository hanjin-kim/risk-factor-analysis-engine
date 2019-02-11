#ifndef fre_riskfactor_risk_factor_portfolio_hpp
#define fre_riskfactor_risk_factor_portfolio_hpp

#include <riskfactor/risk_factor.hpp>

namespace fre
{
	namespace riskfactor
	{

		typedef Data Weight

		class RiskFactorPortfolio : public RiskFactor
		{
		public:
			typedef std::pair<Mask, Weight> pair_type;
			/** key : ptr : pair<amount of shares, mask> */
			typedef std::map<LinearInstrument::Ptr, pair_type> entry_map_type;
			entry_map_type entry_list;

		public :
			explicit RiskFactorPortfolio(const Name&, const Desc&, const CalendarTag&, const Size&);
			explicit RiskFactor(const Name&, const Desc&, Calendar::Ptr, const Size size = 250);

			virtual ~RiskFactor() {}

			void AddRiskFactor(const RiskFactor::Ptr, const Weight&)
		};
	}
}