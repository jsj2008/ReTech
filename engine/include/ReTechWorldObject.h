#ifndef __rtWorldObject_H__
#define __rtWorldObject_H__

#include "ReTechSerializeable.h"

namespace rt
{
	class WorldObject : public Serializeable, public sf::Drawable
	{
	public:
		WorldObject();
		virtual ~WorldObject();

		virtual void UnSerialize(const YAML::Node& iNode);
		virtual void Serialize(YAML::Emitter& iEmitter) const;

		virtual void Update(float iFrameTime);
		virtual void Draw(sf::RenderWindow* iRenderWindow);

		virtual bool LowerThen(const WorldObject* const iOther); 

		void SetLayer(int iLayer);
		int GetLayer();

		bool IsVisible();
		void SetVisible(bool iVisible);

		bool IsEnabled();
		void SetEnabled(bool iEnabled);

		void SetTag(const std::string& iTag);
		std::string GetTag();

		void SetWorld(World* iWorld);

	protected:
		virtual void Render(sf::RenderTarget& target, sf::Renderer& renderer) const;

		bool			mVisible;
		bool			mEnabled;
		int				mLayer;
		std::string		mTag;
		World*			mWorld;
	};
}

#endif