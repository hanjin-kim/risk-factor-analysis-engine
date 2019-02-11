#ifndef fre_riskfactor_risk_factor_hpp
#define fre_riskfactor_risk_factor_hpp

#include <memory>

#include <boost/serialization/access.hpp>
#include <boost/serialization/export.hpp>

#include <riskfactor/series_object.hpp>
#include <riskfactor/calendarical.hpp>
#include <riskfactor/archivable.hpp>

namespace fre {

	namespace riskfactor
	{
		/*!
			위험요인 데이터를 저장하고 처리하기 위한 클래스입니다.
			Named, CalendaricalData 와 Archivable 부터 파생됩니다.
			Insert() 함수를 통해 사용자가 데이터를 입력할 수 있습니다.
			위험요인의 변동성 객체를 참조하여 위험요인 일별 데이터 입력과 동시에 변동성이 계산됩니다.
			날짜별 위험요인 입출력과 변동성 출력을 지원합니다.
		*/
		class RiskFactor : public Named, public SeriesObject, public Calendarical, public Archivable
		{
			/// AverageType 별 변동성 객체 참조를 위한 맵
//			typedef std::map<AverageType, SingleReferenceForecast::ptr> vol_map_type;
//			vol_map_type vol_map;

		public:
			/// CalendarTag 를 활용하는 생성자
			explicit RiskFactor(const Name& name, const Desc& desc, const CalendarTag& cal_tag, const Size size = 250);
			/// Calendar 포인터를 활용하는 생성자
			explicit RiskFactor(const Name&, const Desc&, Calendar::Ptr, const Size size = 250);
			/// 소멸자
			virtual ~RiskFactor() {};

			typedef std::shared_ptr<RiskFactor> Ptr;
			typedef std::weak_ptr<RiskFactor> WPtr;
			typedef std::unique_ptr<RiskFactor> UPtr;

			/// 데이터 입력 함수
			virtual void Insert(const Date&, const Data&);
			/// 변동성 데이터 출력 함수 (AverageType 별)
//			Data GetVolatility(const Date&, const AverageType&);
//			void AddVolatility(const AverageType&);

			virtual void SetArchiveTag(const ArchiveTag&) {};

		protected :
			/// cereal smart pointer 아카이브를 위한 기본 생성자, 아무것도 안함
			RiskFactor() {}

		private:
			/// 변동성 맵 초기화 함수, 향후 기간별(ex. 5일, 2주,...) 변동성 추가 가능성
//			void InitializeMap();

			friend class ::boost::serialization::access;

			template <class Archive>
			void serialize(Archive& ar, const unsigned int version);
		};
	} // namespace riskfactor
	 
} // namespace fre

BOOST_CLASS_EXPORT_KEY(fre::riskfactor::RiskFactor)

#endif // !fre_riskfactor_risk_factor_hpp

