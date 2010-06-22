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

		virtual void UnSerialize(const YAML::Node& iNode);
		virtual void Serialize(YAML::Emitter& iEmitter) const;

		virtual void Update(float iFrameTime);

	protected:
		Poco::SharedPtr<FrameAnimation> mAnimation;
	};
}

#endif