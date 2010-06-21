#include "ReTechCommonIncludes.h"
#include "ReTechSprite.h"
#include "ReTechResourceManager.h"
#include "ReTechImage.h"

namespace rt
{
	Sprite::Sprite()
		: Drawable(new sf::Sprite())
	{
		
	}

	Sprite::~Sprite()
	{

	}

	void Sprite::UnSerialize(DataChunk& iDataChunk)
	{
		Drawable::UnSerialize(iDataChunk);

		SetResource(iDataChunk.GetOption("sprite"));
	}

	void Sprite::SetResource( const std::string& iResourceName )
	{
		Image* image = UResource(Image, iResourceName);
		image->Load();

		static_cast<sf::Sprite*>(mDrawable.get())->SetImage(*image);

		SetWorldSize(static_cast<sf::Sprite*>(mDrawable.get())->GetSize());
	}
}