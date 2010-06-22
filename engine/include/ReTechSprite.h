#ifndef __rtSprite_H__
#define __rtSprite_H__

#include "ReTechDrawable.h"

namespace rt
{
	class Sprite : public Drawable
	{
	public:
		Sprite();
		virtual ~Sprite();

		virtual void UnSerialize(const YAML::Node& iNode);
		virtual void Serialize(YAML::Emitter& iEmitter) const;

		void SetResource(const std::string& iResourceName);
	};
}

#endif