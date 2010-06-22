#include "ReTechCommonIncludes.h"
#include "ReTechAnimation.h"

namespace rt
{
	Animation::Animation()
	{

	}

	Animation::~Animation()
	{

	}

	void Animation::UnSerialize( const YAML::Node& iNode )
	{
		Sprite::UnSerialize(iNode);

		std::string animationFile;

		SafeGet(iNode, "file", animationFile);

		mAnimation.assign(new FrameAnimation(animationFile, static_cast<sf::Sprite*>(mDrawable.get())));
	}

	void Animation::Serialize( YAML::Emitter& iEmitter ) const
	{

	}

	void Animation::Update( float iFrameTime )
	{
		mAnimation->Update(iFrameTime);
	}
}