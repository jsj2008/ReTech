#ifndef __rtParticleSystem_H__
#define __rtParticleSystem_H__

#include "ReTechWorldObject.h"

namespace rt
{
	class ParticleSystem : public WorldObject
	{
	public:
		ParticleSystem();
		virtual ~ParticleSystem();

		virtual void Update(float iFrameTime);
		virtual void Draw(sf::RenderWindow* iRenderWindow);

		void SetResource(const std::string& iResourceName);
		const std::string& GetResource();

	protected:
		SPK::SFML::SFMLSystem* mSystem;

		std::string mResourceName;
	};
}

#endif