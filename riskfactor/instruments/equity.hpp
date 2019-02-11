#ifndef fre_param_var_equity
#define fre_param_var_equity

#include <riskfactor/instruments/linear_instrument.hpp>

namespace fre
{
	namespace riskfactor
	{
		typedef Data Beta;

		class Equity : public LinearInstrument
		{
		public:
			Equity(const Name&, const Desc&);
			virtual ~Equity();

			virtual Exposure EvaluateExposure(const Option& opt) override;

			//void RegisterRiskFactor(const Name&);
			void RegisterRiskFactor(const RiskFactor::Ptr, const RiskFactor::Ptr = RiskFactor::Ptr());
		};
	}
}

#endif // !fre_param_var_equity
