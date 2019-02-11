#include <boost/serialization/nvp.hpp>

#include <riskfactor/risk_factor/equity_price.hpp>
#include <riskfactor/managers/calendar_manager.hpp>
#include <riskfactor/easylogging++/easylogging++.h>

namespace fre
{
	namespace riskfactor
	{
		EquityPrice::EquityPrice(const Name& name, const Desc& desc, const CalendarTag& cal_tag, const Size size)
			: RiskFactor(name, desc, cal_tag, size)
		{
			LOG(DEBUG) << "\nStockPrice constructed" << "\n";
		}

		void EquityPrice::Insert(const Date& date, const Price& price)
		{
			Calendar::Ptr calendar = GetCalendar();

			if (!calendar->isBusinessDay(date))
			{
				LOG(DEBUG) << "The date provided, " << date << ", is not a business day" << std::endl;
				return;
			}

			if (!price_series.empty())
			{
				const price_series_type& prev_pair = *(price_series.rbegin());

				Date prev_date = prev_pair.first;
				Price prev_price = prev_pair.second;

				if (calendar->adjust(prev_date + 1) != date)
				{
					LOG(DEBUG) << "The date provided, " << date << ", is not succeeding the last business day,"
						<< prev_date << std::endl;
					return;
				}

				Data y = log(price / prev_price);
				if (isnan(y))
				{
					LOG(DEBUG) << "NaN value detected for the log return. Aborted." << std::endl;
				}

				RiskFactor::Insert(date, y);
			}

			if (price_series.size() == GetNMax())
			{
				VLOG(1) << "Exceeding container limit = " << GetNMax() << ". Erasing the oldest data." << std::endl;
				price_series.erase(price_series.begin());
			}

			price_series.insert(std::make_pair(date, price));
		}

		template <class Archive>
		void EquityPrice::serialize(Archive& ar, const unsigned int version)
		{
			ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(RiskFactor);
			ar & BOOST_SERIALIZATION_NVP(price_series);
		}
	}
}

BOOST_CLASS_EXPORT_IMPLEMENT(fre::riskfactor::EquityPrice)

#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>

template void fre::riskfactor::EquityPrice::serialize(boost::archive::xml_oarchive & ar, const unsigned int version);
template void fre::riskfactor::EquityPrice::serialize(boost::archive::xml_iarchive & ar, const unsigned int version);