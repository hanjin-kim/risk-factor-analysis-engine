#ifndef fre_riskfactor_time_series_hpp
#define fre_riskfactor_time_series_hpp

#include <vector>
#include <map>

#include <boost/serialization/access.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/map.hpp>

#include <boost/iterator/transform_iterator.hpp>
#include <boost/iterator/reverse_iterator.hpp>
#include <boost/function.hpp>
#include <boost/utility.hpp>

#include <riskfactor/types.hpp>
#include <riskfactor/date.hpp>
namespace fre
{
	namespace riskfactor
	{

		template<typename T>
		class TimeSeries
		{
		protected:
			typedef std::map<Date, T> map_type;
			map_type series;

		public:
			TimeSeries() {};
			virtual ~TimeSeries() {};

			String GetDimension() const { return dimension; }
			Size GetNMax() const { return max_n_sample; }

			Size size() const { return series.size(); }
			bool empty() const { return series.empty(); }

			typedef typename map_type::const_iterator const_iterator;
			typedef typename map_type::const_reverse_iterator const_reverse_iterator;

			const_iterator cbegin() const { return series.begin(); }
			const_iterator cend() const { return series.end(); }
			const_iterator begin() const { return cbegin(); }
			const_iterator end() const { return cend(); }
			const_reverse_iterator crbegin() const {
				return series.rbegin();
			}
			const_reverse_iterator crend() const {
				return series.rend();
			}
			const_reverse_iterator rbegin() const { return crbegin(); }
			const_reverse_iterator rend() const { return crend(); }

			typedef typename map_type::value_type container_value_type;

		private:
			typedef boost::function1<Date, const container_value_type&>
				projection_time;
			typedef boost::function1<T, const container_value_type&>
				projection_value;

		public:
			//! \name Projection iterators
			//@{

			typedef boost::transform_iterator<projection_time, const_iterator>
				const_time_iterator;
			typedef boost::transform_iterator<projection_value, const_iterator>
				const_value_iterator;
			typedef boost::transform_iterator<projection_time,
				const_reverse_iterator>
				const_reverse_time_iterator;
			typedef boost::transform_iterator<projection_value,
				const_reverse_iterator>
				const_reverse_value_iterator;

			const_value_iterator cbegin_values() const {
				return const_value_iterator(cbegin(), get_value);
			}
			const_value_iterator cend_values() const {
				return const_value_iterator(cend(), get_value);
			}
			const_reverse_value_iterator crbegin_values() const {
				return const_reverse_value_iterator(crbegin(), get_value);
			}
			const_reverse_value_iterator crend_values() const {
				return const_reverse_value_iterator(crend(), get_value);
			}

			const_time_iterator cbegin_time() const {
				return const_time_iterator(cbegin(), get_time);
			}
			const_time_iterator cend_time() const {
				return const_time_iterator(cend(), get_time);
			}
			const_reverse_time_iterator crbegin_time() const {
				return const_reverse_time_iterator(crbegin(), get_time);
			}
			const_reverse_time_iterator crend_time() const {
				return const_reverse_time_iterator(crend(), get_time);
			}

			std::vector<Date> dates() const;
			std::vector <T> values() const;

			const_iterator find(const Date&);
			void erase(const const_iterator it);
			void insert(const container_value_type& val);

		private:
			static const Date& get_time(const container_value_type& v) {
				return v.first;
			}
			static const T& get_value(const container_value_type& v) {
				return v.second;
			}

			friend class boost::serialization::access;

			template <class Archive>
			void serialize(Archive& ar, const unsigned int version)
			{
				ar & boost::serialization::make_nvp("daily_data", series);
			}
		};

		template <typename T>
		inline typename TimeSeries<T>::const_iterator TimeSeries<T>::find(const Date& d)
		{
			const_iterator i = series.find(d);
			return i;
		}

		template <typename T>
		inline void TimeSeries<T>::erase(const typename TimeSeries<T>::const_iterator it)
		{
			series.erase(it);
		}

		template <typename T>
		inline void TimeSeries<T>::insert(const typename TimeSeries<T>::container_value_type& val)
		{
			series.insert(val);
		}
	}
}

#endif // !fre_time_series_hpp
#pragma once
