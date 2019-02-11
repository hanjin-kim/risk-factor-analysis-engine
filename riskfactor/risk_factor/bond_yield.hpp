#ifndef fre_riskfactor_bond_yield_hpp
#define fre_riskfactor_bond_yield_hpp

#include <limits>

#include <riskfactor/risk_factor.hpp>

namespace fre
{
	namespace riskfactor
	{

		typedef Data Yield;
		typedef Data Duration;

		class BondYield : public RiskFactor
		{
			Duration duration;

		public :
			/// ������
			BondYield(const Name&, const Desc&, const Duration&, const CalendarTag&, const Size = 250);
			/// �Ҹ���
			virtual ~BondYield() {}

			typedef std::shared_ptr<BondYield> Ptr;
			typedef std::weak_ptr<BondYield> WPtr;
			typedef std::unique_ptr<BondYield> UPtr;

			/*!
			\brief ä���� ���ͷ��� �Է��ϴ� �Լ�.

			���ͷ��� ���� �����̳ʿ� ������ ����˴ϴ�.
			���� �Է½ÿ��� ���ͷ��� ��ȭ���� ������ �ʽ��ϴ�.
			���� �Էµ� ������ ���� ���ͷ� ��ȭ���� ����Ͽ� RiskFactor::Insert() �� ���� ����˴ϴ�.
			*/
			virtual void Insert(const Date&, const Yield&) override;

			/// Ư������ ���ͷ��� ��ȯ�ϴ� �Լ�
			Yield GetYield(const Date&);
			Duration GetDuration() const { return duration;  }

		protected :
			/// shared_ptr ��ī�̺긦 ���� �⺻ ������, �ƹ��͵� ����
			BondYield() {}

		private :
			/// ���� �ð迭 �����͸� �����ϴ� �����̳�. RiskFactor �� �����̳ʿ� ������ ������.
			TimeSeries<Yield> yield_series;

			typedef std::pair<Date, Yield> yield_series_type;

			friend class ::boost::serialization::access;

			template <class Archive>
			void serialize(Archive& ar, const unsigned int version);
		};

		/// inline ����
		inline Yield BondYield::GetYield(const Date& date)
		{
			auto it = yield_series.find(date);

			if (it == yield_series.end())
				return std::numeric_limits<Yield>::quiet_NaN();

			return it->second;
		}
	}
}

BOOST_CLASS_EXPORT_KEY(fre::riskfactor::BondYield)

#endif // !fre_riskfactor_bond_yield_hpp
