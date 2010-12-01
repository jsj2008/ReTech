#pragma once

#include "rtSingleton.h"

namespace rt
{
	class MemoryManager : public Singleton<MemoryManager>
	{
	public:
		MemoryManager();
		~MemoryManager();

		
	};
}