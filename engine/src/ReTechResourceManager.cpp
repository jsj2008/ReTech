#include "ReTechCommonIncludes.h"
#include "ReTechResourceManager.h"

URegisterSingleton(ResourceManager)

namespace rt
{
	ResourceManager::ResourceManager()
	{

	}

	ResourceManager::~ResourceManager()
	{

	}

	Resource* ResourceManager::GetResource( const std::string& iResourceName )
	{
		std::string resourceName = boost::filesystem2::path(iResourceName).string();

		if(mResources.find(resourceName) == mResources.end())
		{
			LogManager::Get()->Error("Cant find resource - " + resourceName);
			return 0;
		}

		return mResources[resourceName].get();
	}

	void ResourceManager::RegisterExtension( const std::string& iExtension, const std::string& iTypeName )
	{
		mExtensions[iExtension] = iTypeName;
	}

	void ResourceManager::CreateResources()
	{
		//TODO make config file with resources
		//findResources(OptionsManager::Get()->GetOption("media_dir").ToString());
	}

	void ResourceManager::ClearResources()
	{
		ResourceMap::iterator end = mResources.end();
		for(ResourceMap::iterator iter = mResources.begin(); iter != end; ++iter)
		{
			iter->second->Unload();
		}
	}

// 	void ResourceManager::findResources( const std::string& iResourceDirectory )
// 	{
// 		std::set<std::string>		resources;
// 		boost::filesystem2::path	resourceName; 
// 
// 		Poco::Glob::glob(iResourceDirectory + "*", resources);
// 
// 		for(std::set<std::string>::iterator iter = resources.begin(); iter != resources.end(); ++iter)
// 		{
// 			resourceName.parse(*iter);
// 
// 			if(resourceName.isDirectory())
// 			{
// 				findResources(*iter);
// 			}
// 			else
// 			{
// 				Resource* newResource = dynamic_cast<Resource*>(ObjectsFactory<Serializeable>::CreateObject(mExtensions[resourceName.getExtension()]));
// 				if(newResource != 0)
// 				{
// 					newResource->Initialize(*iter);
// 					mResources[*iter].reset(newResource);
// 				}
// 				else
// 				{
// 					LogManager::Get()->Error("Type for " + (*iter) + " is not registered.");
// 				}
// 			}
// 		}
// 	}
}