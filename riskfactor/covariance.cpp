#include <riskfactor/types.hpp>
#include <riskfactor/covariance.hpp>
#include <riskfactor/errors.hpp>
#include <riskfactor/easylogging++/easylogging++.h>

namespace fre
{
	namespace riskfactor
	{	
		Covariance::Covariance(RiskFactor::Ptr f1, RiskFactor::Ptr f2)
			: Calendarical(SetupCalendar(f1, f2)), reference{ f1, f2 }
		{}
		const Calendar::Ptr Covariance::SetupCalendar(RiskFactor::Ptr f1, RiskFactor::Ptr f2)
		{
			// todo
			// adjustment for two different calendar..
			if (f1->GetCalendar() != f2->GetCalendar())
			{
				LOG(ERROR) << "Calendar is different between two riskfactors!!" << std::endl;
				throw Error("riskfactor/covariance.cpp", 22, "SetupCalendar", "Calendar is different between two riskfactors.");
			}

			return f1->GetCalendar();
		}

		template <class Archive>
		void Covariance::serialize(Archive& ar, const unsigned int version)
		{
			ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Archivable);
			ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Forecast);

		}
	}
}