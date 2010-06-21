#include "ReTechCommonIncludes.h"
#include "ReTechScriptManager.h"

URegisterSingleton(ScriptManager)

namespace rt
{
	ScriptManager::ScriptManager()
		: mEngine(0)
	{
		mEngine = asCreateScriptEngine(ANGELSCRIPT_VERSION);
		mEngine->SetMessageCallback(asMETHOD(ScriptManager,MessageCallback), this, asCALL_THISCALL);

		mMainModule = mEngine->GetModule("main", asGM_ALWAYS_CREATE);

		Poco::FileInputStream fileStream("test.as");
		std::string test;
		std::string buf;

		while(std::getline(fileStream, buf))
		{
			test += '\n' + buf;
		}

		mMainModule->AddScriptSection("section1", test.c_str());

		int r = mMainModule->Build();

		mEngine->mo
	}

	ScriptManager::~ScriptManager()
	{

	}

	void ScriptManager::MessageCallback(const asSMessageInfo* iMessage)
	{
		const char *type = "ERR ";
		if( iMessage->type == asMSGTYPE_WARNING ) 
			type = "WARN";
		else if( iMessage->type == asMSGTYPE_INFORMATION ) 
			type = "INFO";
		printf("%s (%d, %d) : %s : %s\n", iMessage->section, iMessage->row, iMessage->col, type, iMessage->message);

	}
}