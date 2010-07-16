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

		virtual void UnSerialize(const YAML::Node& iNode);
		virtual void Serialize(YAML::Emitter& iEmitter) const;

		virtual void Update(float iFrameTime);
		virtual void Draw(sf::RenderWindow* iRenderWindow);

	protected:
		SPK::SFML::SFMLSystem* mSystem;
		SPK::SFML::SFMLSystem* mSystem2;
	};
}

#endif