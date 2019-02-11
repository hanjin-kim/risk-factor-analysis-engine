#ifndef fre_riskfactor_archiver_hpp
#define fre_riskfactor_archiver_hpp

#include <boost/filesystem/path.hpp>

#include <riskfactor/types.hpp>
#include <riskfactor/archivable.hpp>

namespace fre
{
	namespace riskfactor
	{
		/*!
		 *\brief ��ī�̺� I/O�� �����ϴ� static �޼ҵ� Ŭ����
		 */
		class Archiver
		{
		public:
			Archiver() {}
			~Archiver() {}

			/*!
			 *\param series ��ī�̺��ϱ� ���� Archivable ��ü ������
			 *\param tag ��ī�̺� �±�, ��ī�̺��� ���ϸ�.
			 *
			 * ��ü ����ȭ ��.xml/xml ��ī�̺긦 �����մϴ�.
			 * ��ī�̺갡 �̹� �����ϴ� ��� ����ϴ�.
			 */
			static void Archive(const Archivable::Ptr);

			/*!
			 *\param base_dir ��ī�̺� ���� �⺻ ��� (��. ./archive)
			 *\param name Archivable ��ü�� �̸�. Name convention �� ���� ��ī�̺긦 ã���ϴ�.
			 *\param tag ��ī�̺� �±�, ��ī�̺��� ���ϸ�.
			 *\return Archivable* ��ī�̺갡 �������� ���� ��� NULL ������ ��ȯ
			 *
			 * ��ī�̺긦 �о� Archivable ��ü�� ���� �����ϰ� �� �����͸� ��ȯ�մϴ�.
			 * name �� tag �� ���� Ž���� ��ī�̺� ������ �������� ���� ��� NULL �����͸� ��ȯ�մϴ�.
			 */
			static Archivable::Ptr Load(const String name);
			/*!
			 *\param base_dir ��ī�̺� ���� �⺻ ��� (�⺻�� : ./archive)
			 *��ī�̺� ���� �⺻ ��θ� �����մϴ�. �ѹ� ���� �Ǹ� ��Ÿ�� ���� ��� ��ü�� ������ �⺻ ��ο��� Ž���˴ϴ�.
			 */
			static void SetBaseDir(const String base_dir);

		private:
//			static boost::filesystem::path base_directory;
			static String base_directory;
		};
	}
}

#endif // !fre_riskfactor_archiver_hpp

