#ifndef __rtImage_H__
#define __rtImage_H__

#include "ReTechResource.h"

namespace rt
{
	class Image : public Resource, public sf::Image
	{
	public:
		Image();
		Image(const std::string& iResourceName);
		virtual ~Image();

		virtual void Load();
		virtual void Unload();

		virtual bool IsLoaded();

	protected:
		std::string mDefaultResourceName;
	};
}

#endif