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
		virtual void Serialize(YAML::Emitter& iEmitter);

		virtual bool IsMouseInside(const sf::Vector2f& iMousePos);
		virtual bool HandleFocusedEvent(const sf::Event& iEvent);

		virtual void MouseEnter();
		virtual void MouseLeave();

	protected:
		std::string		mNormalResource;
		std::string		mHoverResource;

		std::string		mOnPressExec;
		std::string		mOnPressExecParam;
	};
}

#endif