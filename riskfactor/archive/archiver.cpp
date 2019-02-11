#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/serialization/nvp.hpp>

#include <boost/filesystem.hpp>
#include <boost/utility.hpp>

#include <riskfactor/easylogging++/easylogging++.h>
#include <riskfactor/archive/archiver.hpp>
#include <riskfactor/errors.hpp>

namespace fre
{
	namespace riskfactor
	{
		String Archiver::base_directory = "./archive";
//		boost::filesystem::path Archiver::base_directory = "./archive";

		void Archiver::SetBaseDir(const String base_dir)
		{
			base_directory = base_dir;
		}

		Archivable::Ptr Archiver::Load(const String name)
		{
			QL_REQUIRE(name != "", "Name must be provided.");

			namespace fs = boost::filesystem;

			fs::ifstream ifs;

			String fpath = base_directory + "/" + name + ".xml";

			fs::path dir(fpath);

			LOG(DEBUG) << "Trying to open " << dir.string() << std::endl;

			try
			{
				ifs.open(dir);
			}
			catch (std::exception& e)
			{
				LOG(ERROR) << dir.string() << std::endl;
				LOG(ERROR) << "파일을 열 수 없습니다. " << e.what() << std::endl;
				ifs.close();
				return Archivable::Ptr();
			}

			if (!ifs) {
				LOG(DEBUG) << "No archive found" << std::endl;
				return Archivable::Ptr();
			}

			LOG(DEBUG) << "File opened " << std::endl;
			Archivable::Ptr ptr;
			{
				boost::archive::xml_iarchive ia(ifs);

				try
				{
					ia >> BOOST_SERIALIZATION_NVP(ptr);
				}
				catch (boost::archive::archive_exception& e)
				{
					LOG(ERROR) << e.what() << std::endl;
					return Archivable::Ptr();
				}
			}

			LOG(DEBUG) << "The archive of " << ptr->GetArchiveTag() << " is successfully loaded." << std::endl;
			ifs.close();

			return ptr;
		}

		void Archiver::Archive(const Archivable::Ptr ptr)
		{

			LOG(DEBUG) << "Archiver::Archive begins" << std::endl;

			namespace fs = boost::filesystem;

			// path exist?
			String name = ptr->GetArchiveTag();

			String fname = base_directory + "/" + name + ".xml";

			fs::path dir(fname);

			LOG(DEBUG) << "base_dir = " << dir.parent_path().string() << std::endl;

			if (!fs::exists(dir.parent_path()))
			{
				try
				{
					LOG(DEBUG) << "Creating directory .. " << dir.parent_path().string() << std::endl;
					fs::create_directories(dir.parent_path());
				}
				catch (boost::archive::archive_exception& e)
				{
					LOG(ERROR) << "Can't create directory(s). :" << e.what() << std::endl;
					return;
				}
			}

			fs::ofstream outf;

			try

			{
				outf.open(dir);
			}
			catch (std::exception& e)
			{
				LOG(ERROR) << "Can't open files : " << e.what() << std::endl;
				return;
			}
			// bare block for archives, otherwise archive will not be closed properly
			{
				boost::archive::xml_oarchive oa(outf);

				try
				{
					LOG(DEBUG) << "Serializing.. " + name << std::endl;
					oa << BOOST_SERIALIZATION_NVP(ptr);
				}
				catch (boost::archive::archive_exception& e)
				{
					LOG(DEBUG) << "Error while serializing " + name << std::endl;
					LOG(DEBUG) << e.what() << std::endl;
					outf.close();
					boost::filesystem::remove(dir);
					return;
				}
			}

			LOG(DEBUG) << "The archive of " << ptr->GetArchiveTag() << " is successfully stored." << std::endl;
			outf.close();
		}
	}
}
