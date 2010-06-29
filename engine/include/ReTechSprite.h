#ifndef __rtSprite_H__
#define __rtSprite_H__

#include "ReTechWorldObject.h"

namespace rt
{
	class Sprite : public WorldObject
	{
	public:
		Sprite();
		virtual ~Sprite();

		virtual void UnSerialize(const YAML::Node& iNode);
		virtual void Serialize(YAML::Emitter& iEmitter) const;

		virtual void Draw(sf::RenderWindow* iRenderWindow);

		void SetResource(const std::string& iResourceName);

		protected:
			sf::Sprite mSprite;
	};
}

#endif