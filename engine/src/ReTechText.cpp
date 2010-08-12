#include "ReTechCommonIncludes.h"
#include "ReTechText.h"
#include "ReTechFont.h"

namespace rt
{
	Text::Text()
	{
		CreateFuncProperty("string", fastdelegate::MakeDelegate(&mText, &sf::Text::SetString), fastdelegate::MakeDelegate(&mText, &sf::Text::GetString));
		CreateFuncProperty("char_size", fastdelegate::MakeDelegate(&mText, &sf::Text::SetCharacterSize),  fastdelegate::MakeDelegate(&mText, &sf::Text::GetCharacterSize));
		CreateFuncProperty("font", fastdelegate::MakeDelegate(this, &Text::SetFont),  fastdelegate::MakeDelegate(this, &Text::GetFont));
	}

	Text::~Text()
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

	void Text::SetFont( const std::string& iResourceName )
	{
		mResourceName = iResourceName;

		Font* font = UResource(Font, iResourceName);
		font->Load();

		mText.SetFont(*font);
	}

	const std::string& Text::GetFont()
	{
		return mResourceName;
	}
}