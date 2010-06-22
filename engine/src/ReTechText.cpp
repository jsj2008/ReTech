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

	void Text::UnSerialize( const YAML::Node& iNode )
	{
		Drawable::UnSerialize(iNode);

		SafeGet(iNode, "string", fastdelegate::MakeDelegate(this, &Text::SetString));
		SafeGet(iNode, "font", fastdelegate::MakeDelegate(this, &Text::SetFont));
		SafeGet(iNode, "char_size", fastdelegate::MakeDelegate(this, &Text::SetSize));
	}

	void Text::Serialize( YAML::Emitter& iEmitter ) const
	{

	}

	void Text::SetString( const std::string& iString )
	{
		static_cast<sf::Text*>(mDrawable.get())->SetString(iString);
	}

	void Text::SetSize( int iSize )
	{
		static_cast<sf::Text*>(mDrawable.get())->SetCharacterSize(iSize);
	}

	void Text::SetFont( const std::string& iResourceName )
	{
		Font* font = UResource(Font, iResourceName);
		font->Load();

		static_cast<sf::Text*>(mDrawable.get())->SetFont(*font);
	}
}