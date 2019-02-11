#include <riskfactor/managers/risk_factor_manager.hpp>
#include <riskfactor/archive/archiver.hpp>
#include <riskfactor/easylogging++/easylogging++.h>

#include <riskfactor/risk_factor/equity_price.hpp>
#include <riskfactor/risk_factor/bond_yield.hpp>

namespace fre
{
	namespace riskfactor
	{
		RiskFactor::Ptr RiskFactorManager::GetRiskFactor(const Name& name)
		{
			// cache search 
			auto ptr = cache[name].lock();

			if (!ptr)
			{

				// take a look into the archive
				ptr = std::static_pointer_cast<RiskFactor, Archivable>(Archiver::Load(name));

				if (!ptr)
				{
					LOG(DEBUG) << "No archive exists for " << name << "." << std::endl;
					return ptr;
				}
				else
				{
					LOG(DEBUG) << "RiskFactor loaded from its archive" << std::endl;
				}

				LOG(DEBUG) << "Adding loaded RiskFactor to cache" << std::endl;
				cache[name] = ptr;
			}
			else
			{
				LOG(DEBUG) << "RiskFactor loaded from cache" << std::endl;
			}

			LOG(DEBUG) << "------- RiskFactor found --------" << std::endl;
			LOG(DEBUG) << " Name : " << ptr->GetName() << std::endl;
			LOG(DEBUG) << " Size : " << ptr->size() << std::endl;
		
			return ptr;
		}

		RiskFactor::Ptr RiskFactorManager::Create(const Name& name, const Desc& desc, const CalendarTag& caltag, const Size size, const RiskFactorType& type)
		{
			RiskFactor::Ptr ptr = GetRiskFactor(name);

			if (!ptr)
			{
				LOG(DEBUG) << "Creating a new RiskFactor object.." << std::endl;

				switch (type)
				{
				case RiskFactorType::None: ptr = std::make_shared<RiskFactor>(RiskFactor(name, desc, caltag, size)); break;
				//case RiskFactorType::EquityPrice: ptr = std::make_shared<EquityPrice>(EquityPrice(name, desc, caltag, size)); break;
				//case RiskFactorType::BondYield: ptr = std::make_shared<BondYield>(BondYield(name, desc, caltag, size)); break;
				}

				cache[name] = ptr;
				LOG(DEBUG) << "RiskFactor added to cache" << std::endl;
			}
			
			return ptr;
		}
	}
}