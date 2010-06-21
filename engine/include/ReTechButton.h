#ifndef __rtButton_H__
#define __rtButton_H__

#include "ReTechWorldObject.h"
#include "ReTechSprite.h"
#include "ReTechText.h"

namespace rt
{
	class Button : public WorldObject
	{
	public:
		Button();
		virtual ~Button();
		
		virtual void UnSerialize(DataChunk& iDataChunk);

		virtual void OnAddToWorld();

		bool IsInside(const sf::Vector2f& iPoint);
		bool HandleEvent(const sf::Event& iEvent);

	protected:
		WorldObject*	mNormal;
		WorldObject*	mHover;

		std::string		mOnPressExec;

		bool			mIsMouseOver;

		InputManager::InputHandler mHandler;
	};
}

#endif