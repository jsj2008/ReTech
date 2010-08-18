#ifndef __rtResourceManager_H__
#define __rtResourceManager_H__

#include "ReTechResource.h"

namespace rt
{
	class ResourceManager : public Singleton<ResourceManager>
	{
	public:
		typedef std::map<std::string, std::string> StringMap;
		typedef Poco::HashMap<std::string, boost::shared_ptr<Resource>> ResourceMap;

		ResourceManager();
		~ResourceManager();

		Resource* GetResource(const std::string& iResourceName);

		void RegisterExtension(const std::string& iExtension, const std::string& iTypeName);

		void CreateResources();
		void ClearResources();

	protected:
		void findResources(const std::string& iResourceDirectory);

		ResourceMap mResources;
		StringMap	mExtensions;
	};
}

#endif