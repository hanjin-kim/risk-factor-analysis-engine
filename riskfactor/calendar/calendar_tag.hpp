#ifndef fre_riskfactor_calendar_tag_hpp
#define fre_riskfactor_calendar_tag_hpp

#include <map>

#include <riskfactor/types.hpp>

namespace fre
{
	namespace riskfactor
	{
		enum class CalendarTag
		{
			SouthKorea,
			SouthKorea_Settlement,
			SouthKorea_KRX,

			UnitedStates,
			UnitedStates_Settlement,
			UnitedStates_NYSE,
			UnitedStates_GovernmentBond,
			UnitedStates_NERC,

			Argentina,
			Argentina_Merval,

			Australia,

			Brazil,
			Brazil_Settlement,
			Brazil_Exchange,

			Canada,
			Canada_Settlement,
			Canada_TSX,

			China,
			China_SSE,

			CzechRepublic,
			CzechRepublic_PSE,

			Denmark,

			Finland,

			Germany,
			Germany_FrankfurtStockExchange,
			Germany_Settlement,
			Germany_Xetra,
			Germany_Eurex,
			Germany_Euwax,

			HongKong,
			HongKong_HKEx,

			Hungary,

			Iceland,
			Iceland_ICEX,

			India,
			India_NSE,

			Indonesia,
			Indonesia_IDX,
			Indonesia_BEJ,
			Indonesia_JSX,

			Italy,
			Italy_Settlement,
			Italy_Exchange,

			Japan,

			Mexico,
			Mexico_BMV,

			NewZealand,

			Norway,

			Poland,

			Russia,

			SaudiArabia,
			SaudiArabia_Tadawul,

			Singapore,
			Singapore_SGX,

			Slovakia,
			Slovakia_BSSE,

			SouthAfrica,

			Sweden,

			Switzerland,

			Taiwan,
			Taiwan_TSEC,

			Turkey,

			Ukraine,
			Ukraine_USE,

			UnitedKingdom,
			UnitedKingdom_Settlement,
			UnitedKingdom_Exchange,
			UnitedKingdom_Metals,
		};

