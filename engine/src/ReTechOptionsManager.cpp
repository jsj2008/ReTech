#include "ReTechCommonIncludes.h"
#include "ReTechOptionsManager.h"

URegisterSingleton(OptionsManager)

namespace rt
{
	OptionsManager::OptionsManager()
	{

	}

	OptionsManager::~OptionsManager()
	{

	}

	Option& OptionsManager::GetOption( const std::string& iName )
	{
		return mOptions[iName];
	}
}