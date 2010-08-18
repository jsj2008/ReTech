#include "ReTechCommonIncludes.h"
#include "ReTechButton.h"
#include "ReTechConsoleManager.h"

namespace rt
{
	Button::Button()
	{
		mClassName = "Button";
	}

	Button::~Button()
	{
	}

	void Button::UnSerialize( const YAML::Node& iNode )
	{
		WorldObject::UnSerialize(iNode);

		SafeGet(iNode, "on_press", mOnPressExec);
		
		Poco::StringTokenizer tokenizer(mOnPressExec, " ");
		if(tokenizer.count() == 2)
		{
			mOnPressExec = tokenizer[0];
			mOnPressExecParam = tokenizer[1];
		}

		SafeGet(iNode, "normal", mNormalResource);
		SafeGet(iNode, "hover", mHoverResource);

		SetResource(mNormalResource);
	}

	void Button::Serialize( YAML::Emitter& iEmitter ) const
	{
		WorldObject::Serialize(iEmitter);
	}

	bool Button::IsMouseInside( const sf::Vector2f& iMousePos )
	{
		return sf::FloatRect(GetPosition(), mSprite.GetSize()).Contains(iMousePos);
	}

	bool Button::HandleFocusedEvent( const sf::Event& iEvent )
	{
		if(iEvent.Type == sf::Event::MouseButtonReleased)
		{
			if(ConsoleManager::Get()->HasArgs(mOnPressExec))
			{
				ConsoleManager::Get()->RunExec(mOnPressExec, mOnPressExecParam);
			}
			else
			{
				ConsoleManager::Get()->RunExec(mOnPressExec);
			}

			return true;
		}

		return false;
	}

	void Button::MouseEnter()
	{
		SetResource(mHoverResource);
	}

	void Button::MouseLeave()
	{
		SetResource(mNormalResource);
	}
}