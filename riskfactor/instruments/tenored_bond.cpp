#include <riskfactor/instruments/tenored_bond.hpp>
#include <riskfactor/managers/risk_factor_manager.hpp>
#include <riskfactor/risk_factor/bond_yield.hpp>

namespace fre
{
	namespace riskfactor
	{
		TenoredBond::TenoredBond(const Name& name, const Desc& desc)
			: LinearInstrument(name, desc)
		{}

		/*
		void TenoredBond::SetCurvInfo(const CurvName& name, const Duration& duration, const TenorL& tl, const TenorR& tr)
		{
			InitializeRiskFactorList();

			std::pair<Date, Price> ref_data = GetClosingPrice();
			Date ref_date = ref_data.first;

			YearFraction left_duration = TenorToYearFraction(tl);
			YearFraction right_duration = left_duration;

			if (tr != Tenor::None && tr != tl)
				right_duration = TenorToYearFraction(tr);

			// Duration mapping
			Weight w = 1;
			
			if(tr != Tenor::None && tr != tl)
				w = (right_duration - duration) / (right_duration - left_duration);

			// risk factor registeration
			RiskFactorManager& mgr = RiskFactorManager::GetInstance();

			Name left_name = name + "_" + TenorToString(tl);

			BondYield::Ptr left_factor = std::static_pointer_cast<BondYield>(mgr.GetRiskFactor(left_name));

			// delta = MD x y, weight obtained above
			Yield left_y = left_factor->GetYield(ref_date);
			Delta left_delta = left_duration / (1. + left_y) * left_y;
			Weight left_weight = w;

			RegisterRiskFactor(left_factor, left_delta, left_weight);

			if (tr != Tenor::None && tr != tl)
			{
				Name right_name = name + "_" + TenorToString(tr);

				BondYield::Ptr right_factor = std::static_pointer_cast<BondYield>(mgr.GetRiskFactor(right_name));

				Yield right_y = right_factor->GetYield(ref_date);
				Delta right_delta = right_duration / (1. + right_y) * right_y;
				Weight right_weight = 1 - w;


				RegisterRiskFactor(right_factor, right_delta, right_weight);
			}
		}
		*/
		void TenoredBond::SetCurvInfo(const Duration& duration, BondYield::Ptr tl, BondYield::Ptr tr)
		{
			InitializeRiskFactorList();

			std::pair<Date, Price> ref_data = GetClosingPrice();
			Date ref_date = ref_data.first;

			YearFraction left_duration = tl->GetDuration();
			YearFraction right_duration = 0;

			if (tr)
				right_duration = tr->GetDuration();

			// Duration mapping
			Weight w = 1;

			if (tr)
				w = (right_duration - duration) / (right_duration - left_duration);

			// risk factor registeration
			RiskFactorManager& mgr = RiskFactorManager::GetInstance();

			// delta = MD x y, weight obtained above
			Yield left_y = tl->GetYield(ref_date);
			Delta left_delta = left_duration / (1. + left_y) * left_y;
			Weight left_weight = w;

			RegisterRiskFactor(tl, left_delta, left_weight);

			if (tr)
			{
				Yield right_y = tr->GetYield(ref_date);
				Delta right_delta = right_duration / (1. + right_y) * right_y;
				Weight right_weight = 1 - w;

				RegisterRiskFactor(tr, right_delta, right_weight);
			}
		}

		Exposure TenoredBond::EvaluateExposure(const Option& opt)
		{
			exposure = DefaultEvaluateExposure(opt);
			return exposure;
		}

		Name TenoredBond::TenorToString(const Tenor& t)
		{
			Name ret;

			switch (t)
			{
			case Tenor::OneD: ret = "1D"; break;
			case Tenor::ThreeM: ret = "3M"; break;
			case Tenor::SixM: ret = "6M"; break;
			case Tenor::NineM: ret = "9M"; break;
			case Tenor::OneY: ret = "1Y"; break;
			case Tenor::OneHalfY: ret = "1Y6M"; break;
			case Tenor::TwoY: ret = "2Y"; break;
			case Tenor::TwoHalfY: ret = "2Y6M"; break;
			case Tenor::ThreeY: ret = "3Y"; break;
			case Tenor::FourY: ret = "4Y"; break;
			case Tenor::FiveY: ret = "5Y"; break;
			case Tenor::SevenY: ret = "7Y"; break;
			case Tenor::TenY: ret = "10Y"; break;
			case Tenor::FifteenY: ret = "15Y"; break;
			case Tenor::TwentyY: ret = "20Y"; break;
			case Tenor::TwentyFiveY: ret = "25Y"; break;
			case Tenor::ThirtyY: ret = "30Y"; break;
			case Tenor::FourtyY: ret = "40Y"; break;
			case Tenor::FiftyY: ret = "50Y"; break;
			}

			return ret;
		}

		YearFraction TenoredBond::TenorToYearFraction(const Tenor& t)
		{
			YearFraction ret;

			switch (t)
			{
			case Tenor::OneD: ret = 0.00273973; break;
			case Tenor::ThreeM: ret = 0.25; break;
			case Tenor::SixM: ret = 0.5; break;
			case Tenor::NineM: ret = 0.75; break;
			case Tenor::OneY: ret = 1.; break;
			case Tenor::OneHalfY: ret = 1.5; break;
			case Tenor::TwoY: ret = 2.; break;
			case Tenor::TwoHalfY: ret = 2.5; break;
			case Tenor::ThreeY: ret = 3.; break;
			case Tenor::FourY: ret = 4.; break;
			case Tenor::FiveY: ret = 5.; break;
			case Tenor::SevenY: ret = 7.; break;
			case Tenor::TenY: ret = 10.; break;
			case Tenor::FifteenY: ret = 15.; break;
			case Tenor::TwentyY: ret = 20.; break;
			case Tenor::TwentyFiveY: ret = 25.; break;
			case Tenor::ThirtyY: ret = 30.; break;
			case Tenor::FourtyY: ret = 40.; break;
			case Tenor::FiftyY: ret = 50.; break;
			}

			return ret;
		}
		
	}
}