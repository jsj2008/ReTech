#ifndef __rtObjectsFactory_H__
#define __rtObjectsFactory_H__

namespace rt
{
	class Serializeable;

	class ObjectsFactory
	{
	public:
		ObjectsFactory();
		~ObjectsFactory();

		template<class T>
		static bool RegisterObject(const std::string& iTypeName)
		{
			mObjectsFactory.registerClass<T>(iTypeName);

			return true;
		}

		static Serializeable* CreateObject(const std::string& iTypeName);

	protected:
		static Poco::DynamicFactory<Serializeable> mObjectsFactory;
	};
}

#endif