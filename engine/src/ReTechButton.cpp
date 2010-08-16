#include "ReTechCommonIncludes.h"
#include "ReTechButton.h"
#include "ReTechConsoleManager.h"

namespace rt
{
	Button::Button()
		: mIsMouseOver(false)
	{
		mClassName = "Button";

		mHandler = InputManager::MakeHandler(&Button::HandleEvent, this);
		InputManager::Get()->RegisterHandler(&mHandler);
	}

	Button::~Button()
	{
		InputManager::Get()->UnregisterHandler(&mHandler);
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

	bool Button::IsInside(const sf::Vector2f& iPoint)
	{
		return sf::FloatRect(GetPosition(), mSprite.GetSize()).Contains(iPoint);
	}

	bool Button::HandleEvent(const sf::Event& iEvent)
	{
		if(iEvent.Type == sf::Event::MouseMoved)
		{
			if(mIsMouseOver != IsInside(WorldsManager::Get()->ScreenToWorld(iEvent.MouseMove.X, iEvent.MouseMove.Y)))
			{
				mIsMouseOver = !mIsMouseOver;

				if(mIsMouseOver)
				{
					SetResource(mHoverResource);
				}
				else
				{
					SetResource(mNormalResource);
				}
			}
		}
		else if(iEvent.Type == sf::Event::MouseButtonReleased)
		{
			if(IsInside(WorldsManager::Get()->ScreenToWorld(iEvent.MouseButton.X, iEvent.MouseButton.Y)))
			{
				if(ConsoleManager::Get()->HasArgs(mOnPressExec))
				{
					ConsoleManager::Get()->RunExec(mOnPressExec, mOnPressExecParam);
				}
				else
				{
					ConsoleManager::Get()->RunExec(mOnPressExec);
				}
			}
		}

		return false;
	}
}