#ifndef fre_riskfactor_quantlib_calendar_factory_hpp
#define fre_riskfactor_quantlib_calendar_factory_hpp

#include <memory>

#include <ql/time/calendars/all.hpp>

#include <riskfactor/types.hpp>
#include <riskfactor/calendar/calendar_tag.hpp>

namespace fre
{
	namespace riskfactor
	{
		/*!
			QuantLib 캘린더를 생성하는 팩토리 클래스.
			생성을 위한 전역함수를 제공합니다.
			CalendarAdapter의 생성자에서 사용됩니다.
		*/
		class QuantLibCalendarFactory
		{
		public:
			static std::unique_ptr<::QuantLib::Calendar> Create(const CalendarTag&);
		};

		std::unique_ptr<::QuantLib::Calendar> QuantLibCalendarFactory::Create(const CalendarTag& tag)
		{
			namespace ql = ::QuantLib;

			typedef std::unique_ptr<ql::Calendar> ptr_type;

			ptr_type ptr;

			if (tag == CalendarTag::SouthKorea_Settlement)
			{
				ptr = ptr_type(new ql::SouthKorea(ql::SouthKorea::Market::Settlement));
			}
			else if (tag == CalendarTag::SouthKorea || tag == CalendarTag::SouthKorea_KRX)
			{
				ptr = ptr_type(new ql::SouthKorea(ql::SouthKorea::Market::KRX));
			}
			else if (tag == CalendarTag::UnitedStates || tag == CalendarTag::UnitedStates_Settlement)
			{
				ptr = ptr_type(new ql::UnitedStates(ql::UnitedStates::Market::Settlement));
			}
			else if (tag == CalendarTag::UnitedStates_NYSE)
			{
				ptr = ptr_type(new ql::UnitedStates(ql::UnitedStates::Market::NYSE));
			}
			else if (tag == CalendarTag::UnitedStates_GovernmentBond)
			{
				ptr = ptr_type(new ql::UnitedStates(ql::UnitedStates::Market::GovernmentBond));
			}
			else if (tag == CalendarTag::UnitedStates_NERC)
			{
				ptr = ptr_type(new ql::UnitedStates(ql::UnitedStates::Market::NERC));
			}
			else if (tag == CalendarTag::Argentina || tag == CalendarTag::Argentina_Merval)
			{
				ptr = ptr_type(new ql::Argentina(ql::Argentina::Market::Merval));
			}
			else if (tag == CalendarTag::Australia)
			{
				ptr = ptr_type(new ql::Australia());
			}
			else if (tag == CalendarTag::Brazil || tag == CalendarTag::Brazil_Settlement)
			{
				ptr = ptr_type(new ql::Brazil(ql::Brazil::Market::Settlement));
			}
			else if (tag == CalendarTag::Brazil_Exchange)
			{
				ptr = ptr_type(new ql::Brazil(ql::Brazil::Market::Exchange));
			}
			else if (tag == CalendarTag::Canada || tag == CalendarTag::Canada_Settlement)
			{
				ptr = ptr_type(new ql::Canada(ql::Canada::Market::Settlement));
			}
			else if (tag == CalendarTag::Canada_TSX)
			{
				ptr = ptr_type(new ql::Canada(ql::Canada::Market::TSX));
			}
			else if (tag == CalendarTag::China || tag == CalendarTag::China_SSE)
			{
				ptr = ptr_type(new ql::China(ql::China::Market::SSE));
			}
			else if (tag == CalendarTag::CzechRepublic || tag == CalendarTag::CzechRepublic_PSE)
			{
				ptr = ptr_type(new ql::CzechRepublic(ql::CzechRepublic::Market::PSE));
			}
			else if (tag == CalendarTag::Denmark)
			{
				ptr = ptr_type(new ql::Denmark());
			}
			else if (tag == CalendarTag::Finland)
			{
				ptr = ptr_type(new ql::Finland());
			}
			else if (tag == CalendarTag::Germany || tag == CalendarTag::Germany_FrankfurtStockExchange)
			{
				ptr = ptr_type(new ql::Germany(ql::Germany::Market::FrankfurtStockExchange));
			}
			else if (tag == CalendarTag::Germany_Settlement)
			{
				ptr = ptr_type(new ql::Germany(ql::Germany::Market::Settlement));
			}
			else if (tag == CalendarTag::Germany_Xetra)
			{
				ptr = ptr_type(new ql::Germany(ql::Germany::Market::Xetra));
			}
			else if (tag == CalendarTag::Germany_Eurex)
			{
				ptr = ptr_type(new ql::Germany(ql::Germany::Market::Eurex));
			}
			else if (tag == CalendarTag::Germany_Euwax)
			{
				ptr = ptr_type(new ql::Germany(ql::Germany::Market::Euwax));
			}
			else if (tag == CalendarTag::HongKong || tag == CalendarTag::HongKong_HKEx)
			{
				ptr = ptr_type(new ql::HongKong(ql::HongKong::Market::HKEx));
			}
			else if (tag == CalendarTag::Hungary)
			{
				ptr = ptr_type(new ql::Hungary());
			}
			else if (tag == CalendarTag::Iceland || tag == CalendarTag::Iceland_ICEX)
			{
				ptr = ptr_type(new ql::Iceland(ql::Iceland::Market::ICEX));
			}
			else if (tag == CalendarTag::India || tag == CalendarTag::India_NSE)
			{
				ptr = ptr_type(new ql::India(ql::India::Market::NSE));
			}
			else if (tag == CalendarTag::Indonesia || tag == CalendarTag::Indonesia_IDX)
			{
				ptr = ptr_type(new ql::Indonesia(ql::Indonesia::Market::IDX));
			}
			else if (tag == CalendarTag::Indonesia_BEJ)
			{
				ptr = ptr_type(new ql::Indonesia(ql::Indonesia::Market::BEJ));
			}
			else if (tag == CalendarTag::Indonesia_JSX)
			{
				ptr = ptr_type(new ql::Indonesia(ql::Indonesia::Market::JSX));
			}
			else if (tag == CalendarTag::Italy || tag == CalendarTag::Italy_Settlement)
			{
				ptr = ptr_type(new ql::Italy(ql::Italy::Market::Settlement));
			}
			else if (tag == CalendarTag::Italy_Exchange)
			{
				ptr = ptr_type(new ql::Italy(ql::Italy::Market::Exchange));
			}
			else if (tag == CalendarTag::Japan)
			{
				ptr = ptr_type(new ql::Japan());
			}
			else if (tag == CalendarTag::Mexico || tag == CalendarTag::Mexico_BMV)
			{
				ptr = ptr_type(new ql::Mexico(ql::Mexico::Market::BMV));
			}
			else if (tag == CalendarTag::NewZealand)
			{
				ptr = ptr_type(new ql::NewZealand());
			}
			else if (tag == CalendarTag::Norway)
			{
				ptr = ptr_type(new ql::Norway());
			}
			else if (tag == CalendarTag::Poland)
			{
				ptr = ptr_type(new ql::Poland());
			}
			else if (tag == CalendarTag::Russia)
			{
				ptr = ptr_type(new ql::Russia());
			}
			else if (tag == CalendarTag::SaudiArabia || tag == CalendarTag::SaudiArabia_Tadawul)
			{
				ptr = ptr_type(new ql::SaudiArabia(ql::SaudiArabia::Market::Tadawul));
			}
			else if (tag == CalendarTag::Singapore || tag == CalendarTag::Singapore_SGX)
			{
				ptr = ptr_type(new ql::Singapore(ql::Singapore::Market::SGX));
			}
			else if (tag == CalendarTag::Slovakia || tag == CalendarTag::Slovakia_BSSE)
			{
				ptr = ptr_type(new ql::Slovakia(ql::Slovakia::Market::BSSE));
			}
			else if (tag == CalendarTag::SouthAfrica)
			{
				ptr = ptr_type(new ql::SouthAfrica());
			}
			else if (tag == CalendarTag::Sweden)
			{
				ptr = ptr_type(new ql::Sweden());
			}
			else if (tag == CalendarTag::Switzerland)
			{
				ptr = ptr_type(new ql::Switzerland());
			}
			else if (tag == CalendarTag::Taiwan || tag == CalendarTag::Taiwan_TSEC)
			{
				ptr = ptr_type(new ql::Taiwan(ql::Taiwan::Market::TSEC));
			}
			else if (tag == CalendarTag::Turkey)
			{
				ptr = ptr_type(new ql::Turkey());
			}
			else if (tag == CalendarTag::Ukraine || tag == CalendarTag::Ukraine_USE)
			{
				ptr = ptr_type(new ql::Ukraine(ql::Ukraine::Market::USE));
			}
			else if (tag == CalendarTag::UnitedKingdom || tag == CalendarTag::UnitedKingdom_Settlement)
			{
				ptr = ptr_type(new ql::UnitedKingdom(ql::UnitedKingdom::Market::Settlement));
			}
			else if (tag == CalendarTag::UnitedKingdom_Exchange)
			{
				ptr = ptr_type(new ql::UnitedKingdom(ql::UnitedKingdom::Market::Exchange));
			}
			else if (tag == CalendarTag::UnitedKingdom_Metals)
			{
				ptr = ptr_type(new ql::UnitedKingdom(ql::UnitedKingdom::Market::Metals));
			}
			else
			{
				ptr = ptr_type();
			}

			return ptr;
		}
	}
}

#endif // !fre_quantlib_calendar_manager_hpp
