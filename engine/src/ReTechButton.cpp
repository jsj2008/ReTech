/*
Copyright (c) 2010 Alexander Novitsky                                             

Permission is hereby granted, free of charge, to any person obtaining a copy  
of this software and associated documentation files (the "Software"), to deal 
in the Software without restriction, including without limitation the rights  
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell     
copies of the Software, and to permit persons to whom the Software is         
furnished to do so, subject to the following conditions:                      

The above copyright notice and this permission notice shall be included in    
all copies or substantial portions of the Software.                           

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR    
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,      
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE   
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER        
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN     
THE SOFTWARE.
*/

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