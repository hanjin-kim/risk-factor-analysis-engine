#ifndef fre_riskfactor_named_hpp
#define fre_riskfactor_named_hpp

#include <boost/serialization/access.hpp>
#include <boost/serialization/nvp.hpp>

#include <riskfactor/types.hpp>

namespace fre
{
	namespace riskfactor
	{
		/*!
			Name-based �Ŵ�����Ʈ�� �ʿ��� ��� ��� �Ǵ� Ŭ�����Դϴ�. 
			��ü�� �̸��� ������ �����ϰ� �ֽ��ϴ�.
		*/
		class Named
		{
			///��ü�� �̸�
			Name name;
			/// ��ü�� ���� ����
			mutable Desc description;

		public :
			/// �� ������
			/*!
				��κ��� ��� �� �����ڸ� ����մϴ�. 
				��ü�� �̸��� ������ ���ڷ� ������, �� �� ������ Ÿ���� ������Դϴ�.
				��, Named(Name("�̸�"), Desc("����")) �� ���� ���Ǿ�� �մϴ�.
				explicit Ű���忡 ���ؼ��� ������ ��ũ�� �����ϼ���.

				http://opensw.wikidot.com/cpp-fundamentals-explicit
			*/
			explicit Named(const Name&, const Desc&);
			/// �Ҹ���
			virtual ~Named() {};

			/// ��ü�� �̸��� ��ȯ�մϴ�.
			Name GetName() const { return name; }
			/// ��ü�� ������ ��ȯ�մϴ�.
			Desc GetDescription() const { return description; }
			/// ��ü�� �̸��� �����մϴ�.
			void SetName(const Name& nm) { name = nm; }
			/// ��ü�� ������ �����մϴ�.
			void SetDescription(const Desc& desc) { description = desc; }

		protected:
			/// cereal smart pointer ��ī�̺긦 ���� �⺻ ������, �ƹ��͵� ����
			Named() {}

		private :
			/// cereal ������ ���� ������ ����
			friend class boost::serialization::access;

			/// cereal serialize �Լ�
			template <class Archive>
			void serialize(Archive& ar, const unsigned int version)
			{
				ar & BOOST_SERIALIZATION_NVP(name);
				ar & BOOST_SERIALIZATION_NVP(description);
			}
		};

		inline Named::Named(const Name& nm, const Desc& dsc)
			: name(nm), description(dsc)
		{}
	}
}

#endif // !fre_riskfactor_named_hpp
