#ifndef __rtParticle_H__
#define __rtParticle_H__

#include "ReTechResource.h"

namespace rt
{
	class Particle : public Resource
	{
	public:
		Particle();
		Particle(const std::string& iResourceName);
		virtual ~Particle();

		virtual void Load();
		virtual void Unload();

		virtual bool IsLoaded();

		SPK::SPK_ID GetSystemID();

	protected:
		SPK::SFML::SFMLSystem* mSystem;
	};
}

#endif