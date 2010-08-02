#include "ReTechCommonIncludes.h"
#include "ReTechSprite.h"
#include "ReTechResourceManager.h"
#include "ReTechImage.h"

namespace rt
{
	Sprite::Sprite()
	{
		CreateFuncProperty("sprite", fastdelegate::MakeDelegate(this, &Sprite::SetResource), fastdelegate::MakeDelegate(this, &Sprite::GetResource));
	}

	Sprite::~Sprite()
	{

	}

	void Sprite::Draw( sf::RenderWindow* iRenderWindow )
	{
		mSprite.SetPosition(GetPosition());
		mSprite.SetScale(GetScale());
		mSprite.SetOrigin(GetOrigin());
		mSprite.SetRotation(GetRotation());

		iRenderWindow->Draw(mSprite);
	}

	void Sprite::SetResource( const std::string& iResourceName )
	{
		mResourceName = iResourceName;

		Image* image = UResource(Image, iResourceName);

		if(image)
		{
			image->Load();
			mSprite.SetImage(*image);
		}
	}

	const std::string& Sprite::GetResource()
	{
		return  mResourceName;
	}
}