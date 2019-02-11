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
			������� �����͸� �����ϰ� ó���ϱ� ���� Ŭ�����Դϴ�.
			Named, CalendaricalData �� Archivable ���� �Ļ��˴ϴ�.
			Insert() �Լ��� ���� ����ڰ� �����͸� �Է��� �� �ֽ��ϴ�.
			��������� ������ ��ü�� �����Ͽ� ������� �Ϻ� ������ �Է°� ���ÿ� �������� ���˴ϴ�.
			��¥�� ������� ����°� ������ ����� �����մϴ�.
		*/
		class RiskFactor : public Named, public SeriesObject, public Calendarical, public Archivable
		{
			/// AverageType �� ������ ��ü ������ ���� ��
//			typedef std::map<AverageType, SingleReferenceForecast::ptr> vol_map_type;
//			vol_map_type vol_map;

		public:
			/// CalendarTag �� Ȱ���ϴ� ������
			explicit RiskFactor(const Name& name, const Desc& desc, const CalendarTag& cal_tag, const Size size = 250);
			/// Calendar �����͸� Ȱ���ϴ� ������
			explicit RiskFactor(const Name&, const Desc&, Calendar::Ptr, const Size size = 250);
			/// �Ҹ���
			virtual ~RiskFactor() {};

			typedef std::shared_ptr<RiskFactor> Ptr;
			typedef std::weak_ptr<RiskFactor> WPtr;
			typedef std::unique_ptr<RiskFactor> UPtr;

			/// ������ �Է� �Լ�
			virtual void Insert(const Date&, const Data&);
			/// ������ ������ ��� �Լ� (AverageType ��)
//			Data GetVolatility(const Date&, const AverageType&);
//			void AddVolatility(const AverageType&);

			virtual void SetArchiveTag(const ArchiveTag&) {};

		protected :
			/// cereal smart pointer ��ī�̺긦 ���� �⺻ ������, �ƹ��͵� ����
			RiskFactor() {}

		private:
			/// ������ �� �ʱ�ȭ �Լ�, ���� �Ⱓ��(ex. 5��, 2��,...) ������ �߰� ���ɼ�
//			void InitializeMap();

			friend class ::boost::serialization::access;

			template <class Archive>
			void serialize(Archive& ar, const unsigned int version);
		};
	} // namespace riskfactor
	 
} // namespace fre

BOOST_CLASS_EXPORT_KEY(fre::riskfactor::RiskFactor)

#endif // !fre_riskfactor_risk_factor_hpp

