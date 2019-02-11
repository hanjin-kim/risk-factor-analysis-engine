#ifndef fre_riskfactor_data_hpp
#define fre_riskfactor_data_hpp

#include <math.h>
#include <limits>
#include <iostream>

#include <boost/serialization/access.hpp>
#include <boost/serialization/nvp.hpp>

#include <riskfactor/types.hpp>

namespace fre
{
	namespace riskfactor
	{
		/*
		class Data
		{
			double value;

		public :
			Data() : value(std::numeric_limits<double>::quiet_NaN()) {};
			Data(const double v) : value(v) {};
			Data(const Data& d) : value(d.GetValue()) {};
			virtual ~Data() {};

			double GetValue() const { return value; }

			operator Size() const { return Size(value); }

			Data& operator+=(const Data& rhs)
			{
				this->value += rhs.GetValue();
				return *this;
			}
			Data& operator-=(const Data& rhs)
			{
				this->value -= rhs.GetValue();
				return *this;
			}
			Data& operator*=(const Data& rhs)
			{
				this->value *= rhs.GetValue();
				return *this;
			}

			Data& operator*=(const double rhs)
			{
				this->value *= rhs;
				return *this;
			}

			Data& operator/=(const Data& rhs)
			{
				this->value /= rhs.GetValue();
				return *this;
			}

			friend std::ostream& operator<<(std::ostream& os, const Data& dt)
			{
				os << dt.GetValue();
				return os;
			}

		private :
			friend class ::boost::serialization::access;

			template <class Archive>
			void serialize(Archive& ar, const unsigned int version)
			{
				ar & BOOST_SERIALIZATION_NVP(value);
			}
		};

		inline Data operator+(const Data& lhs, const Data& rhs)
		{
			return Data(lhs.GetValue() + rhs.GetValue());
		}

		inline Data operator-(const Data& lhs, const Data& rhs)
		{
			return Data(lhs.GetValue() - rhs.GetValue());
		}

		inline Data operator*(const Data& lhs, const Data& rhs)
		{
			return Data(lhs.GetValue() * rhs.GetValue());
		}

		inline Data operator/(const Data& lhs, const Data& rhs)
		{
			return Data(lhs.GetValue() / rhs.GetValue());
		}

		inline Data operator+(const Data& lhs, const double& rhs)
		{
			return Data(lhs.GetValue() + rhs);
		}

		inline Data operator-(const Data& lhs, const double& rhs)
		{
			return Data(lhs.GetValue() - rhs);
		}

		inline Data operator*(const Data& lhs, const double& rhs)
		{
			return Data(lhs.GetValue() * rhs);
		}

		inline Data operator/(const Data& lhs, const double& rhs)
		{
			return Data(lhs.GetValue() / rhs);
		}
		
		inline Data operator/(const Data& lhs, const double rhs)
		{
			return Data(lhs.GetValue() / rhs);
		}
		
		inline Data operator+(const double lhs, const Data& rhs)
		{
			return Data(lhs + rhs.GetValue());
		}

		inline Data operator-(const double lhs, const Data& rhs)
		{
			return Data(lhs - rhs.GetValue());
		}

		inline Data operator*(const double lhs, const Data& rhs)
		{
			return Data(lhs * rhs.GetValue());
		}

		inline Data operator/(const double lhs, const Data& rhs)
		{
			return Data(lhs / rhs.GetValue());
		}

		inline Data operator/(const Size lhs, const Data& rhs)
		{
			return Data(double(lhs) / rhs.GetValue());
		}

		// DATA static arithmatics
		inline static Data Log(const Data& dat)
		{
			double logval = ::log(dat.GetValue());

			return Data(logval);
		}

		inline static Data Sqrt(const Data& dat)
		{
			double sqrtval = ::sqrt(dat.GetValue());

			return Data(sqrtval);
		}		

		inline static bool Isnan(const Data& dat)
		{
			return std::isnan(dat.GetValue());
		}

		inline static bool Isinf(const Data& dat)
		{
			return std::isinf(dat.GetValue());
		}

		namespace Eigen
		{
			namespace fr = ::fre::riskfactor;

			inline static fr::Data log10(const fr::Data& dat)
			{
				return fr::Data(::log10(dat.GetValue()));
			}
		}
*/
	}
}

#endif // !fre_riskfactor_data_hpp
