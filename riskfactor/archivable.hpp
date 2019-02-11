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
			�� Ŭ������ Archiver Ŭ���� �ν��Ͻ��� ���� ����ȭ �Ǵ� ��ü�� ��������Ŭ�����Դϴ�.
			Archiver Ŭ������ ���� ����ȭ �ϰ��� �ϴ� ��ü�� ��� �� Ŭ������ ����
			�Ļ��Ǿ�� �մϴ�.
		*/
		class Archivable
		{
			/*! 
				Archiver::Archive()�� ���� ��ī�̺� �ϴµ� ���Ǵ� �±��Դϴ�.
				��ī�̺� ��δ� ������ �����ϴ�. :

					{Archiver::base_directory}/{archive_tag}.json
			*/
			ArchiveTag archive_tag;
		public:

			/// ������
			Archivable(const ArchiveTag& tag)
				: archive_tag(tag)
			{}
			/// �Ҹ���
			virtual ~Archivable() {}

			typedef std::shared_ptr<Archivable> Ptr;
			typedef std::weak_ptr<Archivable> WPtr;
			typedef std::unique_ptr<Archivable> UPtr;

			/// ��ī�̺� �±׸� ��ȯ�ϴ� �Լ�
			ArchiveTag GetArchiveTag() const { return archive_tag; }
			/// ��ī�̺� �±׸� �����ϴ� �Լ�, �Ļ�Ŭ�������� �����Ͽ��� �մϴ�.
			virtual void SetArchiveTag(const ArchiveTag&) = 0;

		protected :
			/// cereal smart pointer ��ī�̺긦 ���� �⺻ ������, �ƹ��͵� ����
			Archivable() {}

		private :
			
			/// cereal access ������ ���� friend ����
			friend class boost::serialization::access;

			/// cereal serialize �ۺ� �Լ�
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