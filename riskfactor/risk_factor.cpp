#include <boost/serialization/nvp.hpp>
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/shared_ptr.hpp>

#include <riskfactor/risk_factor.hpp>
#include <riskfactor/errors.hpp>
#include <riskfactor/calendar/calendar_tag.hpp>
#include <riskfactor/calendar/calendar.hpp>
#include <riskfactor/easylogging++/easylogging++.h>

namespace fre
{
	namespace riskfactor
	{
		RiskFactor::RiskFactor(const Name& name, const Desc& desc, const CalendarTag& cal_tag, const Size size)
			: Named(name, desc), Calendarical(cal_tag), SeriesObject(size), Archivable(ArchiveTag(name))
		{
			LOG(DEBUG) << "\nRiskFactor constructed" << "\n";
		}

		RiskFactor::RiskFactor(const Name& name, const Desc& desc, Calendar::Ptr cal, const Size size)
			: Named(name, desc), Calendarical(cal), SeriesObject(size), Archivable(ArchiveTag(name))
		{}

		void RiskFactor::Insert(const Date& date, const Data& data)
		{

			if (!GetCalendar()->isBusinessDay(date))
			{
				LOG(ERROR) << "The date provided, " << date << ", is not a business day" << std::endl;
				return;
			}

			if (!empty() && GetCalendar()->adjust(rbegin()->first + 1) != date)
			{
				LOG(ERROR) << "The date provided, " << date
					<< ", is not succeeding the last business day," << rbegin()->first << std::endl;
				return;
			}

			if (!GetCalendar()->isBusinessDay(date))
			{
				LOG(ERROR) << date << " is not a business day. Data is not inserted." << std::endl;
				return;
			}

			if (size() == GetNMax())
			{
				VLOG(1) << "Exceeding container limit = " << GetNMax() << ". Erasing the oldest data." << std::endl;
				erase(begin());
			}

			insert(std::make_pair(date, data));
			VLOG(2) << "Data (" << date << " : " << date << ") added." << std::endl;

		}

		template <class Archive>
		void RiskFactor::serialize(Archive& ar, const unsigned int version)
		{
			ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Named);
			ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Archivable);
			ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(SeriesObject);
			ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Calendarical);
//			ar & BOOST_SERIALIZATION_NVP(vol_map);
		}
	}
}

BOOST_CLASS_EXPORT_IMPLEMENT(fre::riskfactor::RiskFactor)

#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>

template void fre::riskfactor::RiskFactor::serialize(boost::archive::xml_oarchive & ar, const unsigned int version);
template void fre::riskfactor::RiskFactor::serialize(boost::archive::xml_iarchive & ar, const unsigned int version);