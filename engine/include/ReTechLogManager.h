#ifndef __rtLogManager_H__
#define __rtLogManager_H__

#include "ReTechSingleton.h"

namespace rt
{
	class LogManager : public Singleton<LogManager>
	{
	public:
		LogManager();
		~LogManager();

		void Initialize();

		void Error(const std::string& iMessage);
		void Warning(const std::string& iMessage);
		void Notice(const std::string& iMessage);

	protected:
		std::ofstream mFileStream;
	};
}

#endif