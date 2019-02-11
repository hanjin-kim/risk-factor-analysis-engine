#include <boost/serialization/nvp.hpp>
#include <boost/serialization/split_member.hpp>

#include <riskfactor/easylogging++/easylogging++.h>
#include <riskfactor/calendar/calendar_tag.hpp>
#include <riskfactor/calendar/calendar.hpp>
#include <riskfactor/calendar/quantlib_calendar_factory.hpp>
#include <riskfactor/date.hpp>
#include <riskfactor/errors.hpp>

namespace fre
{
	namespace riskfactor
	{
		Calendar::Calendar(const CalendarTag& tag)
			: Archivable(ArchiveTag("calendar/" + CalendarTagToString[tag])),
			last_modified_date(Date())
		{
			LOG(DEBUG) << "Calendar constructor" << std::endl;
			CheckQLCalendar();
		}

		bool Calendar::empty() const
		{
			return !ql_calendar || ql_calendar->empty();
		}

		String Calendar::name() const
		{
			return ql_calendar->name();
		}

		bool Calendar::isBusinessDay(const Date& d) const
		{
			if (added_holidays.find(d) != added_holidays.end()) return false;
			if (removed_holidays.find(d) != removed_holidays.end()) return true;

			return ql_calendar->isBusinessDay(d);
		}

		bool Calendar::isHoliday(const Date& d) const
		{
			return !isBusinessDay(d);
		}

		bool Calendar::isWeekend(Weekday w) const
		{
			return ql_calendar->isWeekend(::QuantLib::Weekday(int(w)));
		}

		bool Calendar::isEndOfMonth(const Date& d) const
		{
			return ql_calendar->isEndOfMonth(d);
		}

		Date Calendar::endOfMonth(const Date& d) const
		{
			return Date(ql_calendar->endOfMonth(d));
		}

		void Calendar::addHoliday(const Date& d)
		{
			removed_holidays.erase(d);

			if (isBusinessDay(d))
			{
				last_modified_date = Date::todaysDate();
				added_holidays.insert(d);
			}
		}

		void Calendar::removeHoliday(const Date& d)
		{
			added_holidays.erase(d);

			if (!isBusinessDay(d))
			{
				last_modified_date = Date::todaysDate();
				removed_holidays.insert(d);
			}
		}

		/*
		static std::vector<Date> CalendarAdapter::holidayList(const Calendar& calendar, const Date& from, const Date& to, bool includeWeekEnds)
		{
			/// todo
			/// obsolete, perhaps
		}
		*/

		Date Calendar::adjust(const Date& d, ::QuantLib::BusinessDayConvention c) const
		{
			if (d == Date())
			{
//				LOG(ERROR) << "Null date provided. No adjustment implemented." << std::endl;
			}

			if (c == ::QuantLib::Unadjusted)
				return d;

			Date d1 = d;
			if (c == ::QuantLib::Following || c == ::QuantLib::ModifiedFollowing
				|| c == ::QuantLib::HalfMonthModifiedFollowing) {
				while (isHoliday(d1))
					d1++;
				if (c == ::QuantLib::ModifiedFollowing
					|| c == ::QuantLib::HalfMonthModifiedFollowing) {
					if (d1.month() != d.month()) {
						return adjust(d, ::QuantLib::Preceding);
					}
					if (c == ::QuantLib::HalfMonthModifiedFollowing) {
						if (d.dayOfMonth() <= 15 && d1.dayOfMonth() > 15) {
							return adjust(d, ::QuantLib::Preceding);
						}
					}
				}
			}
			else if (c == ::QuantLib::Preceding || c == ::QuantLib::ModifiedPreceding) {
				while (isHoliday(d1))
					d1--;
				if (c == ::QuantLib::ModifiedPreceding && d1.month() != d.month()) {
					return adjust(d, ::QuantLib::Following);
				}
			}
			else if (c == ::QuantLib::Nearest) {
				Date d2 = d;
				while (isHoliday(d1) && isHoliday(d2))
				{
					d1++;
					d2--;
				}
				if (isHoliday(d1))
					return d2;
				else
					return d1;
			}
			else {
//				LOG(ERROR) << "Unknown daycountconvention" << std::endl;
			}
			return d1;
		}
		/*
		virtual Date CalendarAdapter::advance(const Date& date,
			const Period& period,
			::QuantLib::BusinessDayConvention convention = ::QuantLib::Following,
			bool endOfMonth = false) const
		{
			/// todo
			/// obsolete, perhaps
		}

		virtual Date::serial_type CalendarAdapter::businessDaysBetween(const Date& from,
			const Date& to,
			bool includeFirst = true,
			bool includeLast = false) const
		{
			/// todo
			/// obsolete, perhaps
		}
		*/

		void Calendar::CheckQLCalendar()
		{
			if (!ql_calendar)
			{
				ql_calendar = QuantLibCalendarFactory::Create(tag);
			}
		}

		template <class Archive>
		void Calendar::save(Archive& ar, const unsigned int version) const
		{
			ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Archivable);
			ar & boost::serialization::make_nvp("calendar_tag", tag);
			ar & BOOST_SERIALIZATION_NVP(added_holidays);
			ar & BOOST_SERIALIZATION_NVP(removed_holidays);
			ar & BOOST_SERIALIZATION_NVP(last_modified_date);
		}

		template <class Archive>
		void Calendar::load(Archive& ar, const unsigned int version)
		{
			ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Archivable);
			ar & boost::serialization::make_nvp("calendar_tag", tag);
			ar & BOOST_SERIALIZATION_NVP(added_holidays);
			ar & BOOST_SERIALIZATION_NVP(removed_holidays);
			ar & BOOST_SERIALIZATION_NVP(last_modified_date);

			LOG(DEBUG) << "ADDED HOLIDAYS --------" << std::endl;
			for (auto holiday : added_holidays)
			{
				LOG(DEBUG) << holiday << std::endl;
			}

			CheckQLCalendar();
		}

		template<class Archive>
		void Calendar::serialize(Archive & ar,	const unsigned int version)
		{
			boost::serialization::split_member(ar, *this, version);
		}
	}
}

BOOST_CLASS_EXPORT_IMPLEMENT(fre::riskfactor::Calendar)

#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>

template void fre::riskfactor::Calendar::save(boost::archive::xml_oarchive & ar, const unsigned int version) const;
template void fre::riskfactor::Calendar::load(boost::archive::xml_iarchive & ar, const unsigned int version);

template void fre::riskfactor::Calendar::serialize(boost::archive::xml_oarchive & ar, const unsigned int version);
template void fre::riskfactor::Calendar::serialize(boost::archive::xml_iarchive & ar, const unsigned int version);