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
#include "rtConsole.h"
#include "ReTechGameCore.h"
#include "ReTechConsoleManager.h"

namespace rt
{
	Console::Console(sf::Key::Code iToggleKey/* = sf::Key::Tilde*/)
		: mVisible(false), mToggleKeyCode(iToggleKey)
	{
		mBackgroundShape = sf::Shape::Rectangle(sf::FloatRect(0.0f, 0.0f, 
			static_cast<float>(GameCore::Get()->GetMainWindow()->GetWidth()), static_cast<float>(GameCore::Get()->GetMainWindow()->GetHeight() * 0.5f)), 
			sf::Color(128, 128, 128, 128));

		mConsoleText.SetFont(sf::Font::GetDefaultFont());
		mConsoleText.SetCharacterSize(10);
		mConsoleText.SetColor(sf::Color(0, 255, 0, 200));

		mConsoleStrings.push_back(">");
	}

	Console::~Console()
	{

	}

	void Console::Render()
	{
		if(mVisible)
		{
			GameCore::Get()->GetMainWindow()->Draw(mBackgroundShape);

			float textHeightPos = GameCore::Get()->GetMainWindow()->GetHeight() * 0.5f;

			std::for_each(mConsoleStrings.begin(), mConsoleStrings.end(), [this,&textHeightPos](sf::String& iString)->void
			{
				if(textHeightPos > 0.0f)
				{
					textHeightPos -= 15.0f;

					mConsoleText.SetString(iString);
					mConsoleText.SetPosition(0.0f, textHeightPos);
					GameCore::Get()->GetMainWindow()->Draw(mConsoleText);
				}
			});
		}
	}

	bool Console::HandleEvent( const sf::Event& iEvent )
	{
		if(iEvent.Type == sf::Event::KeyPressed && iEvent.Key.Code == mToggleKeyCode)
		{
			ToggleConsole();
			return true;
		}

		if(mVisible && (iEvent.Type == sf::Event::KeyPressed || iEvent.Type == sf::Event::KeyReleased))
		{
			if(iEvent.Type == sf::Event::KeyPressed)
			{
				sf::String& consoleString = mConsoleStrings[0];
				if(iEvent.Key.Code == sf::Key::Back && consoleString.GetSize() > 1)
				{
					consoleString.Erase(consoleString.GetSize() - 1);
				}
				else if(iEvent.Key.Code == sf::Key::Return && consoleString.GetSize() > 1)
				{
					consoleString.Erase(0);
					ConsoleManager::Get()->RunExec(consoleString);

					mConsoleStrings.push_back("Try to execute:" + consoleString);
					mConsoleStrings[0] = ">";
				}
				else if((iEvent.Key.Code >= sf::Key::A && iEvent.Key.Code <= sf::Key::Z) || (iEvent.Key.Code >= sf::Key::Num0 && iEvent.Key.Code <= sf::Key::Num9))
				{
					consoleString.Insert(consoleString.GetSize(), static_cast<char>(iEvent.Key.Code));
				}
			}

			return true;
		}

		return false;
	}

	void Console::ToggleConsole()
	{
		mVisible = !mVisible;
	}
}