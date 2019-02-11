#ifndef fre_riskfactor_covariance_factor_hpp
#define fre_riskfactor_covariance_factor_hpp

#include <memory>
#include <initializer_list>

#include <boost/serialization/access.hpp>
#include <boost/serialization/export.hpp>

#include <riskfactor/calendarical.hpp>
#include <riskfactor/risk_factor.hpp>
#include <riskfactor/calendar/calendar.hpp>
#include <riskfactor/argument.hpp>

namespace fre
{
	namespace riskfactor
	{
		class RiskFactor;

		typedef std::initializer_list<Argument> ArgList;

		class Covariance : public Calendarical
		{
		public:
			Covariance(RiskFactor::Ptr f1, RiskFactor::Ptr f2);
			virtual ~Covariance() {};

			typedef std::shared_ptr<Covariance> Ptr;
			typedef std::weak_ptr<Covariance> WPtr;
			typedef std::unique_ptr<Covariance> UPtr;

			// pure virtual function
			virtual Data Evaluate(const Date& ref_date, const Size& ndays = 250, const ArgList args = {}) = 0;

		protected :
			/// shared_ptr 아카이브를 위한 기본 생성자, 아무것도 안함
			Covariance() {}

			/// 참조 데이터 포인터
			RiskFactor::Ptr reference[2];

		private :
			static const Calendar::Ptr SetupCalendar(RiskFactor::Ptr f1, RiskFactor::Ptr f2);		

			friend class boost::serialization::access;

			template <class Archive>
			void serialize(Archive& ar, const unsigned int version);
		};
	}
}

BOOST_CLASS_EXPORT_KEY(fre::riskfactor::Covariance)


#endif // !fre_riskfactor_covariance_factor_hpp
