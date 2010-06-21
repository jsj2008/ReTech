#include "ReTechCommonIncludes.h"
#include "ReTechResourceManager.h"

namespace rt
{
	Resource::Resource()
		: mResourceName("")
	{
		
	}

	Resource::~Resource()
	{
	}

	void Resource::Initialize( const std::string& iResourceName )
	{
		mResourceName = iResourceName;
	}

	void Resource::Reload()
	{
		Unload();
		Load();
	}
}