#ifndef __rtAnimation_H__
#define __rtAnimation_H__

#include "ReTechSprite.h"
#include "ReTechFrameAnimation.h"

namespace rt
{
	class Animation : virtual public Sprite
	{
	public:
		Animation();
		virtual ~Animation();

		virtual void UnSerialize(DataChunk& iDataChunk);

		virtual void Update(float iFrameTime);

	protected:
		Poco::SharedPtr<FrameAnimation> mAnimation;
	};
}

#endif