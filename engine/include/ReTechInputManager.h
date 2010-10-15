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

#ifndef __rtInputManager_H__
#define __rtInputManager_H__

#include "ReTechSingleton.h"

namespace rt
{
	class InputManager : public Singleton<InputManager>
	{
	public:
		typedef std::multimap<sf::Key::Code, std::string>			KeyboardBinds;
		typedef std::multimap<sf::Mouse::Button, std::string>		MouseBinds;
		typedef fastdelegate::FastDelegate1<const sf::Event&, bool>	InputHandler;
		typedef std::list<InputHandler*>							HandlersList;

		typedef boost::shared_ptr<InputManager>						Ptr;

		InputManager();
		~InputManager();

		void Update(float iFrameTime);

		void RegisterBind(sf::Key::Code iKey, const std::string& iExecName);
		void RegisterBind(sf::Mouse::Button iButton, const std::string& iExecName);

		void UnregisterBind(sf::Key::Code iKey);
		void UnregisterBind(sf::Mouse::Button iButton);

		void RegisterHandler(InputHandler* iHandler);
		void UnregisterHandler(InputHandler* iHandler);

		template<class T>
		static InputHandler MakeHandler(bool(T::*iFunc)(const sf::Event&), T* iObject)
		{
			return fastdelegate::MakeDelegate(iObject, iFunc);
		}

		sf::Vector2f GetMousePosition();

	protected:
		template <class T>
		void processUnary(T iKey, std::multimap<T, std::string>& iStorage)
		{
			std::multimap<T, std::string>::iterator iter = iStorage.find(iKey);

			if(iter != iStorage.end())
			{
				std::multimap<T, std::string>::iterator end = iStorage.upper_bound(iKey);

				for(;iter != end; ++iter)
				{
					if(!iter->second.empty())
					{
						ConsoleManager::Get()->RunExec(iter->second);
					}
				}
			}
		}

		template <class T>
		void processBinary(T iKey, bool iSwitch, std::multimap<T, std::string>& iStorage)
		{
			std::multimap<T, std::string>::iterator iter = iStorage.find(iKey);

			if(iter != iStorage.end())
			{
				std::multimap<T, std::string>::iterator end = iStorage.upper_bound(iKey);

				for(;iter != end; ++iter)
				{
					if(!iter->second.empty())
					{
						ConsoleManager::Get()->RunExec(iter->second, iSwitch);
					}
				}
			}
		}

		bool isHandledByExternals(const sf::Event& iEvent);

		KeyboardBinds					mUnaryKeyboardBinds;
		KeyboardBinds					mBinaryKeyboardBinds;
		MouseBinds						mUnaryMouseBinds;
		MouseBinds						mBinaryMouseBinds;

		HandlersList					mHandlers;
	};
}

#endif