#ifndef fre_riskfactor_calendarical_hpp
#define fre_riskfactor_calendarical_hpp

#include <memory>

#include <boost/serialization/access.hpp>

#include <riskfactor/named.hpp>
#include <riskfactor/timeseries.hpp>
#include <riskfactor/calendar/calendar.hpp>

namespace fre
{

	namespace riskfactor
	{
		/*!
			캘린더를 참조하는 시계열 데이터를 보관하는 객체를 위한 기반클래스입니다.
			캘린더, 시계열 데이터 컨테이너의 크기를 제공하여야 합니다.
			시계열 데이터의 상수 반복자를 통한 접근을 제공합니다.

			@todo 시계열 데이터 최대 크기를 변경할 수 있도록 해야한다. 
					현재 지정된 크기 보다 변경될 크기가 작을 경우, 재확인한다.
		*/
		class Calendarical// : public Enable_Shared_From_This<Calendarical>
		{
			/// 캘린더
			Calendar::Ptr calendar;


		public :
			/// CalendarTag 를 활용하는 생성자
			explicit Calendarical(const CalendarTag&);
			/// Calendar 포인터를 활용하는 생성자
			explicit Calendarical(Calendar::Ptr);
			/// 소멸자
			virtual ~Calendarical() {}

			/// 참조하는 캘린더를 반환합니다.
			Calendar::Ptr GetCalendar() { return calendar; }

			typedef std::shared_ptr<Calendarical> Ptr;
			typedef std::shared_ptr<const Calendarical> CPtr;
			typedef std::weak_ptr<Calendarical> WPtr;
			typedef std::unique_ptr<Calendarical> UPtr;

		protected :
			/// smart pointer 아카이브를 위한 기본 생성자, 아무것도 안함
			Calendarical() {}

		private :
			/// serialization 지원을 위한 프렌드 선언
			friend class ::boost::serialization::access;

			/// serialize 함수 선언
			template <class Archive>
			void save(Archive& ar, const unsigned int version) const;

			template <class Archive>
			void load(Archive& ar, const unsigned int version);

			template <class Archive>
			void serialize(Archive& ar, const unsigned int version);
		};
	}
}

#endif // !fre_riskfactor_calendarical_hpp
