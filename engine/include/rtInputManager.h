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

#include "rtSingleton.h"

namespace rt
{
	class InputManager : public Singleton<InputManager>
	{
	public:
		class ExecHolder
		{
		public:
			std::string FunctionName;
			camp::Args	FunctionArguments;
			bool		PredefinedArguments;
		};

		typedef std::multimap<sf::Key::Code, ExecHolder>			KeyboardBinds;
		typedef KeyboardBinds::iterator								KeyboardBindsIter;
		typedef std::multimap<sf::Mouse::Button, ExecHolder>		MouseBinds;
		typedef MouseBinds::iterator								MouseBindsIter;

		typedef fastdelegate::FastDelegate1<const sf::Event&, bool>	InputHandler;
		typedef std::list<InputHandler*>							HandlersList;

		typedef boost::shared_ptr<InputManager>						Ptr;

		InputManager();
		~InputManager();

		void Update(float iFrameTime);

		void RegisterBind(sf::Key::Code iKey, const std::string& iExecName, const camp::Args& iArguments = camp::Args::empty);
		void RegisterBind(sf::Mouse::Button iButton, const std::string& iExecName, const camp::Args& iArguments = camp::Args::empty);

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
		void processKey(sf::Key::Code iKey, bool iPressed);
		void processMouse(sf::Mouse::Button iButton, bool iPressed);

		bool isHandledByExternals(const sf::Event& iEvent);

		KeyboardBinds					mKeyboardBinds;
		MouseBinds						mMouseBinds;

		HandlersList					mHandlers;
	};
}

#endif