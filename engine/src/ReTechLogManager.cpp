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