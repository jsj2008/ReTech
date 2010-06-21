#ifndef __rtOptionsManager_H__
#define __rtOptionsManager_H__

#include "ReTechSingleton.h"
#include "ReTechOption.h"

namespace rt
{
	class OptionsManager : public Singleton<OptionsManager>
	{
	public:
		typedef std::map<std::string, Option> OptionsMap;

		OptionsManager();
		~OptionsManager();

		Option& GetOption(const std::string& iName);

	protected:
		OptionsMap mOptions;
	};
}

#endif