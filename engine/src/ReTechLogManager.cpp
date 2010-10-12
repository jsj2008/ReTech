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
#include "ReTechLogManager.h"

URegisterSingleton(LogManager)

namespace rt
{
	LogManager::LogManager()
	{
	}

	LogManager::~LogManager()
	{
		if(mFileStream.is_open())
		{
			mFileStream.close();
		}
	}

	void LogManager::Initialize()
	{
		mFileStream.open("game.log");
	}

	void LogManager::Error( const std::string& iMessage )
	{
		if(mFileStream.is_open())
		{
			mFileStream << "ERROR:\t" << iMessage << "\n";
		}
	}

	void LogManager::Warning( const std::string& iMessage )
	{
		if(mFileStream.is_open())
		{
			mFileStream << "WARNING:\t" << iMessage << "\n";
		}
	}

	void LogManager::Notice( const std::string& iMessage )
	{
		if(mFileStream.is_open())
		{
			mFileStream << "NOTICE:\t" << iMessage << "\n";
		}
	}
}