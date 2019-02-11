#ifndef fre_riskfactor_cash_hpp
#define fre_riskfactor_cash_hpp

#include <riskfactor/instruments/linear_instrument.hpp>

namespace fre
{
	namespace riskfactor
	{
		class Cash : public LinearInstrument
		{
		public :
			Cash(const Name& n, const Desc& d)
				: LinearInstrument(n, d)
			{}

			virtual ~Cash() {}

			virtual Data EvaluateExposure(const Option&)
			{
				return 0;
			}
		};
	}
}

#endif // !fre_riskfactor_cash_hpp
