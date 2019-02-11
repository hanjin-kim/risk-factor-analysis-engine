#ifndef fre_riskfactor_series_object_hpp
#define fre_riskfactor_sieries_object_hpp

#include <memory>

#include <boost/serialization/access.hpp>

#include <riskfactor/timeseries.hpp>

namespace fre
{
	namespace riskfactor
	{

		class Date;

		class SeriesObject
		{
			/// 시계열 데이터
			TimeSeries<Data> series;
			/// 시계열 데이터의 최대 크기
			Size max_size;

		public:
			/// 생성자
			explicit SeriesObject(const Size& size);
			/// 소멸자
			virtual ~SeriesObject() {}

			/// 특정일의 데이터를 반환합니다.
			Data Get(const Date&);
			/// 시계열 데이터의 최대 크기를 반환합니다.
			Size GetNMax() const { return max_size; }

			typedef std::shared_ptr<SeriesObject> Ptr;
			typedef std::shared_ptr<const SeriesObject> CPtr;
			typedef std::weak_ptr<SeriesObject> WPtr;
			typedef std::unique_ptr<SeriesObject> UPtr;

			typedef TimeSeries<Data> series_type;
			typedef series_type::container_value_type series_value_type;
			typedef series_type::const_iterator const_iterator;
			typedef series_type::const_reverse_iterator const_reverse_iterator;

			const_iterator begin() const;
			const_iterator end() const;
			const_reverse_iterator rbegin() const;
			const_reverse_iterator rend() const;

			const_iterator find(const Date& d) { return series.find(d); }
			Size size() const { return series.size(); }
			bool empty() const { return series.empty(); }

		protected :
			/// smart pointer 아카이브를 위한 기본 생성자, 아무것도 안함
			SeriesObject() {}

			/// 기본 입력 함수
			void insert(series_value_type v) { series.insert(v); }
			void erase(const_iterator it) { series.erase(it); }

		private:
			/// serialization 지원을 위한 프렌드 선언
			friend class ::boost::serialization::access;

			/// serialize 함수 선언
			template <class Archive>
			void serialize(Archive& ar, const unsigned int version);
		};
	}
}

#endif // !fre_riskfactor_series_object.hpp
