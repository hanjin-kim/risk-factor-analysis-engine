/*!
 *\file calendar_manager.hpp
 *\author Hanjin Kim
 *\date 2017-05-04
 *\brief A singleton object under control of the calendar objects
 *
 * QuantLib Calendars are instantiated at the first instantiation of CalendarManager.
 * The only public member method is <tt>GetCalendar(string name)</tt> which find 
 * the Calendar object corresponding to the given name convention.
 * The Name convention and it constructor should be predefined at the end of the file.
 *
 * Usage : boost::shared_ptr<Calendar> calendar_obj = CalendarManager::GetCalendar("SouthKorea");
 *
 *\note There is no destructor since this object should live until the whole process ends.
 * 
 */

#ifndef fre_map_calendar_manager_hpp
#define fre_map_calendar_manager_hpp

#include <unordered_map>

#include <riskfactor/types.hpp>
#include <riskfactor/patterns/singleton.hpp>
#include <riskfactor/calendar/calendar.hpp>

namespace fre
{
	namespace riskfactor
	{
		enum class CalendarTag;

		class CalendarManager : public Singleton<CalendarManager>
		{
		public:
			Calendar::Ptr GetCalendar(const CalendarTag&);

		private:
			std::unordered_map<CalendarTag, Calendar::WPtr, EnumClassHash> cache;
		};
	}
}

#endif // !fre_map_calendar_hpp
