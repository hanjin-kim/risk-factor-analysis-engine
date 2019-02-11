#ifndef fre_riskfactor_equity_price_hpp
#define fre_riskfactor_equity_price_hpp

#include <memory>

#include <boost/serialization/access.hpp>
#include <boost/serialization/export.hpp>

#include <riskfactor/risk_factor.hpp>

namespace fre
{
	namespace riskfactor
	{
		typedef Data Price;
		/*!
			�ֽ��� �������κ��� ���� ���ͷ��� ����ϱ� ���� RiskFactor ���� �Ļ��� Ŭ�����Դϴ�.
			Insert() �� ����-���ͷ� ��ȯ�� ���� �������̵� �˴ϴ�.
		*/
		class EquityPrice : public RiskFactor
		{
		public :
			/// ������
			EquityPrice(const Name& name, const Desc& desc, const CalendarTag& cal_tag, const Size size = 250);
			/// �Ҹ���
			virtual ~EquityPrice() {};

			typedef std::shared_ptr<EquityPrice> Ptr;
			typedef std::weak_ptr<EquityPrice> WPtr;
			typedef std::unique_ptr<EquityPrice> UPtr;

			/*!
				\brief �ֽ��� ������ �Է��ϴ� �Լ�. 

				������ ���� �����̳ʿ� ������ ����˴ϴ�.
				���� �Է½ÿ��� ���ͷ��� ������ �ʽ��ϴ�.
				���� �Էµ� ������ ���� ���ͷ��� ����Ͽ� RiskFactor::Insert() �� ���� ����˴ϴ�.
			*/
			virtual void Insert(const Date&, const Price&) override;

			/// Ư������ �ֽ� ������ ��ȯ�ϴ� �Լ�.
			Price GetPrice(const Date&);

		protected :
			/// shared_ptr ��ī�̺긦 ���� �⺻ ������, �ƹ��͵� ����
			EquityPrice() {}

		private :
			/// ���� �ð迭 �����͸� �����ϴ� �����̳�. RiskFactor �� �����̳ʿ� ������ ������.
			TimeSeries<Price> price_series;

			typedef std::pair<Date, Price> price_series_type;

			friend class ::boost::serialization::access;

			template <class Archive>
			void serialize(Archive& ar, const unsigned int version);
		};

		/// inline ����
		inline Price EquityPrice::GetPrice(const Date& date)
		{
			auto it = price_series.find(date);
			if (it == price_series.end())
				return Data();

			return it->second;
		}
	}
}

BOOST_CLASS_EXPORT_KEY(fre::riskfactor::EquityPrice)

#endif // !fre_riskfactor_equity_price.hpp
