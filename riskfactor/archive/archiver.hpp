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
		 *\brief 아카이브 I/O를 수행하는 static 메소드 클래스
		 */
		class Archiver
		{
		public:
			Archiver() {}
			~Archiver() {}

			/*!
			 *\param series 아카이브하기 위한 Archivable 객체 포인터
			 *\param tag 아카이브 태그, 아카이브의 파일명.
			 *
			 * 객체 직렬화 후.xml/xml 아카이브를 저장합니다.
			 * 아카이브가 이미 존재하는 경우 덮어씁니다.
			 */
			static void Archive(const Archivable::Ptr);

			/*!
			 *\param base_dir 아카이브 저장 기본 경로 (예. ./archive)
			 *\param name Archivable 객체의 이름. Name convention 을 통해 아카이브를 찾습니다.
			 *\param tag 아카이브 태그, 아카이브의 파일명.
			 *\return Archivable* 아카이브가 존재하지 않을 경우 NULL 포인터 반환
			 *
			 * 아카이브를 읽어 Archivable 객체를 힙에 생성하고 그 포인터를 반환합니다.
			 * name 과 tag 에 따라 탐색한 아카이브 파일이 존재하지 않을 경우 NULL 포인터를 반환합니다.
			 */
			static Archivable::Ptr Load(const String name);
			/*!
			 *\param base_dir 아카이브 저장 기본 경로 (기본값 : ./archive)
			 *아카이브 저장 기본 경로를 지정합니다. 한번 지정 되면 런타임 동안 모든 객체가 동일한 기본 경로에서 탐색됩니다.
			 */
			static void SetBaseDir(const String base_dir);

		private:
//			static boost::filesystem::path base_directory;
			static String base_directory;
		};
	}
}

#endif // !fre_riskfactor_archiver_hpp

