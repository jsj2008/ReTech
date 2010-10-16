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

#pragma once

#include "rtSingleton.h"

namespace rt
{
	class ConsoleManager : public Singleton<ConsoleManager>
	{
	public:
		struct CommandDesc
		{
			std::string			mName;
			camp::UserObject	mObject;
			std::string			mFunction;
		};

		typedef std::map<std::string, CommandDesc>	CommandMap;
		typedef CommandMap::iterator				CommandMapIter;

		typedef boost::shared_ptr<ConsoleManager>	Ptr;

		ConsoleManager();
		~ConsoleManager();

		void RegisterCommand(const std::string& iName, camp::UserObject iObject, const std::string& iFunction);
		void CallCommand(const std::string& iName, const camp::Args& iArgs = camp::Args::empty);
		void ParseCommand(const std::string& iCommandString);

		bool HasArguments(const std::string& iName);

		static void RegisterMetaClass()
		{
			camp::Class::declare<ConsoleManager>("ConsoleManager")
				.constructor0();
		}

	protected:
		CommandMap mCommands;
	};
}

CAMP_AUTO_TYPE(rt::ConsoleManager, &rt::ConsoleManager::RegisterMetaClass)