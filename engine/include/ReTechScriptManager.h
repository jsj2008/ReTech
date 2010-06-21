#ifndef __rtScriptManager_H__
#define __rtScriptManager_H__

#include "ReTechSingleton.h"

namespace rt
{
	class ScriptManager : public Singleton<ScriptManager>
	{
		public:
			ScriptManager();
			~ScriptManager();

			void MessageCallback(const asSMessageInfo* iMessage);

	protected:
		asIScriptEngine* mEngine;
		asIScriptModule* mMainModule;
	};
}

#endif