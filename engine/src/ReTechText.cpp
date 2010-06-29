#include "ReTechCommonIncludes.h"
#include "ReTechText.h"
#include "ReTechFont.h"

namespace rt
{
	Text::Text()
	{

	}

	Text::~Text()
	{

	}

	void Text::UnSerialize( const YAML::Node& iNode )
	{
		WorldObject::UnSerialize(iNode);

		SafeGet(iNode, "string", fastdelegate::MakeDelegate(this, &Text::SetString));
		SafeGet(iNode, "font", fastdelegate::MakeDelegate(this, &Text::SetFont));
		SafeGet(iNode, "char_size", fastdelegate::MakeDelegate(this, &Text::SetSize));
	}

	void Text::Serialize( YAML::Emitter& iEmitter ) const
	{

	}

	void Text::Draw( sf::RenderWindow* iRenderWindow )
	{
		mText.SetPosition(GetPosition());
		mText.SetScale(GetScale());
		mText.SetOrigin(GetOrigin());
		mText.SetRotation(GetRotation());

		iRenderWindow->Draw(mText);
	}

	void Text::SetString( const std::string& iString )
	{
		mText.SetString(iString);
	}

	void Text::SetSize( int iSize )
	{
		mText.SetCharacterSize(iSize);
	}

	void Text::SetFont( const std::string& iResourceName )
	{
		Font* font = UResource(Font, iResourceName);
		font->Load();

		mText.SetFont(*font);
	}
}