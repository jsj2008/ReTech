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

		void SetFocusLock(bool iFocusLock);

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
		bool isHandledByFocused(const sf::Event& iEvent);

		void updateFocused();

		KeyboardBinds					mUnaryKeyboardBinds;
		KeyboardBinds					mBinaryKeyboardBinds;
		MouseBinds						mUnaryMouseBinds;
		MouseBinds						mBinaryMouseBinds;

		HandlersList					mHandlers;

		boost::weak_ptr<WorldObject>	mFocusedObject;

		bool							mFocusLock;
	};
}

#endif