#include <riskfactor/date.hpp>

namespace fre
{
	namespace riskfactor
	{
		Date& Date::operator+=(const serial_type days)
		{
			this->QuantLib::Date::operator+=(days);

			return *this;
		}

		Date& Date::operator-=(const serial_type days)
		{
			this->QuantLib::Date::operator-=(days);

			return *this;
		}

		Date Date::operator+(const serial_type days) const
		{
			return Date(this->serialNumber() + days);
		}

		Date Date::operator-(const serial_type days) const
		{
			return Date(this->serialNumber() - days);
		}

		Date& Date::operator=(const ::QuantLib::Date& d)
		{
			this->QuantLib::Date::operator=(d);

			return *this;
		}
	}
}