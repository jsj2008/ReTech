#include "ReTechCommonIncludes.h"
#include "ReTechSprite.h"
#include "ReTechResourceManager.h"
#include "ReTechImage.h"

namespace rt
{
	Sprite::Sprite()
	{
		
	}

	Sprite::~Sprite()
	{

	}

	void Sprite::UnSerialize( const YAML::Node& iNode )
	{
		WorldObject::UnSerialize(iNode);

		SafeGet(iNode, "sprite", fastdelegate::MakeDelegate(this, &Sprite::SetResource));
	}

	void Sprite::Serialize( YAML::Emitter& iEmitter ) const
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
		Image* image = UResource(Image, iResourceName);

		if(image)
		{
			image->Load();
			mSprite.SetImage(*image);
		}
	}
}