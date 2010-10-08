#ifndef __rtObjectsFactory_H__
#define __rtObjectsFactory_H__

namespace rt
{
	template<class T>
	class BaseInstantiator
	{
	public:
		virtual T* CreateInstance() = 0;
	};

	template<class C, class T>
	class Instantiator : public BaseInstantiator<T>
	{
	public:
		virtual T* CreateInstance()
		{
			return new C();
		}
	};

	template<class T>
	class ObjectsFactory
	{
	public:
		ObjectsFactory(){}
		~ObjectsFactory(){}

		template<class C>
		static bool RegisterObject(const std::string& iTypeName)
		{
			if(mRegisteredClasses.find(iTypeName) != mRegisteredClasses.end())
			{
				return false;
			}
			
			mRegisteredClasses[iTypeName] = boost::shared_ptr<BaseInstantiator<T> >(new Instantiator<C, T>());

			return true;
		}

		static T* CreateObject(const std::string& iTypeName)
		{
			std::string realTypeName = iTypeName;

			if(mRedirects.find(iTypeName) != mRedirects.end())
			{
				realTypeName = mRedirects[iTypeName];
			}

			if(mRegisteredClasses.find(iTypeName) == mRegisteredClasses.end())
			{
				return 0;
			}

			return mRegisteredClasses[iTypeName]->CreateInstance();
		}

		static void AddRedirect(const std::string& iClassFrom, const std::string& iClassTo)
		{
			mRedirects[iClassFrom] = iClassTo;
		}

		static void RemoveRedirect(const std::string& iClassFrom)
		{
			mRedirects.erase(iClassFrom);
		}

	protected:
		static std::map<std::string, boost::shared_ptr<BaseInstantiator<T> > >	mRegisteredClasses;
		static std::map<std::string, std::string>								mRedirects;
	};
}

#endif