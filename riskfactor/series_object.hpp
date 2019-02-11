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
			/// �ð迭 ������
			TimeSeries<Data> series;
			/// �ð迭 �������� �ִ� ũ��
			Size max_size;

		public:
			/// ������
			explicit SeriesObject(const Size& size);
			/// �Ҹ���
			virtual ~SeriesObject() {}

			/// Ư������ �����͸� ��ȯ�մϴ�.
			Data Get(const Date&);
			/// �ð迭 �������� �ִ� ũ�⸦ ��ȯ�մϴ�.
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
			/// smart pointer ��ī�̺긦 ���� �⺻ ������, �ƹ��͵� ����
			SeriesObject() {}

			/// �⺻ �Է� �Լ�
			void insert(series_value_type v) { series.insert(v); }
			void erase(const_iterator it) { series.erase(it); }

		private:
			/// serialization ������ ���� ������ ����
			friend class ::boost::serialization::access;

			/// serialize �Լ� ����
			template <class Archive>
			void serialize(Archive& ar, const unsigned int version);
		};
	}
}

#endif // !fre_riskfactor_series_object.hpp
