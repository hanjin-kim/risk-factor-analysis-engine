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
			주식의 가격으로부터 일일 수익률을 계산하기 위해 RiskFactor 에서 파생된 클래스입니다.
			Insert() 는 가격-수익률 변환을 위해 오버라이드 됩니다.
		*/
		class EquityPrice : public RiskFactor
		{
		public :
			/// 생성자
			EquityPrice(const Name& name, const Desc& desc, const CalendarTag& cal_tag, const Size size = 250);
			/// 소멸자
			virtual ~EquityPrice() {};

			typedef std::shared_ptr<EquityPrice> Ptr;
			typedef std::weak_ptr<EquityPrice> WPtr;
			typedef std::unique_ptr<EquityPrice> UPtr;

			/*!
				\brief 주식의 가격을 입력하는 함수. 

				가격은 가격 컨테이너에 별도로 저장됩니다.
				최조 입력시에는 수익률이 계산되지 않습니다.
				이후 입력된 가격은 일일 수익률을 계산하여 RiskFactor::Insert() 를 통해 저장됩니다.
			*/
			virtual void Insert(const Date&, const Price&) override;

			/// 특정일의 주식 가격을 반환하는 함수.
			Price GetPrice(const Date&);

		protected :
			/// shared_ptr 아카이브를 위한 기본 생성자, 아무것도 안함
			EquityPrice() {}

		private :
			/// 가격 시계열 데이터를 저장하는 컨태이너. RiskFactor 의 컨테이너와 별도로 관리됨.
			TimeSeries<Price> price_series;

			typedef std::pair<Date, Price> price_series_type;

			friend class ::boost::serialization::access;

			template <class Archive>
			void serialize(Archive& ar, const unsigned int version);
		};

		/// inline 정의
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
