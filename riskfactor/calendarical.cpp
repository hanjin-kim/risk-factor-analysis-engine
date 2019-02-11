#include <boost/serialization/nvp.hpp>
#include <boost/serialization/split_member.hpp>

#include <riskfactor/calendarical.hpp>
#include <riskfactor/calendar/calendar.hpp>
#include <riskfactor/calendar/calendar_tag.hpp>
#include <riskfactor/easylogging++/easylogging++.h>
#include <riskfactor/managers/calendar_manager.hpp>

namespace fre
{
	namespace riskfactor
	{
		Calendarical::Calendarical(const CalendarTag& cal_tag)
		{
			CalendarManager& mgr = CalendarManager::GetInstance();
			calendar = mgr.GetCalendar(cal_tag);

			LOG(DEBUG) << "\nCalendaricalData constructed" << "\n"
				<< "========================" << "\n"
				<< " cal_tag : " << CalendarTagToString[cal_tag] << std::endl;
		}
		
		Calendarical::Calendarical(Calendar::Ptr cal)
			: calendar(cal)
		{}

		template <class Archive>
		void Calendarical::save(Archive& ar, const unsigned int version) const
		{
			CalendarTag calendar_tag = calendar->GetCalendarTag();

			ar & BOOST_SERIALIZATION_NVP(calendar_tag);;
		}

		template <class Archive>
		void Calendarical::load(Archive& ar, const unsigned int version)
		{
			CalendarTag cal_tag;

			ar & boost::serialization::make_nvp("calendar_tag", cal_tag);

			CalendarManager& mgr = CalendarManager::GetInstance();
			calendar = mgr.GetCalendar(cal_tag);
		}

		template <class Archive>
		void Calendarical::serialize(Archive& ar, const unsigned int version)
		{
			boost::serialization::split_member(ar, *this, version);
		}
	}
}

#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>

template void fre::riskfactor::Calendarical::save(boost::archive::xml_oarchive & ar, const unsigned int version) const;
template void fre::riskfactor::Calendarical::load(boost::archive::xml_iarchive & ar, const unsigned int version);

template void fre::riskfactor::Calendarical::serialize(boost::archive::xml_oarchive & ar, const unsigned int version);
template void fre::riskfactor::Calendarical::serialize(boost::archive::xml_iarchive & ar, const unsigned int version);