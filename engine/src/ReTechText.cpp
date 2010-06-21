#include "ReTechCommonIncludes.h"
#include "ReTechText.h"
#include "ReTechFont.h"

namespace rt
{
	Text::Text()
		: Drawable(new sf::Text())
	{

	}

	Text::~Text()
	{

	}

	void Text::UnSerialize(DataChunk& iDataChunk)
	{
		Drawable::UnSerialize(iDataChunk);

		static_cast<sf::Text*>(mDrawable.get())->SetString(iDataChunk.GetOption("string"));

		SetResource(iDataChunk.GetOption("font"));
		
		int size = 30;
		Poco::NumberParser::tryParse(iDataChunk.GetOption("size"), size);
		static_cast<sf::Text*>(mDrawable.get())->SetCharacterSize(size);
	}

	void Text::SetResource( const std::string& iResourceName )
	{
		Font* font = UResource(Font, iResourceName);
		font->Load();

		static_cast<sf::Text*>(mDrawable.get())->SetFont(*font);
	}
}