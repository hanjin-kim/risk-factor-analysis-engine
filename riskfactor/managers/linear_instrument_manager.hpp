#ifndef fre_riskfactor_linear_instrument_manager_hpp
#define fre_riskfactor_linear_instrument_manager_hpp

#include <unordered_map>

#include <riskfactor/types.hpp>
#include <riskfactor/patterns/singleton.hpp>
#include <riskfactor/instruments/linear_instrument.hpp>

namespace fre
{
	namespace riskfactor
	{
		enum class LinearInstrumentType
		{
			equity,
			bond,
			cash,
		};

		class LinearInstrumentManager : public Singleton<LinearInstrumentManager>
		{
		public:
			LinearInstrument::Ptr GetInstrument(const Name& name);
			LinearInstrument::Ptr Create(const Name&, const Desc&, const LinearInstrumentType& type);

		private:
			std::unordered_map<Name, LinearInstrument::WPtr> cache;
		};
	}
}

#endif // !fre_riskfactor_risk_factor_manager_hpp
