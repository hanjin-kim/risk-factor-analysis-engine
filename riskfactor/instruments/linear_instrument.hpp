#ifndef fre_riskfactor_linear_exposure_hpp
#define fre_riskfactor_linear_exposure_hpp

#include <map>
#include <tuple>

#include <Eigen/Dense>

#include <riskfactor/types.hpp>
#include <riskfactor/named.hpp>
#include <riskfactor/risk_factor.hpp>
#include <riskfactor/easylogging++/easylogging++.h>

namespace fre
{
	namespace riskfactor
	{
		typedef Bool Mask;
		typedef Data Weight;
		typedef Data Delta;
		typedef Data Exposure;
		typedef String Option;
		typedef Data Price;

		using Matrix = Eigen::Matrix<Data, Eigen::Dynamic, Eigen::Dynamic>;
		using Vector = Eigen::Matrix<Data, Eigen::Dynamic, 1>;

		class LinearInstrument : public Named, public Calendarical
		{
		public:
			typedef std::tuple<Mask, Weight, Delta> tuple_type;
			typedef std::map<RiskFactor::Ptr, tuple_type> map_type;

		protected:
			/** key : ptr to RiskFactor, value : tuple<mask, Weight, Delta>  */
			map_type factor_list;

			// Exposure evaluation reference
			Date closing_date;
			Price closing_price; // not adjusted

			std::shared_ptr<Matrix> ptr_covariance_matrix;
			std::shared_ptr<Vector> ptr_basis;

			Exposure exposure;

		public:
			LinearInstrument(const Name&, const Desc&);
			virtual ~LinearInstrument();

			virtual Exposure EvaluateExposure(const Option& = "") = 0;

			void SetClosingPrice(const Date&, const Price&);
			void SetMask(const RiskFactor::Ptr, const bool mask = 1);
			void SetWeight(const RiskFactor::Ptr, const Weight&);
			void SetDelta(const RiskFactor::Ptr, const Delta&);
			void RemoveRiskFactor(const RiskFactor::Ptr);
			void InitializeRiskFactorList() { factor_list.swap(map_type()); }

			std::pair<Date, Price> GetClosingPrice() const { return std::make_pair(closing_date, closing_price); }
			Mask GetMask(const RiskFactor::Ptr) const;
			Weight GetWeight(const RiskFactor::Ptr) const;
			Delta GetDelta(const RiskFactor::Ptr) const;
			const map_type& GetFactorList() const { return factor_list; }

			Size MaskedSize();

			void PrintFactorList();
			void PrintFactorList(::el::base::Writer& os);

			typedef std::shared_ptr<LinearInstrument> Ptr;
			typedef std::weak_ptr<LinearInstrument> WPtr;
			typedef std::unique_ptr<LinearInstrument> UPtr;

		protected:

			std::list<Option> TokenizeOptionString(const Option&);
			std::map<Option, Data> GetMappedOptionList(const Option&);

			void RegisterRiskFactor(const RiskFactor::Ptr, const Delta&, const Weight& = 1);

			Matrix EvaluateCovarianceMatrix(Size, const Option& = "");

			Exposure DefaultEvaluateExposure(const Option& opt);
		};
	}
}
#endif // !fre_riskfactor_linear_instrument_hpp
