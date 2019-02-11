#ifndef fre_param_var_linear_portfolio_hpp
#define fre_param_var_linear_portfolio_hpp

#include <map>
#include <memory>

#include <riskfactor/instruments/linear_instrument.hpp>

namespace fre
{
	namespace riskfactor
	{

		typedef double Beta;

		class LinearInstrumentPortfolio : public LinearInstrument
		{
		public:
			typedef std::pair<Mask, Weight> pair_type;
			/** key : ptr : pair<amount of shares, mask> */
			typedef std::map<LinearInstrument::Ptr, pair_type> entry_map_type;
			entry_map_type entry_list;

		public:
			LinearInstrumentPortfolio(const Name&, const Desc&);
			virtual ~LinearInstrumentPortfolio();

			virtual Exposure EvaluateExposure(const String& opt) override;

//			int AddInstrument(const LinearInstrument& inst, const Amount&, const Mask& = true);
			int AddInstrument(const LinearInstrument::Ptr inst, const Weight&, const Mask& = true);

//			void RemoveInstrument(const LinearInstrument& inst);
			void RemoveInstrument(const LinearInstrument::Ptr inst);

			void SetMask(const LinearInstrument::Ptr inst, const Mask& = 1);
			void SetWeight(const LinearInstrument::Ptr inst, const Weight&);

			Exposure EvaluateContributionalExposure(const LinearInstrument::Ptr inst);
			Exposure EvaluateIncrementalExposure(const LinearInstrument::Ptr inst);
			
		private:
			/** Weight matrix evaluation */
			void EvaluateRiskFactorWeights();

			bool riskfactor_weight_evaluated;
			bool entrylist_evaluated;
			
		};
	}
}

#endif // !fre_param_var_portfolio_hpp
