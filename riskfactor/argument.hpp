#ifndef fre_riskfactor_argument_hpp
#define fre_riskfactor_argument_hpp

#include <riskfactor/types.hpp>

namespace fre
{
	namespace riskfactor
	{
		class Argument
		{
			String key;
			Data value;

		public :
			Argument() = delete;
			Argument(String k, Data v) : key(k), value(v) {}
			
			String GetKey() const { return key; }
			Data GetValue() const { return value; }
		};
	}
}

#endif // !fre_riskfactor_arguments_hpp

