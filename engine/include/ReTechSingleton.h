#ifndef __ReTechSingleton_H__
#define __ReTechSingleton_H__

namespace rt
{
	template<class T>
	class Singleton
	{
	public:
		Singleton()
		{
			mInstance = static_cast<T*>(this);
		}

		static T* Get()
		{
			return mInstance;
		}

	protected:
		static T* mInstance;
	};
}

#endif