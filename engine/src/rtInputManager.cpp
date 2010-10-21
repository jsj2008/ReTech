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

#include "rtCommonIncludes.h"
#include "rtInputManager.h"
#include "rtConsoleManager.h"
#include "rtRenderManager.h"
#include "rtWorldObject.h"
#include "rtGuiManager.h"
#include "rtToolManager.h"

URegisterSingleton(InputManager);

namespace rt
{
	InputManager::InputManager()
	{

	}

	InputManager::~InputManager()
	{

	}

	void InputManager::Update( float iFrameTime )
	{
		// Process events
		sf::Event Event;
		while (GameCore::Get()->GetMainWindow()->GetEvent(Event))
		{
			if(!ToolManager::Get()->HandleEvent(Event) && !GuiManager::Get()->HandleEvent(Event) && !isHandledByExternals(Event))
			{
				// Close window : exit
				if (Event.Type == sf::Event::Closed)
					GameCore::Get()->Stop();

				//Process binds
				if(Event.Type == sf::Event::KeyPressed)
				{
					processKey(Event.Key.Code, true);
				}
				else if(Event.Type == sf::Event::KeyReleased)
				{
					processKey(Event.Key.Code, false);
				}
				else if(Event.Type == sf::Event::MouseButtonPressed)
				{
					processMouse(Event.MouseButton.Button, true);
				}
				else if(Event.Type == sf::Event::MouseButtonReleased)
				{
					processMouse(Event.MouseButton.Button, false);
				}
			}
		}
	}

	void InputManager::RegisterBind( sf::Key::Code iKey, const std::string& iExecName)
	{
		mKeyboardBinds.insert(std::make_pair(iKey, iExecName));
	}

	void InputManager::RegisterBind( sf::Mouse::Button iButton, const std::string& iExecName)
	{
		mMouseBinds.insert(std::make_pair(iButton, iExecName));
	}	

	void InputManager::UnregisterBind( sf::Key::Code iKey )
	{
		mKeyboardBinds.erase(iKey);
	}

	void InputManager::UnregisterBind( sf::Mouse::Button iButton )
	{
		mMouseBinds.erase(iButton);
	}

	void InputManager::RegisterHandler( InputHandler* iHandler )
	{
 		if(std::find(mHandlers.begin(), mHandlers.end(), iHandler) != mHandlers.end())
 		{
 			ULogWarning("Handler already registered");
 			return;
 		}

		mHandlers.push_back(iHandler);
	}

	void InputManager::UnregisterHandler( InputHandler* iHandler )
	{
		HandlersList::iterator findedHandler = std::find(mHandlers.begin(), mHandlers.end(), iHandler);
		if(findedHandler != mHandlers.end())
		{
			(*findedHandler) = 0;
		}
	}

	sf::Vector2f InputManager::GetMousePosition()
	{
		return WorldsManager::Get()->ScreenToWorld(GameCore::Get()->GetMainWindow()->GetInput().GetMouseX(), GameCore::Get()->GetMainWindow()->GetInput().GetMouseY());
	}

	bool InputManager::isHandledByExternals(const sf::Event& iEvent)
	{
		mHandlers.erase(std::remove(mHandlers.begin(), mHandlers.end(), static_cast<InputHandler*>(0)), mHandlers.end());

		HandlersList::iterator end = mHandlers.end();

		for(HandlersList::iterator iter = mHandlers.begin(); iter != end; ++iter)
		{
			if((*iter) != 0 && (*(*iter))(iEvent))
			{
				return true;
			}
		}

		return false;
	}

	void InputManager::processKey( sf::Key::Code iKey, bool iPressed )
	{
		KeyboardBindsIter iter = mKeyboardBinds.find(iKey);

		if(iter != mKeyboardBinds.end())
		{
			KeyboardBindsIter end = mKeyboardBinds.upper_bound(iKey);

			for(;iter != end; ++iter)
			{
				if(!iter->second.empty())
				{
					if(iPressed && !ConsoleManager::Get()->HasArguments(iter->second))
					{
						continue;
					}

					ConsoleManager::Get()->CallCommand(iter->second, camp::Args(iPressed));
				}
			}
		}
	}

	void InputManager::processMouse( sf::Mouse::Button iButton, bool iPressed )
	{
		MouseBindsIter iter = mMouseBinds.find(iButton);

		if(iter != mMouseBinds.end())
		{
			MouseBindsIter end = mMouseBinds.upper_bound(iButton);

			for(;iter != end; ++iter)
			{
				if(!iter->second.empty())
				{
					if(iPressed && !ConsoleManager::Get()->HasArguments(iter->second))
					{
						continue;
					}

					ConsoleManager::Get()->CallCommand(iter->second, camp::Args(iPressed));
				}
			}
		}
	}
}