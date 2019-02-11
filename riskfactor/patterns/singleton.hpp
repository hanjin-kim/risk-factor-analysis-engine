#ifndef fre_singleton_hpp
#define fre_singleton_hpp

namespace fre
{
	namespace riskfactor
	{
		template <typename T>
		class Singleton
		{
		protected:
			Singleton() {}
			virtual ~Singleton() {}

		public:
			Singleton(const Singleton&) = delete;

			static T& GetInstance()
			{
				if (instance == NULL)
					instance = new T;
				return *instance;
			}

			static void DestroyInstance()
			{
				if (instance)
				{
					delete instance;
					instance = NULL;
				}
			}

		private:
			static T* instance;
		};

		template <typename T> T* Singleton<T>::instance = 0;
	}
}
#endif // !fre_singleton_hpp
