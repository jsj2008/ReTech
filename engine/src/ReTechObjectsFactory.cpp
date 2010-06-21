#include "ReTechCommonIncludes.h"
#include "ReTechObjectsFactory.h"
#include "ReTechSerializeable.h"

Poco::DynamicFactory<rt::Serializeable> rt::ObjectsFactory::mObjectsFactory;

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
		if(mObjectsFactory.isClass(iTypeName))
		{
			return mObjectsFactory.createInstance(iTypeName);
		}

		return 0;
	}
}