		static std::map<CalendarTag, String> CalendarTagToString =
		{
			// 일괄적인 아카이브 관리를 위해서, Factory 조건문에 따라서 작성
			// SouthKorea나 KRX 나 같은 켈린더임
			{ CalendarTag::SouthKorea, "SouthKorea_KRX" },
			{ CalendarTag::SouthKorea_Settlement, "SouthKorea_Settlement" },
			{ CalendarTag::SouthKorea_KRX, "SouthKorea_KRX" },

			{ CalendarTag::UnitedStates, "UnitedStates_Settlement" },
			{ CalendarTag::UnitedStates_Settlement, "UnitedStates_Settlement" },
			{ CalendarTag::UnitedStates_NYSE, "UnitedStates_NYSE" },
			{ CalendarTag::UnitedStates_GovernmentBond, "UnitedStates_GovernmentBond" },
			{ CalendarTag::UnitedStates_NERC, "UnitedStates_NERC" },

			{ CalendarTag::Argentina, "Argentina_Merval" },
			{ CalendarTag::Argentina_Merval, "Argentina_Merval" },

			{ CalendarTag::Australia, "Australia" },

			{ CalendarTag::Brazil, "Brazil_Settlement" },
			{ CalendarTag::Brazil_Settlement, "Brazil_Settlement" },
			{ CalendarTag::Brazil_Exchange, "Brazil_Exchange" },

			{ CalendarTag::Canada, "Canada_Settlement" },
			{ CalendarTag::Canada_Settlement, "Canada_Settlement" },
			{ CalendarTag::Canada_TSX, "Canada_TSX" },

			{ CalendarTag::China, "China_SSE" },
			{ CalendarTag::China_SSE, "China_SSE" },

			{ CalendarTag::CzechRepublic, "CzechRepublic_PSE" },
			{ CalendarTag::CzechRepublic_PSE, "CzechRepublic_PSE" },

			{ CalendarTag::Denmark, "Denmark" },

			{ CalendarTag::Finland, "Finland" },

			{ CalendarTag::Germany, "Germany_FrankfurtStockExchange" },
			{ CalendarTag::Germany_FrankfurtStockExchange, "Germany_FrankfurtStockExchange" },
			{ CalendarTag::Germany_Settlement, "Germany_Settlement" },
			{ CalendarTag::Germany_Xetra, "Germany_Xetra" },
			{ CalendarTag::Germany_Eurex, "Germany_Eurex" },
			{ CalendarTag::Germany_Euwax, "Germany_Euwax" },

			{ CalendarTag::HongKong, "HongKong_HKEx" },
			{ CalendarTag::HongKong_HKEx, "HongKong_HKEx" },

			{ CalendarTag::Hungary, "Hungary" },

			{ CalendarTag::Iceland, "Iceland_ICEX" },
			{ CalendarTag::Iceland_ICEX, "iceland_ICEX" },

			{ CalendarTag::India, "India_NSE" },
			{ CalendarTag::India_NSE, "India_NSE" } ,

			{ CalendarTag::Indonesia, "Indonesia_IDX" },
			{ CalendarTag::Indonesia_IDX, "Indonesia_IDX" },
			{ CalendarTag::Indonesia_BEJ, "Indonesia_BEJ" },
			{ CalendarTag::Indonesia_JSX, "Indonesia_JSX" },

			{ CalendarTag::Italy, "Italy_Settlement" },
			{ CalendarTag::Italy_Settlement, "Italy_Settlement" },
			{ CalendarTag::Italy_Exchange, "Italy_Exchange" },

			{ CalendarTag::Japan, "Japan" },

			{ CalendarTag::Mexico, "Mexico_BMV" },
			{ CalendarTag::Mexico_BMV, "Mexico_BMV" },

			{ CalendarTag::NewZealand, "NewZealand" },

			{ CalendarTag::Norway, "Norway" },

			{ CalendarTag::Poland, "Poland" },

			{ CalendarTag::Russia, "Russia" },

			{ CalendarTag::SaudiArabia, "SaudiArabia_Tadawul" },
			{ CalendarTag::SaudiArabia_Tadawul, "SaudiArabia_Tadawul" },

			{ CalendarTag::Singapore, "Singapore_SGX" },
			{ CalendarTag::Singapore_SGX, "Singapore_SGX" },

			{ CalendarTag::Slovakia, "Slovakia_BSSE" },
			{ CalendarTag::Slovakia_BSSE, "Slovakia_BSSE" },

			{ CalendarTag::SouthAfrica, "SouthAfrica" },

			{ CalendarTag::Sweden, "Sweden" },

			{ CalendarTag::Switzerland, "Switzerland" },

			{ CalendarTag::Taiwan, "Taiwan_TSEC" },
			{ CalendarTag::Taiwan_TSEC, "Taiwan_TSEC" },

			{ CalendarTag::Turkey, "Turkey" },

			{ CalendarTag::Ukraine, "Ukraine_USE" },
			{ CalendarTag::Ukraine_USE, "Ukraine_USE" },

			{ CalendarTag::UnitedKingdom, "UnitedKingdom_Settlement" },
			{ CalendarTag::UnitedKingdom_Settlement, "UnitedKingdom_Settlement" },
			{ CalendarTag::UnitedKingdom_Exchange, "UnitedKingdom_Exchange" },
			{ CalendarTag::UnitedKingdom_Metals, "UnitedKingdom_Metals" },
		};

