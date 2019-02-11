#include <riskfactor/managers/linear_instrument_manager.hpp>
#include <riskfactor/easylogging++/easylogging++.h>

#include <riskfactor/instruments/equity.hpp>
#include <riskfactor/instruments/tenored_bond.hpp>
#include <riskfactor/instruments/cash.hpp>


namespace fre
{
	namespace riskfactor
	{
		LinearInstrument::Ptr LinearInstrumentManager::GetInstrument(const Name& name)
		{

			// cache search 
			auto ptr = cache[name].lock();

			if (!ptr)
			{

				LOG(DEBUG) << "Instrument does not exist." << std::endl;
				return LinearInstrument::Ptr();
			}
			else
			{
				LOG(DEBUG) << "Instrument loaded from cache" << std::endl;
			}

			return ptr;
		}

		LinearInstrument::Ptr LinearInstrumentManager::Create(const Name& name, const Desc& desc, const LinearInstrumentType& type)
		{
			LinearInstrument::Ptr ptr = GetInstrument(name);

			if (!ptr)
			{
				LOG(DEBUG) << "Creating a new Instrument object.." << std::endl;

				switch (type)
				{
				case LinearInstrumentType::equity: ptr = std::make_shared<Equity>(Equity(name, desc)); break;
				case LinearInstrumentType::bond: ptr = std::make_shared<TenoredBond>(TenoredBond(name, desc)); break;
				case LinearInstrumentType::cash: ptr = std::make_shared<Cash>(Cash(name, desc)); break;
				}

				cache[name] = ptr;
				LOG(DEBUG) << "Instrument added to cache" << std::endl;
			}

			return ptr;
		}
	}
}