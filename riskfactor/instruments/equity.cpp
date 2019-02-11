#include <riskfactor/instruments/equity.hpp>
#include <riskfactor/managers/risk_factor_manager.hpp>
namespace fre
{
	namespace riskfactor
	{
		Equity::Equity(const Name& nm, const Desc& desc)
			: LinearInstrument(nm, desc)
		{}

		Equity::~Equity()
		{}

		Exposure Equity::EvaluateExposure(const Option& opt)
		{
			exposure = DefaultEvaluateExposure(opt);
			return exposure;
		}

		// portfolio 가 null 이 아니면 beta riskfactor 로 봄
		void Equity::RegisterRiskFactor(const RiskFactor::Ptr factor, const RiskFactor::Ptr portfolio)
		{
			// todo : beta factor
			LinearInstrument::RegisterRiskFactor(factor, Delta(1), Weight(1));
		}
		/*
		void Equity::RegisterRiskFactor(const Name& name)
		{
			RiskFactorManager& mgr = RiskFactorManager::GetInstance();
			RiskFactor::Ptr ptr = mgr.GetRiskFactor(name);

			RegisterRiskFactor(ptr);

			LOG(DEBUG) << "------- RiskFactor Registered --------" << std::endl;
			LOG(DEBUG) << " Name : " << ptr->GetName() << std::endl;
			LOG(DEBUG) << " Size : " << ptr->size() << std::endl;
		}
		*/
	
	}
}