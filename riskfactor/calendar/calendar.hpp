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
			QuantLib 캘린더를 FnRiskEngine에서 사용하기 위한 래퍼 클래스입니다.
			QuantLib 캘린더 객체를 unique_ptr 로 포함하고 있습니다.
			대부분의 멤버함수는 QuantLib::Calendar 를 바이패스합니다.
		*/
		class Calendar : public Archivable
		{
			/// CalendarTag
			CalendarTag tag;
			/// QuantLib Calendar 의 포인터.
			std::unique_ptr<::QuantLib::Calendar> ql_calendar;
			/// QuantLib 과는 별도로 관리되는 휴일 목록
			Date::Set added_holidays;
			Date::Set removed_holidays;
			/// 휴일 목록이 최종 수정된 날짜
			Date last_modified_date;

		public:
			/// CalendarTag 를 통한 생성
			Calendar(const CalendarTag& tag);
			/// 소멸자
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
			/// cereal smart pointer 아카이브를 위한 기본 생성자, 아무것도 안함
			Calendar() : last_modified_date(Date()) {}

		private:
			/// CalendarCheck
			void CheckQLCalendar();

			/// serialization 지원을 위한 프렌드 선언
			friend class ::boost::serialization::access;

			/// serialize 함수 선언
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
