#ifndef fre_riskfactor_calendar_hpp
#define fre_riskfactor_calendar_hpp

#include <memory>

#include <boost/serialization/access.hpp>
#include <boost/serialization/export.hpp>

#include <ql/time/calendar.hpp>

#include <riskfactor/types.hpp>
#include <riskfactor/date.hpp>
#include <riskfactor/weekday.hpp>
#include <riskfactor/archivable.hpp>

namespace fre
{
	namespace riskfactor
	{
		enum class CalendarTag;
		/*!
			QuantLib Ķ������ FnRiskEngine���� ����ϱ� ���� ���� Ŭ�����Դϴ�.
			QuantLib Ķ���� ��ü�� unique_ptr �� �����ϰ� �ֽ��ϴ�.
			��κ��� ����Լ��� QuantLib::Calendar �� �����н��մϴ�.
		*/
		class Calendar : public Archivable
		{
			/// CalendarTag
			CalendarTag tag;
			/// QuantLib Calendar �� ������.
			std::unique_ptr<::QuantLib::Calendar> ql_calendar;
			/// QuantLib ���� ������ �����Ǵ� ���� ���
			Date::Set added_holidays;
			Date::Set removed_holidays;
			/// ���� ����� ���� ������ ��¥
			Date last_modified_date;

		public:
			/// CalendarTag �� ���� ����
			Calendar(const CalendarTag& tag);
			/// �Ҹ���
			virtual ~Calendar() {}

			bool empty() const;
			String name() const;
			bool isBusinessDay(const Date& d) const;
			bool isHoliday(const Date& d) const;
			bool isWeekend(Weekday w) const;
			bool isEndOfMonth(const Date& d) const;
			Date endOfMonth(const Date& d) const;
			void addHoliday(const Date&);
			void removeHoliday(const Date&);

			Date adjust(const Date&,
				::QuantLib::BusinessDayConvention convention = ::QuantLib::Following) const;
			
			/*
			static std::vector<Date> holidayList(const Calendar& calendar,
			const Date& from,
			const Date& to,
			bool includeWeekEnds = false);
			virtual Date advance(const Date&,
			Integer n,
			TimeUnit unit,
			QuantLib::BusinessDayConvention convention = QuantLib::Following,
			bool endOfMonth = false) const;
			virtual Date advance(const Date& date,
			const Period& period,
			QuantLib::BusinessDayConvention convention = QuantLib::Following,
			bool endOfMonth = false) const;
			virtual Date::serial_type businessDaysBetween(const Date& from,
			const Date& to,
			bool includeFirst = true,
			bool includeLast = false) const;
			*/
			Date LastModifiedDate() const { return last_modified_date; }
			CalendarTag GetCalendarTag() const { return tag; }

			virtual void SetArchiveTag(const ArchiveTag&) override {}

		protected:
			/// cereal smart pointer ��ī�̺긦 ���� �⺻ ������, �ƹ��͵� ����
			Calendar() : last_modified_date(Date()) {}

		private:
			/// CalendarCheck
			void CheckQLCalendar();

			/// serialization ������ ���� ������ ����
			friend class ::boost::serialization::access;

			/// serialize �Լ� ����
			template <class Archive>
			void save(Archive& ar, const unsigned int version) const;

			template <class Archive>
			void load(Archive& ar, const unsigned int version);

			template <class Archive>
			void serialize(Archive& ar, const unsigned int version);

		public:
			typedef std::shared_ptr<Calendar> Ptr;
			typedef std::shared_ptr <const Calendar> CPtr;
			typedef std::unique_ptr<Calendar> UPtr;
			typedef std::weak_ptr<Calendar> WPtr;

			friend bool operator==(const Calendar& c1, const Calendar& c2)
			{
				return (c1.empty() && c2.empty())
					|| (!c1.empty() && !c2.empty() && c1.name() == c2.name());
			}
			friend bool operator!=(const Calendar& c1, const Calendar& c2)
			{
				return !(c1 == c2);
			}

			friend std::ostream& operator<<(std::ostream& out, const Calendar &c)
			{
				return out << c.name();
			}
		};
	}
}

BOOST_CLASS_EXPORT_KEY(fre::riskfactor::Calendar)

#endif // !fre_calendar_hpp
