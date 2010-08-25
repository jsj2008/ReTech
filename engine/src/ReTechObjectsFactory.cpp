#include "ReTechCommonIncludes.h"
#include "ReTechObjectsFactory.h"
#include "ReTechSerializeable.h"

Poco::DynamicFactory<rt::Serializeable> rt::ObjectsFactory::mObjectsFactory;
std::map<sf::String, sf::String> rt::ObjectsFactory::mRedirects;

namespace rt
{
	ObjectsFactory::ObjectsFactory()
	{

	}

	ObjectsFactory::~ObjectsFactory()
	{

	}

	Serializeable* ObjectsFactory::CreateObject( const std::string& iTypeName )
	{
		std::string realTypeName = iTypeName;

		if(mRedirects.find(iTypeName) != mRedirects.end())
		{
			realTypeName = mRedirects[iTypeName];
		}

		if(mObjectsFactory.isClass(realTypeName))
		{
			return mObjectsFactory.createInstance(realTypeName);
		}

		return 0;
	}

	void ObjectsFactory::AddRedirect(const sf::String& iClassFrom, const sf::String& iClassTo)
	{
		mRedirects[iClassFrom] = iClassTo;
	}

	void ObjectsFactory::RemoveRedirect(const sf::String& iClassFrom)
	{
		mRedirects.erase(iClassFrom);
	}
}