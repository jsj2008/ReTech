#include "ReTechCommonIncludes.h"
#include "ReTechImage.h"

namespace rt
{
	Image::Image()
		: mDefaultResourceName("./media/default/no_texture.tga")
	{

	}

	Image::Image( const std::string& iResourceName )
		: mDefaultResourceName("./media/default/no_texture.tga")
	{
		Initialize(iResourceName);
	}

	Image::~Image()
	{

	}

	void Image::Load()
	{
		if(!IsLoaded())
		{
			if(!LoadFromFile(mResourceName))
			{
				if(!LoadFromFile(mDefaultResourceName))
				{
					LogManager::Get()->Warning("Missed default texture for Image.");
				}
			}
		}
	}

	void Image::Unload()
	{
		*static_cast<sf::Image*>(this) = sf::Image();
	}

	bool Image::IsLoaded()
	{
		return GetPixelsPtr() != 0;
	}
}