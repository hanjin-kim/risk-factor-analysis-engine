#ifndef fre_riskfactor_calendarical_hpp
#define fre_riskfactor_calendarical_hpp

#include <memory>

#include <boost/serialization/access.hpp>

#include <riskfactor/named.hpp>
#include <riskfactor/timeseries.hpp>
#include <riskfactor/calendar/calendar.hpp>

namespace fre
{

	namespace riskfactor
	{
		/*!
			Ķ������ �����ϴ� �ð迭 �����͸� �����ϴ� ��ü�� ���� ���Ŭ�����Դϴ�.
			Ķ����, �ð迭 ������ �����̳��� ũ�⸦ �����Ͽ��� �մϴ�.
			�ð迭 �������� ��� �ݺ��ڸ� ���� ������ �����մϴ�.

			@todo �ð迭 ������ �ִ� ũ�⸦ ������ �� �ֵ��� �ؾ��Ѵ�. 
					���� ������ ũ�� ���� ����� ũ�Ⱑ ���� ���, ��Ȯ���Ѵ�.
		*/
		class Calendarical// : public Enable_Shared_From_This<Calendarical>
		{
			/// Ķ����
			Calendar::Ptr calendar;


		public :
			/// CalendarTag �� Ȱ���ϴ� ������
			explicit Calendarical(const CalendarTag&);
			/// Calendar �����͸� Ȱ���ϴ� ������
			explicit Calendarical(Calendar::Ptr);
			/// �Ҹ���
			virtual ~Calendarical() {}

			/// �����ϴ� Ķ������ ��ȯ�մϴ�.
			Calendar::Ptr GetCalendar() { return calendar; }

			typedef std::shared_ptr<Calendarical> Ptr;
			typedef std::shared_ptr<const Calendarical> CPtr;
			typedef std::weak_ptr<Calendarical> WPtr;
			typedef std::unique_ptr<Calendarical> UPtr;

		protected :
			/// smart pointer ��ī�̺긦 ���� �⺻ ������, �ƹ��͵� ����
			Calendarical() {}

		private :
			/// serialization ������ ���� ������ ����
			friend class ::boost::serialization::access;

			/// serialize �Լ� ����
			template <class Archive>
			void save(Archive& ar, const unsigned int version) const;

			template <class Archive>
			void load(Archive& ar, const unsigned int version);

			template <class Archive>
			void serialize(Archive& ar, const unsigned int version);
		};
	}
}

#endif // !fre_riskfactor_calendarical_hpp
