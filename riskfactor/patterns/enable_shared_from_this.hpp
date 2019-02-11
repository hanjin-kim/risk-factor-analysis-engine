#ifndef fre_risk_factor_enable_shared_from_this_hpp
#define fre_risk_factor_enable_shared_from_this_hpp

#include <memory>

namespace fre
{
	namespace riskfactor
	{
		template<class Derived>
		class enable_shared_from_This
		{
		public:
			typedef std::shared_ptr<Derived> Ptr;

			Ptr shared_from_This()
			{
				return std::static_pointer_cast<Derived>(static_cast<Derived *>(this)->shared_from_this());
			}
			Ptr shared_from_This() const
			{
				return std::static_pointer_cast<Derived>(static_cast<Derived *>(this)->shared_from_this());
			}
		};
	}
}

#endif //!fre_ris_factor_enable_shared_from_this_hpp