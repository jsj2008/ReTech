#include "ReTechCommonIncludes.h"
#include "ReTechButton.h"
#include "ReTechConsoleManager.h"

namespace rt
{
	Button::Button()
		: mIsMouseOver(false), mNormal(0), mHover(0)
	{
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
	}

	void Button::Serialize( YAML::Emitter& iEmitter ) const
	{

	}

	void Button::OnAddToWorld()
	{
		WorldObject::OnAddToWorld();

		mNormal = GetSubObjectByTag("normal");
		mHover = GetSubObjectByTag("hover");

		mHover->SetVisible(false);
	}

	bool Button::IsInside(const sf::Vector2f& iPoint)
	{
		return sf::FloatRect(GetInheritedWorldPosition(), GetWorldSize()).Contains(iPoint);
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
					mNormal->SetVisible(false);
					mHover->SetVisible(true);
				}
				else
				{
					mNormal->SetVisible(true);
					mHover->SetVisible(false);
				}
			}
		}
		else if(iEvent.Type == sf::Event::MouseButtonReleased)
		{
			if(IsInside(WorldsManager::Get()->ScreenToWorld(iEvent.MouseButton.X, iEvent.MouseButton.Y)))
			{
				ConsoleManager::Get()->RunExec(mOnPressExec);
			}
		}

		return false;
	}
}