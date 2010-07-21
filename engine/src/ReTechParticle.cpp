#include "ReTechCommonIncludes.h"
#include "ReTechParticle.h"

namespace rt
{
	Particle::Particle()
		: mSystem(0)
	{

	}

	Particle::Particle( const std::string& iResourceName )
		: mSystem(0)
	{
		Initialize(iResourceName);
	}

	Particle::~Particle()
	{

	}

	void Particle::Load()
	{
		if(!IsLoaded())
		{
			// Creates the model
			SPK::Model* sparkModel = SPK::Model::create(
				SPK::FLAG_GREEN | SPK::FLAG_ALPHA, SPK::FLAG_GREEN, SPK::FLAG_GREEN);
			sparkModel->setParam(SPK::PARAM_RED, 0.0f);
			sparkModel->setParam(SPK::PARAM_GREEN, 0.5f, 1.0f, 0.0f, 0.1f);
			sparkModel->setParam(SPK::PARAM_BLUE,0.0f);
			sparkModel->setParam(SPK::PARAM_ALPHA,1.0f);
			sparkModel->setLifeTime(0.2f, 0.6f);
			// Creates the renderer
			SPK::SFML::SFMLLineRenderer* sparkRenderer = SPK::SFML::SFMLLineRenderer::create(0.1f, 1.0f);
			sparkRenderer->setBlendMode(sf::Blend::Add);
			sparkRenderer->setGroundCulling(true);
			// Creates the zone
			SPK::Sphere* sparkSource = SPK::Sphere::create(SPK::Vector3D(0.0f,0.0f,10.0f), 5.0f);
			// Creates the emitter
			SPK::SphericEmitter* sparkEmitter = 
				SPK::SphericEmitter::create(SPK::Vector3D(0.0f,0.0f,1.0f),3.14159f / 4.0f,3.0f * 3.14159f / 4.0f);
			sparkEmitter->setForce(100.0f,250.0f);
			sparkEmitter->setZone(sparkSource);
			sparkEmitter->setTank(-1);
			sparkEmitter->setFlow(150);

			// Creates the Group
			SPK::Group* sparkGroup = SPK::Group::create(sparkModel,2500);
			sparkGroup->setRenderer(sparkRenderer);
			sparkGroup->addEmitter(sparkEmitter);
			sparkGroup->setGravity(SPK::Vector3D(0.0f,0.0f,-200.0f));
			sparkGroup->setFriction(0.0f);

			// Creates the System
			mSystem = SPK::SFML::SFMLSystem::create();
			mSystem->addGroup(sparkGroup);

			// Defines which objects will be shared by all systems
			sparkModel->setShared(true);
			sparkRenderer->setShared(true);
		}
	}

	void Particle::Unload()
	{
		SPK_Destroy(mSystem);
		mSystem = 0;
	}

	bool Particle::IsLoaded()
	{
		return mSystem != 0;
	}

	SPK::SPK_ID Particle::GetSystemID()
	{
		if(mSystem)
		{
			return mSystem->getID();
		}
		else
		{
			return -1;
		}
	}
}