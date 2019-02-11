#include <boost/serialization/nvp.hpp>

#include <riskfactor/risk_factor/bond_yield.hpp>
#include <riskfactor/managers/calendar_manager.hpp>
#include <riskfactor/easylogging++/easylogging++.h>

namespace fre
{
	namespace riskfactor
	{
		BondYield::BondYield(const Name& name, const Desc& desc, const Duration& dur, const CalendarTag& cal_tag, const Size size)
			: RiskFactor(name, desc, cal_tag, size), duration(dur)
		{
			LOG(DEBUG) << "\nStockPrice constructed" << "\n";
		}

		void BondYield::Insert(const Date& date, const Yield& y)
		{
			Calendar::Ptr calendar = GetCalendar();

			if (!calendar->isBusinessDay(date))
			{
				LOG(DEBUG) << "The date provided, " << date << ", is not a business day" << std::endl;
				return;
			}

			if (!yield_series.empty())
			{
				const yield_series_type& prev_pair = *(yield_series.rbegin());

				Date prev_date = prev_pair.first;
				Yield prev_y = prev_pair.second;

				if (calendar->adjust(prev_date + 1) != date)
				{
					LOG(DEBUG) << "The date provided, " << date << ", is not succeeding the last business day,"
						<< prev_date << std::endl;
					return;
				}

				Data z = log(y / prev_y);
				
				if (isnan(z))
				{
					if (abs(prev_y - y) < 1.0E-20)
					{
						z = 0;
					}
					else
					{
						LOG(DEBUG) << "NaN value returend. Aborted." << std::endl;
						return;
					}
				}

				RiskFactor::Insert(date, z);
			}

			if (yield_series.size() == GetNMax())
			{
				VLOG(1) << "Exceeding container limit = " << GetNMax() << ". Erasing the oldest data." << std::endl;
				yield_series.erase(yield_series.begin());
			}

			yield_series.insert(std::make_pair(date, y));
		}

		template <class Archive>
		void BondYield::serialize(Archive& ar, const unsigned int version)
		{
			ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(RiskFactor);
			ar & BOOST_SERIALIZATION_NVP(yield_series);
		}
	}
}

BOOST_CLASS_EXPORT_IMPLEMENT(fre::riskfactor::BondYield)

#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>

template void fre::riskfactor::BondYield::serialize(boost::archive::xml_oarchive & ar, const unsigned int version);
template void fre::riskfactor::BondYield::serialize(boost::archive::xml_iarchive & ar, const unsigned int version);