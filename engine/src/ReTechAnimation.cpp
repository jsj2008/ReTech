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

	void Animation::UnSerialize(DataChunk& iDataChunk)
	{
		Sprite::UnSerialize(iDataChunk);

		mAnimation.assign(new FrameAnimation(iDataChunk.GetOption("file"), static_cast<sf::Sprite*>(mDrawable.get())));
	}

	void Animation::Update( float iFrameTime )
	{
		mAnimation->Update(iFrameTime);
	}
}