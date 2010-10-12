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
#include "ReTechInputManager.h"
#include "ReTechConsoleManager.h"
#include "ReTechRenderManager.h"
#include "ReTechWorldObject.h"

URegisterSingleton(InputManager);

namespace rt
{
	InputManager::InputManager()
		: mFocusLock(false)
	{

	}

	InputManager::~InputManager()
	{

	}

	void InputManager::Update( float iFrameTime )
	{
		updateFocused();

		// Process events
		sf::Event Event;
		while (GameCore::Get()->GetMainWindow()->GetEvent(Event))
		{
			if(!isHandledByFocused(Event) && !isHandledByExternals(Event))
			{
				// Close window : exit
				if (Event.Type == sf::Event::Closed)
					GameCore::Get()->Stop();

				//Process binds
				if(Event.Type == sf::Event::KeyPressed)
				{
					processBinary(Event.Key.Code, true, mBinaryKeyboardBinds);
				}
				else if(Event.Type == sf::Event::KeyReleased)
				{
					processUnary(Event.Key.Code, mUnaryKeyboardBinds);
					processBinary(Event.Key.Code, false, mBinaryKeyboardBinds);
				}
				else if(Event.Type == sf::Event::MouseButtonPressed)
				{
					processBinary(Event.MouseButton.Button, true, mBinaryMouseBinds);
				}
				else if(Event.Type == sf::Event::MouseButtonReleased)
				{
					processUnary(Event.MouseButton.Button, mUnaryMouseBinds);
					processBinary(Event.MouseButton.Button, false, mBinaryMouseBinds);
				}
			}
		}
	}

	void InputManager::RegisterBind( sf::Key::Code iKey, const std::string& iExecName)
	{
		if(!ConsoleManager::Get()->HasArgs(iExecName))
		{
			mUnaryKeyboardBinds.insert(std::make_pair(iKey, iExecName));
		}
		else
		{
			mBinaryKeyboardBinds.insert(std::make_pair(iKey, iExecName));
		}
		
	}

	void InputManager::RegisterBind( sf::Mouse::Button iButton, const std::string& iExecName)
	{
		if(!ConsoleManager::Get()->HasArgs(iExecName))
		{
			mUnaryMouseBinds.insert(std::make_pair(iButton, iExecName));
		}
		else
		{
			mBinaryMouseBinds.insert(std::make_pair(iButton, iExecName));
		}
	}	

	void InputManager::UnregisterBind( sf::Key::Code iKey )
	{
		mUnaryKeyboardBinds.erase(iKey);
		mBinaryKeyboardBinds.erase(iKey);
	}

	void InputManager::UnregisterBind( sf::Mouse::Button iButton )
	{
		mUnaryMouseBinds.erase(iButton);
		mBinaryMouseBinds.erase(iButton);
	}

	void InputManager::RegisterHandler( InputHandler* iHandler )
	{
 		if(std::find(mHandlers.begin(), mHandlers.end(), iHandler) != mHandlers.end())
 		{
 			LogManager::Get()->Warning("Handler already registered");
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

	void InputManager::SetFocusLock( bool iFocusLock )
	{
		mFocusLock = iFocusLock;
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

	bool InputManager::isHandledByFocused( const sf::Event& iEvent )
	{
		return !mFocusedObject.expired() ? mFocusedObject.lock()->HandleFocusedEvent(iEvent) : false;
	}

	void InputManager::updateFocused()
	{
		if(!mFocusLock)
		{
			sf::Vector2f mousePos = GetMousePosition();
			RenderManager::WorldObjectsVec visibleObjects = RenderManager::Get()->GetVisibleObjectsCache();

			boost::weak_ptr<WorldObject> newFocused;

			for(RenderManager::WorldObjectsVec::reverse_iterator iter = visibleObjects.rbegin(); iter != visibleObjects.rend(); ++iter)
			{
				if((*iter).lock()->IsPointInside(mousePos))
				{
					newFocused = (*iter);
					break;
				}
			}

			if(newFocused.lock() != mFocusedObject.lock())
			{
				if(!mFocusedObject.expired())
				{
					mFocusedObject.lock()->MouseLeave();
				}

				if(!newFocused.expired())
				{
					newFocused.lock()->MouseEnter();
				}

				mFocusedObject = newFocused;
			}
		}
	}
}