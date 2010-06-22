#include "ReTechCommonIncludes.h"
#include "ReTechDrawable.h"

namespace rt
{
	Drawable::Drawable(sf::Drawable* iDrawable)
		: mDrawable(iDrawable)
	{

	}

	Drawable::~Drawable()
	{

	}

	void Drawable::UnSerialize( const YAML::Node& iNode )
	{
		WorldObject::UnSerialize(iNode);
	}

	void Drawable::Serialize( YAML::Emitter& iEmitter ) const
	{

	}

	void Drawable::Draw(sf::RenderWindow* iRenderWindow)
	{
		iRenderWindow->Draw(*mDrawable);
	}

	void Drawable::OnSetWorldPosition()
	{
		mDrawable->SetPosition(GetInheritedWorldPosition());
	}

	void Drawable::OnSetWorldScale()
	{
		mDrawable->SetScale(GetInheritedWorldScale());
	}

	void Drawable::OnSetWorldRotation()
	{
		mDrawable->SetRotation(GetInheritedWorldRotation());
	}
}