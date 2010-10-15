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
			BaseExec(bool iHasArgs, bool iRefArg)
				: mHasArgs(iHasArgs), mRefArg(iRefArg){}
			bool mHasArgs;
			bool mRefArg;
		};

		template<class T>
		class ExecHolder : public BaseExec
		{
		public:
			ExecHolder(fastdelegate::FastDelegate1<T> iFunction)
				: mFunction(iFunction), BaseExec(true, false){}

			fastdelegate::FastDelegate1<T>	mFunction;
		};

		template<>
		class ExecHolder<void> : public BaseExec
		{
		public:
			ExecHolder(fastdelegate::FastDelegate0<> iFunction)
				: mFunction(iFunction), BaseExec(false, false){}

			fastdelegate::FastDelegate0<>	mFunction;
		};

		typedef std::map<std::string, boost::shared_ptr<BaseExec> > ExecMap;
		typedef ExecMap::iterator									ExecMapIter;

		typedef boost::shared_ptr<ConsoleManager>					Ptr;

		ConsoleManager();
		~ConsoleManager();

		template<class C>
		void RegisterExec(const std::string& iExecName, void(C::*iFunc)(void), C* iObject)
		{
			mExecs[iExecName].reset(new ExecHolder<void>(fastdelegate::MakeDelegate(iObject, iFunc)));
		}

		template<class T, class C>
		void RegisterExec(const std::string& iExecName, void(C::*iFunc)(T), C* iObject)
		{
			mExecs[iExecName].reset(new ExecHolder<T>(fastdelegate::FastDelegate1<T>(iObject, iFunc)));
		}

		template<class T, class C>
		void RegisterExec(const std::string& iExecName, void(C::*iFunc)(T&), C* iObject)
		{
			mExecs[iExecName].reset(new ExecHolder<T&>(fastdelegate::FastDelegate1<T&>(iObject, iFunc)));
			mExecs[iExecName]->mRefArg = true;
		}

		void RunExec(const std::string& iExecName)
		{
			if(mExecs.find(iExecName) != mExecs.end())
			{
				static_cast<ExecHolder<void>* >(mExecs[iExecName].get())->mFunction();
			}
		}

		template<class T>
		void RunExec(const std::string& iExecName, T iValue)
		{
			if(mExecs.find(iExecName) != mExecs.end())
			{
				if(mExecs[iExecName]->mRefArg)
				{
					static_cast<ExecHolder<T&>* >(mExecs[iExecName].get())->mFunction(iValue);
				}
				else
				{
					static_cast<ExecHolder<T>* >(mExecs[iExecName].get())->mFunction(iValue);
				}
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