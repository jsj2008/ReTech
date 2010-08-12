#ifndef __rtButton_H__
#define __rtButton_H__

#include "ReTechWorldObject.h"
#include "ReTechSprite.h"
#include "ReTechText.h"

namespace rt
{
	class Button : public Sprite
	{
	public:
		Button();
		virtual ~Button();

		virtual void UnSerialize(const YAML::Node& iNode);
		virtual void Serialize(YAML::Emitter& iEmitter) const;

		bool IsInside(const sf::Vector2f& iPoint);
		bool HandleEvent(const sf::Event& iEvent);

	protected:
		std::string		mNormalResource;
		std::string		mHoverResource;

		std::string		mOnPressExec;
		std::string		mOnPressExecParam;

		bool			mIsMouseOver;

		InputManager::InputHandler mHandler;
	};
}

#endif