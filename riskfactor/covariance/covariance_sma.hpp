#ifndef fre_riskfactor_covariance_sma_hpp
#define fre_riskfactor_covariance_sma_hpp

#include <riskfactor/covariance.hpp>
#include <riskfactor/argument.hpp>

namespace fre
{
	namespace riskfactor
	{
		class CovarianceSMA : public Covariance
		{
		public :
			CovarianceSMA(RiskFactor::Ptr f1, RiskFactor::Ptr f2);

			virtual ~CovarianceSMA() {};

			virtual Data Evaluate(const Date& ref_date, const Size& ndays, const ArgList) override;

			//typedef std::map<std::tuple<Date, Size>, Data> cache_type;

		protected :
			CovarianceSMA() {}

		private:
			//cache_type cache;
		};
	}
}

#endif // !fre_riskfactor_covariance_sma_hpp
