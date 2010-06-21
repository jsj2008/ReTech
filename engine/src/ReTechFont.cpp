#include "ReTechCommonIncludes.h"
#include "ReTechFont.h"

namespace rt
{
	Font::Font()
		: mIsLoaded(false)
	{

	}

	Font::Font( const std::string& iResourceName )
		: mIsLoaded(false)
	{
		Initialize(iResourceName);
	}

	Font::~Font()
	{

	}

	void Font::Load()
	{
		if(!IsLoaded())
		{
			if(!LoadFromFile(mResourceName))
			{
				*static_cast<sf::Font*>(this) = sf::Font::GetDefaultFont();
			}
		}

		mIsLoaded;
	}

	void Font::Unload()
	{
		*static_cast<sf::Font*>(this) = sf::Font();
	}

	bool Font::IsLoaded()
	{
		return mIsLoaded;
	}
}