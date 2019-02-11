#ifndef fre_riskfactor_covariance_matrix_hpp
#define fre_riskfactor_covariance_matrix_hpp

#include <Eigen/Dense>

#include <riskfactor/types.hpp>
#include <riskfactor/risk_factor.hpp>

namespace fre
{
	namespace riskfactor
	{
		using Matrix = Eigen::Matrix<Data, Eigen::Dynamic, Eigen::Dynamic>;

		typedef String Option;
		typedef Data Lambda;
		typedef bool Mask;

		class CovarianceMatrix
		{
		public:
			typedef std::map <RiskFactor::Ptr, bool> map_type;

		private:
			/** key : ptr to RiskFactor, value : tuple<mask, Weight, Delta, Gamma>  */
			map_type factor_list;

			bool factor_list_updated; // modification flag
			
		public :
			CovarianceMatrix();
			virtual ~CovarianceMatrix() {};
			
			std::shared_ptr<Matrix> GetCovarianceMatrix(const Date&, const Option& = "");

			void AddRiskFactor(const RiskFactor::Ptr, const Mask& = true);
			void RemoveRiskFactor(const RiskFactor::Ptr);
			void SetMask(const RiskFactor::Ptr, const Mask&);

		private :
			Size MaskedSize();

			std::list<Option> TokenizeOptionString(const Option&);
			std::map<Option, Data> GetMappedOptionList(const Option&);
		};
	}
}

#endif // !fre_riskfactor_covariance_matrix_hpp
