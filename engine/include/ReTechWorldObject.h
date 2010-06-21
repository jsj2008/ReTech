#ifndef __rtWorldObject_H__
#define __rtWorldObject_H__

#include "ReTechSerializeable.h"

namespace rt
{
	class WorldObject : public Serializeable
	{
	public:
		typedef std::vector<WorldObject*> ObjectsVec;

		WorldObject();
		virtual ~WorldObject();

		virtual void UnSerialize(DataChunk& iDataChunk);

		virtual void OnAddToWorld();

		virtual void Update(float iFrameTime);
		virtual void Draw(sf::RenderWindow* iRenderWindow);

		virtual bool LowerThen(const WorldObject* const iOther); 

		void SetWorldPosition(const sf::Vector2f& iPosition);
		void SetWorldScale(const sf::Vector2f& iScale);
		void SetWorldRotation(float iAngle);
		void SetWorldSize(const sf::Vector2f& iSize);

		sf::Vector2f GetWorldPosition();
		sf::Vector2f GetWorldScale();
		float GetWorldRotation();
		sf::Vector2f GetWorldSize();

		sf::Vector2f GetInheritedWorldPosition();
		sf::Vector2f GetInheritedWorldScale();
		float GetInheritedWorldRotation();

		virtual void OnSetWorldPosition(){}
		virtual void OnSetWorldScale(){}
		virtual void OnSetWorldRotation(){}
		virtual void OnSetWorldSize(){}

		void SetLayer(int iLayer);
		int GetLayer();

		bool IsVisible();
		void SetVisible(bool iVisible);

		bool IsEnabled();
		void SetEnabled(bool iEnabled);

		void Attach(WorldObject* iWorldObject);
		void Detach(WorldObject* iWorldObject);
		void SetParent(WorldObject* iParent);
		WorldObject* GetParent();

		void SetTag(const std::string& iTag);
		std::string GetTag();

		WorldObject* GetSubObjectByTag(const std::string& iTag);

		void SetWorld(World* iWorld);

	protected:
		bool			mVisible;
		bool			mEnabled;

		sf::Vector2f	mWorldPosition;
		sf::Vector2f	mWorldScale;
		float			mWorldRotation;
		sf::Vector2f	mWorldSize;
		int				mLayer;

		std::string		mTag;

		WorldObject*	mAttachedTo;
		ObjectsVec		mAttaches;
		ObjectsVec		mPendingAttaches;

		World*			mWorld;
	};
}

#endif