#ifndef fre_risk_factor_tenored_bond_hpp
#define fre_risk_factor_tenored_bond_hpp

#include <riskfactor/instruments/linear_instrument.hpp>
#include <riskfactor/risk_factor/bond_yield.hpp>

namespace fre
{
	namespace riskfactor
	{	
		enum class Tenor
		{
			OneD,
			ThreeM,
			SixM,
			NineM,
			OneY,
			OneHalfY,
			TwoY,
			TwoHalfY,
			ThreeY,
			FourY,
			FiveY,
			SevenY,
			TenY,
			FifteenY,
			TwentyY,
			TwentyFiveY,
			ThirtyY,
			FourtyY,
			FiftyY,
			None,
		};


		typedef Data YearFraction;
		typedef Name CurvName;
		typedef YearFraction Duration;

		typedef Tenor TenorL;
		typedef Tenor TenorR;

		class TenoredBond : public LinearInstrument
		{
		public:
			TenoredBond(const Name&, const Desc&);
			virtual ~TenoredBond() {}

			//void SetCurvInfo(const CurvName&, const Duration&, const TenorL&, const TenorR& = Tenor::None);
			void SetCurvInfo(const Duration&, BondYield::Ptr, BondYield::Ptr = BondYield::Ptr());
			virtual Exposure EvaluateExposure(const Option& opt) override;

			static Name TenorToString(const Tenor& t);
			static YearFraction TenorToYearFraction(const Tenor& t);
			
		};
	}
}

#endif // !fre_risk_factor_fnguide_bond_hpp
