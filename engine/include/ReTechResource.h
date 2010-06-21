#ifndef __rtResource_H__
#define __rtResource_H__

#include "ReTechSerializeable.h"

namespace rt
{
	class Resource : public Serializeable
	{
	public:
		Resource();
		virtual ~Resource();

		void Initialize(const std::string& iResourceName);

		virtual void Load() = 0;
		virtual void Unload() = 0;

		void Reload();

		virtual bool IsLoaded() = 0;

	protected:
			std::string mResourceName;
	};
}

#endif