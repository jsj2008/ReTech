#ifndef __rtConsoleManager_H__
#define __rtConsoleManager_H__

#include "ReTechSingleton.h"

namespace rt
{
	class ConsoleManager : public Singleton<ConsoleManager>
	{
	public:
		class BaseExec
		{
		public:
			BaseExec(bool iHasArgs)
				: mHasArgs(iHasArgs){}
			bool mHasArgs;
		};

		template<class T>
		class ExecHolder : public BaseExec
		{
		public:
			ExecHolder(boost::function< void(T) > iFunction)
				: mFunction(iFunction), BaseExec(true){}

			boost::function< void(T) >	mFunction;
		};

		template<>
		class ExecHolder<void> : public BaseExec
		{
		public:
			ExecHolder(boost::function< void(void) > iFunction)
				: mFunction(iFunction), BaseExec(false){}

			boost::function< void(void) >	mFunction;
		};

		typedef std::map<std::string, Poco::SharedPtr<BaseExec> > ExecMap;

		ConsoleManager();
		~ConsoleManager();

		template<class C>
		void RegisterExec(const std::string& iExecName, void(C::*iFunc)(void), C* iObject)
		{
			mExecs[iExecName].assign(new ExecHolder<void>(boost::bind(iFunc, iObject)));
		}

		template<class T, class C>
		void RegisterExec(const std::string& iExecName, void(C::*iFunc)(T), C* iObject)
		{
			mExecs[iExecName].assign(new ExecHolder<T>(boost::bind(iFunc, iObject, _1)));
		}

		void RunExec(const std::string& iExecName)
		{
			if(mExecs.find(iExecName) != mExecs.end())
			{
				reinterpret_cast<ExecHolder<void>* >(mExecs[iExecName].get())->mFunction();
			}
		}

		template<class T>
		void RunExec(const std::string& iExecName, T iValue)
		{
			if(mExecs.find(iExecName) != mExecs.end())
			{
				reinterpret_cast<ExecHolder<T>* >(mExecs[iExecName].get())->mFunction(iValue);
			}
		}

		bool HasArgs(const std::string& iExecName)
		{
			if(mExecs.find(iExecName) != mExecs.end())
			{
				return mExecs[iExecName]->mHasArgs;
			}

			return false;
		}

	protected:
		ExecMap	mExecs;
	};
}

#endif