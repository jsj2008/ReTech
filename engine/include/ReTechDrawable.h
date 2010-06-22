#ifndef __rtDrawable_H__
#define __rtDrawable_H__

#include "ReTechWorldObject.h"

namespace rt
{
	class Drawable : public WorldObject
	{
	public:
		Drawable(sf::Drawable* iDrawable);
		virtual ~Drawable();

		virtual void UnSerialize(const YAML::Node& iNode);
		virtual void Serialize(YAML::Emitter& iEmitter) const;

		virtual void Draw(sf::RenderWindow* iRenderWindow);

		virtual void OnSetWorldPosition();
		virtual void OnSetWorldScale();
		virtual void OnSetWorldRotation();

	protected:
		Poco::SharedPtr<sf::Drawable> mDrawable;
	};
}

#endif