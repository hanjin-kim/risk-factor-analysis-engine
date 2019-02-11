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
			Name-based 매니지먼트가 필요할 경우 상속 되는 클래스입니다. 
			객체의 이름과 설명을 포함하고 있습니다.
		*/
		class Named
		{
			///객체의 이름
			Name name;
			/// 객체에 대한 설명
			mutable Desc description;

		public :
			/// 주 생성자
			/*!
				대부분의 경우 이 생성자를 사용합니다. 
				객체의 이름과 설명을 인자로 받으며, 이 때 인자의 타입은 명시적입니다.
				즉, Named(Name("이름"), Desc("설명")) 과 같이 사용되어야 합니다.
				explicit 키워드에 대해서는 다음의 링크를 참고하세요.

				http://opensw.wikidot.com/cpp-fundamentals-explicit
			*/
			explicit Named(const Name&, const Desc&);
			/// 소멸자
			virtual ~Named() {};

			/// 객체의 이름을 반환합니다.
			Name GetName() const { return name; }
			/// 객체의 설명을 반환합니다.
			Desc GetDescription() const { return description; }
			/// 객체의 이름을 변경합니다.
			void SetName(const Name& nm) { name = nm; }
			/// 객체의 설명을 변경합니다.
			void SetDescription(const Desc& desc) { description = desc; }

		protected:
			/// cereal smart pointer 아카이브를 위한 기본 생성자, 아무것도 안함
			Named() {}

		private :
			/// cereal 지원을 위한 프렌드 선언
			friend class boost::serialization::access;

			/// cereal serialize 함수
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
