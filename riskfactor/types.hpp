#ifndef fre_riskfactor_types_hpp
#define fre_riskfactor_types_hpp

#include <string>

namespace fre
{
	namespace riskfactor
	{
		typedef double Double;

		typedef std::string String;

		typedef String Name;
		typedef String Desc;
		typedef String ArchiveTag;

		typedef bool Bool;
		typedef size_t Size;
		typedef double Data;

		typedef Data Lambda;

		enum class AverageType
		{
			SMA,
			EWMA,
		};

		// Global hashing function for enum
		struct EnumClassHash
		{
			template <typename T>
			Size operator()(T t) const
			{
				return static_cast<Size>(t);
			}
		};
	}
}

#endif // !fre_riskfactor_type_hpp