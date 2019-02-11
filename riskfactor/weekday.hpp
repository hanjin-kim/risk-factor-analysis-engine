#ifndef fre_riskfactor_weekday_hpp
#define fre_riskfactor_weekday_hpp

namespace fre
{
	namespace riskfactor
	{
		/*! Day's serial number MOD 7;
		WEEKDAY Excel function is the same except for Sunday = 7.

		\ingroup datetime
		*/
		enum Weekday {
			Sunday = 1,
			Monday = 2,
			Tuesday = 3,
			Wednesday = 4,
			Thursday = 5,
			Friday = 6,
			Saturday = 7,
			Sun = 1,
			Mon = 2,
			Tue = 3,
			Wed = 4,
			Thu = 5,
			Fri = 6,
			Sat = 7
		};

		/*! \relates Weekday */
		std::ostream& operator<<(std::ostream&, const Weekday&);

		namespace detail {

			struct long_weekday_holder {
				long_weekday_holder(Weekday d) : d(d) {}
				Weekday d;
			};
			std::ostream& operator<<(std::ostream&, const long_weekday_holder&);

			struct short_weekday_holder {
				short_weekday_holder(Weekday d) : d(d) {}
				Weekday d;
			};
			std::ostream& operator<<(std::ostream&, const short_weekday_holder&);

			struct shortest_weekday_holder {
				shortest_weekday_holder(Weekday d) : d(d) {}
				Weekday d;
			};
			std::ostream& operator<<(std::ostream&,
				const shortest_weekday_holder&);

		}

		namespace io {

			//! output weekdays in long format
			/*! \ingroup manips */
			detail::long_weekday_holder long_weekday(Weekday);

			//! output weekdays in short format (three letters)
			/*! \ingroup manips */
			detail::short_weekday_holder short_weekday(Weekday);

			//! output weekdays in shortest format (two letters)
			/*! \ingroup manips */
			detail::shortest_weekday_holder shortest_weekday(Weekday);

		}

	}
}
#endif // !fre_riskfactor_weekday_hpp