		static std::map<String, CalendarTag> StringToCalendarTag =
		{
			{ "SouthKorea", CalendarTag::SouthKorea },
			{ "SouthKorea_Settlement", CalendarTag::SouthKorea_Settlement },
			{ "SouthKorea_KRX", CalendarTag::SouthKorea_KRX },

			{ "UnitedStates", CalendarTag::UnitedStates },
			{ "UnitedStates_Settlement", CalendarTag::UnitedStates_Settlement },
			{ "UnitedStates_NYSE", CalendarTag::UnitedStates_NYSE },
			{ "UnitedStates_GovernmentBond", CalendarTag::UnitedStates_GovernmentBond },
			{ "UnitedStates_NERC", CalendarTag::UnitedStates_NERC },

			{ "Argentina", CalendarTag::Argentina },
			{ "Argentina_Merval", CalendarTag::Argentina_Merval },

			{ "Australia", CalendarTag::Australia },

			{ "Brazil", CalendarTag::Brazil },
			{ "Brazil_Settlement", CalendarTag::Brazil_Settlement },
			{ "Brazil_Exchange", CalendarTag::Brazil_Exchange },

			{ "Canada", CalendarTag::Canada },
			{ "Canada_Settlement", CalendarTag::Canada_Settlement },
			{ "Canada_TSX", CalendarTag::Canada_TSX },

			{ "China", CalendarTag::China },
			{ "China_SSE", CalendarTag::China_SSE },

			{ "CzechRepublic", CalendarTag::CzechRepublic },
			{ "CzechRepublic_PSE", CalendarTag::CzechRepublic_PSE },

			{ "Denmark", CalendarTag::Denmark },

			{ "Finland", CalendarTag::Finland },

			{ "Germany", CalendarTag::Germany },
			{ "Germany_FrankfurtStockExchange", CalendarTag::Germany_FrankfurtStockExchange },
			{ "Germany_Settlement", CalendarTag::Germany_Settlement },
			{ "Germany_Xetra", CalendarTag::Germany_Xetra },
			{ "Germany_Eurex", CalendarTag::Germany_Eurex },
			{ "Germany_Euwax", CalendarTag::Germany_Euwax },

			{ "HongKong", CalendarTag::HongKong },
			{ "HongKong_HKEx", CalendarTag::HongKong_HKEx },

			{ "Hungary", CalendarTag::Hungary },

			{ "Iceland", CalendarTag::Iceland },
			{ "Iceland_ICEX", CalendarTag::Iceland_ICEX },

			{ "India", CalendarTag::India },
			{ "India_NSE", CalendarTag::India_NSE },

			{ "Indonesia", CalendarTag::Indonesia },
			{ "Indonesia_IDX", CalendarTag::Indonesia_IDX },
			{ "Indonesia_BEJ", CalendarTag::Indonesia_BEJ },
			{ "Indonesia_JSX", CalendarTag::Indonesia_JSX },

			{ "Italy", CalendarTag::Italy },
			{ "Italy_Settlement", CalendarTag::Italy_Settlement },
			{ "Italy_Exchange", CalendarTag::Italy_Exchange },

			{ "Japan", CalendarTag::Japan },

			{ "Mexico", CalendarTag::Mexico },
			{ "Mexico_BMV", CalendarTag::Mexico_BMV },

			{ "NewZealand", CalendarTag::NewZealand },

			{ "Norway", CalendarTag::Norway },

			{ "Poland", CalendarTag::Poland },

			{ "Russia", CalendarTag::Russia },

			{ "SaudiArabia", CalendarTag::SaudiArabia },
			{ "SaudiArabia_Tadawul", CalendarTag::SaudiArabia_Tadawul },

			{ "Singapore", CalendarTag::Singapore },
			{ "Singapore_SGX", CalendarTag::Singapore_SGX },

			{ "Slovakia", CalendarTag::Slovakia },
			{ "Slovakia_BSSE", CalendarTag::Slovakia_BSSE },

			{ "SouthAfrica", CalendarTag::SouthAfrica },

			{ "Sweden", CalendarTag::Sweden },

			{ "Switzerland", CalendarTag::Switzerland },

			{ "Taiwan", CalendarTag::Taiwan },
			{ "Taiwan_TSEC", CalendarTag::Taiwan_TSEC },

			{ "Turkey", CalendarTag::Turkey },

			{ "Ukraine", CalendarTag::Ukraine },
			{ "Ukraine_USE", CalendarTag::Ukraine_USE },

			{ "UnitedKingdom", CalendarTag::UnitedKingdom },
			{ "UnitedKingdom_Settlement", CalendarTag::UnitedKingdom_Settlement },
			{ "UnitedKingdom_Exchange", CalendarTag::UnitedKingdom_Exchange },
			{ "UnitedKingdom_Metals", CalendarTag::UnitedKingdom_Metals },
		};
	}
}

#endif // !fre_riskfactor_calendar_tag_hpp