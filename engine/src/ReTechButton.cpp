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

		boost::char_separator<char> sep(" ");
		boost::tokenizer<boost::char_separator<char>> tokenizer(mOnPressExec, sep);
		std::vector<std::string> tokens;

		std::copy(tokenizer.begin(), tokenizer.end(), std::back_inserter(tokens));

		if(tokens.size() == 2)
		{
			mOnPressExec = tokens[0];
			mOnPressExecParam = tokens[1];
		}

		SafeGet(iNode, "normal", mNormalResource);
		SafeGet(iNode, "hover", mHoverResource);

		SetResource(mNormalResource);
	}

	void Button::Serialize( YAML::Emitter& iEmitter )
	{
		WorldObject::Serialize(iEmitter);
	}

	bool Button::IsPointInside( const sf::Vector2f& iMousePos )
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