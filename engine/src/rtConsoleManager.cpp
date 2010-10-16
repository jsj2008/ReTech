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
#include "rtConsoleManager.h"

URegisterSingleton(ConsoleManager)

namespace rt
{
	ConsoleManager::ConsoleManager()
	{

	}

	ConsoleManager::~ConsoleManager()
	{

	}

	void ConsoleManager::RegisterCommand( const std::string& iName, camp::UserObject iObject, const std::string& iFunction )
	{
		if(mCommands.find(iName) != mCommands.end())
		{
			//TODO log
			return;
		}

		CommandDesc newCommand;

		newCommand.mName = iName;
		newCommand.mObject = iObject;
		newCommand.mFunction = iFunction;

		mCommands[iName] = newCommand;
	}

	void ConsoleManager::CallCommand( const std::string& iName, const camp::Args& iArgs/* = camp::Args::empty*/ )
	{
		if(mCommands.find(iName) == mCommands.end())
		{
			//TODO log
			return;
		}

		mCommands[iName].mObject.call(mCommands[iName].mFunction, iArgs);
	}

	void ConsoleManager::ParseCommand( const std::string& iCommandString )
	{
		CallCommand(iCommandString);
	}

	bool ConsoleManager::HasArguments( const std::string& iName )
	{
		if(mCommands.find(iName) == mCommands.end())
		{
			//TODO log
			return false;
		}

		return mCommands[iName].mObject.getClass().function(mCommands[iName].mFunction).argCount() != 0;
	}
}