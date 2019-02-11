#include <riskfactor/series_object.hpp>
#include <riskfactor/date.hpp>
#include <riskfactor/easylogging++/easylogging++.h>


namespace fre
{
	namespace riskfactor
	{
		SeriesObject::SeriesObject(const Size& size)
			: max_size(size)
		{}

		Data SeriesObject::Get(const Date& d)
		{
			// find 쓸 경우 const 사용할 수 없다?
			auto it = series.find(d);

			if (it == series.end())
				return Data();

			return it->second;
		}

		SeriesObject::const_iterator SeriesObject::begin() const { return series.begin(); }
		SeriesObject::const_iterator SeriesObject::end() const { return series.end(); }
		SeriesObject::const_reverse_iterator SeriesObject::rbegin() const { return series.rbegin(); }
		SeriesObject::const_reverse_iterator SeriesObject::rend() const { return series.rend(); }

		template <class Archive>
		void SeriesObject::serialize(Archive& ar, const unsigned int version)
		{
			ar & BOOST_SERIALIZATION_NVP(series);
			ar & BOOST_SERIALIZATION_NVP(max_size);
		}
	}
}


#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>

template void fre::riskfactor::SeriesObject::serialize(boost::archive::xml_oarchive & ar, const unsigned int version);
template void fre::riskfactor::SeriesObject::serialize(boost::archive::xml_iarchive & ar, const unsigned int version);