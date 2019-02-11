#ifndef fre_riskfactor_covariance_ewma_hpp
#define fre_riskfactor_covariance_ewma_hpp

#include <riskfactor/covariance.hpp>
#include <riskfactor/argument.hpp>

namespace fre
{
	namespace riskfactor
	{
		class CovarianceEWMA : public Covariance
		{
		public:
			CovarianceEWMA(RiskFactor::Ptr f1, RiskFactor::Ptr f2);
			virtual ~CovarianceEWMA() {};

			virtual Data Evaluate(const Date&, const Size&, const ArgList args) override;

			//typedef std::map<std::tuple<double, Date, Size>, Data> cache_type;

		protected :
			CovarianceEWMA() {}

		private :
			//cache_type cache;
		};
	}
}

#endif // !fre_riskfactor_covariance_ewma_hpp
