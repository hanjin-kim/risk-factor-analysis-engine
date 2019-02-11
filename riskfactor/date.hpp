/*!
 *\file date.hpp
 *\author Hanjin Kim
 *\date 2017 May 27th
 *\breif A wrapper class for QuantLib::Date
 *
 *This class has an additional constructor with 3 integer argument
 *which correspond to day, month, and year, respectively.
 *the month integer is converted into QuantLib::Month enum value.
 *All the public methods and operators are inherited
 *so one can use this class as much like as QuantLib::Date.
 *Conversion from Date to QuantLib::Date is implemented implicitly.
*/

#ifndef fre_riskfactor_date_hpp
#define fre_riskfactor_date_hpp

#include <iostream>

#include <set>

#include <boost/serialization/access.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/set.hpp>

#include <ql/time/date.hpp>

namespace fre
{
	namespace riskfactor
	{
		class Date : public QuantLib::Date
		{
		public:
			Date() : ::QuantLib::Date() {};
			Date(const int& day, const int& month, const int& year)
				: ::QuantLib::Date(day, ::QuantLib::Month(month), year)
			{}
			Date(const int& day, const ::QuantLib::Month& month, const int& year)
				: ::QuantLib::Date(day, month, year)
			{}
			Date(const serial_type& serial)
				: ::QuantLib::Date(serial)
			{}

			Date(const Date& date)
				: ::QuantLib::Date(date)
			{}


			Date(const ::QuantLib::Date& date)
				: ::QuantLib::Date(date)
			{}

			typedef ::QuantLib::Date::serial_type serial_type;
			typedef std::set<Date> Set;

			//! increments date by the given number of days
			Date& operator+=(const serial_type days);
			//! decrement date by the given number of days
			Date& operator-=(const serial_type days);
			//! returns a new date incremented by the given number of days
			Date operator+(const serial_type days) const;
			//! returns a new date decremented by the given number of days
			Date operator-(const serial_type days) const;

			Date& operator=(const ::QuantLib::Date& d);

		private:
			friend class boost::serialization::access;

			template <class Archive>
			void save(Archive& ar, const unsigned int version) const
			{
				::QuantLib::Date::serial_type serial_number = this->serialNumber();
				ar & boost::serialization::make_nvp("date_serial", serial_number);
			}

			template <class Archive>
			void load(Archive& ar, const unsigned int version)
			{
				::QuantLib::Date::serial_type serial_number;
				ar & boost::serialization::make_nvp("date_serial", serial_number);
				
				*this += serial_number;				
			}

			BOOST_SERIALIZATION_SPLIT_MEMBER()
		};
	}
}

#endif // !pyre_date_hpp
