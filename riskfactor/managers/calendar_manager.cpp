#include <memory>

#include <riskfactor/managers/calendar_manager.hpp>
#include <riskfactor/archive/archiver.hpp>
#include <riskfactor/calendar/calendar.hpp>
#include <riskfactor/calendar/calendar_tag.hpp>

namespace fre
{
	namespace riskfactor
	{
		Calendar::Ptr CalendarManager::GetCalendar(const CalendarTag& tag)
		{
			// cache search
			auto ptr = cache[tag].lock();

			// if ptr is null
			if (!ptr)
			{
				// take a look into the archive
				ptr = std::static_pointer_cast<Calendar>(Archiver::Load("calendar/" + CalendarTagToString[tag]));
					

				// if no archive exist
				if (!ptr)
				{
					ptr = Calendar::Ptr(new Calendar(tag));
				}

				// register an weak_ptr to the cache
				cache[tag] = ptr;
			}

			return ptr;
		}
	}
}