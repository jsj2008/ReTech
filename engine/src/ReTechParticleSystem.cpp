#include "ReTechCommonIncludes.h"
#include "ReTechParticleSystem.h"

#include "ReTechParticle.h"

namespace rt
{
	ParticleSystem::ParticleSystem()
		: mSystem(0)
	{
	}

	ParticleSystem::~ParticleSystem()
	{
		SPK_Destroy(mSystem);
	}

	void ParticleSystem::UnSerialize( const YAML::Node& iNode )
	{
		WorldObject::UnSerialize(iNode);

		SafeGet(iNode, "particle", fastdelegate::MakeDelegate(this, &ParticleSystem::SetResource));
	}

	void ParticleSystem::Serialize( YAML::Emitter& iEmitter ) const
	{

	}

	void ParticleSystem::Update( float iFrameTime )
	{
		if(mSystem)
		{
 			mSystem->SetPosition(GetPosition());
  			mSystem->SetScale(GetScale());
  			mSystem->SetOrigin(GetOrigin());
  			mSystem->SetRotation(GetRotation());

			mSystem->update(iFrameTime * 0.1f);
		}
	}

	void ParticleSystem::Draw( sf::RenderWindow* iRenderWindow )
	{
		if(mSystem)
		{
			iRenderWindow->SaveGLStates();
			iRenderWindow->Draw(*mSystem);
			iRenderWindow->Draw(*mSystem);
			iRenderWindow->RestoreGLStates();
		}
	}

	void ParticleSystem::SetResource( const std::string& iResourceName )
	{
		Particle* resourceParticle = UResource(Particle, iResourceName);
		if(resourceParticle)
		{
			resourceParticle->Load();
			mSystem = SPK_Copy(SPK::SFML::SFMLSystem, resourceParticle->GetSystemID());
		}
	}
}