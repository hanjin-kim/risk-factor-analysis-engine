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
			/// 생성자
			BondYield(const Name&, const Desc&, const Duration&, const CalendarTag&, const Size = 250);
			/// 소멸자
			virtual ~BondYield() {}

			typedef std::shared_ptr<BondYield> Ptr;
			typedef std::weak_ptr<BondYield> WPtr;
			typedef std::unique_ptr<BondYield> UPtr;

			/*!
			\brief 채권의 수익률을 입력하는 함수.

			수익률은 가격 컨테이너에 별도로 저장됩니다.
			최조 입력시에는 수익률의 변화율이 계산되지 않습니다.
			이후 입력된 가격은 일일 수익률 변화율을 계산하여 RiskFactor::Insert() 를 통해 저장됩니다.
			*/
			virtual void Insert(const Date&, const Yield&) override;

			/// 특정일의 수익률을 변환하는 함수
			Yield GetYield(const Date&);
			Duration GetDuration() const { return duration;  }

		protected :
			/// shared_ptr 아카이브를 위한 기본 생성자, 아무것도 안함
			BondYield() {}

		private :
			/// 가격 시계열 데이터를 저장하는 컨태이너. RiskFactor 의 컨테이너와 별도로 관리됨.
			TimeSeries<Yield> yield_series;

			typedef std::pair<Date, Yield> yield_series_type;

			friend class ::boost::serialization::access;

			template <class Archive>
			void serialize(Archive& ar, const unsigned int version);
		};

		/// inline 정의
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
