#ifndef fre_riskfactor_archivable_hpp
#define fre_riskfactor_archivable_hpp

#include <memory>

#include <boost/serialization/access.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/shared_ptr.hpp>

#include <riskfactor/types.hpp>

namespace fre
{
	namespace riskfactor
	{
		/*!
			이 클래스는 Archiver 클래스 인스턴스를 통해 직렬화 되는 객체의 순수가상클래스입니다.
			Archiver 클래스를 통해 직렬화 하고자 하는 객체는 모두 이 클래스로 부터
			파생되어야 합니다.
		*/
		class Archivable
		{
			/*! 
				Archiver::Archive()를 통해 아카이브 하는데 사용되는 태그입니다.
				아카이브 경로는 다음과 같습니다. :

					{Archiver::base_directory}/{archive_tag}.json
			*/
			ArchiveTag archive_tag;
		public:

			/// 생성자
			Archivable(const ArchiveTag& tag)
				: archive_tag(tag)
			{}
			/// 소멸자
			virtual ~Archivable() {}

			typedef std::shared_ptr<Archivable> Ptr;
			typedef std::weak_ptr<Archivable> WPtr;
			typedef std::unique_ptr<Archivable> UPtr;

			/// 아카이브 태그를 반환하는 함수
			ArchiveTag GetArchiveTag() const { return archive_tag; }
			/// 아카이브 태그를 변경하는 함수, 파생클래스에서 정의하여야 합니다.
			virtual void SetArchiveTag(const ArchiveTag&) = 0;

		protected :
			/// cereal smart pointer 아카이브를 위한 기본 생성자, 아무것도 안함
			Archivable() {}

		private :
			
			/// cereal access 접근을 위한 friend 선언
			friend class boost::serialization::access;

			/// cereal serialize 템블릿 함수
			template <class Archive>
			void serialize(Archive& ar, const unsigned int version)
			{
				ar & BOOST_SERIALIZATION_NVP(archive_tag);
			}
			
		};
	}
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(fre::riskfactor::Archivable)

#endif