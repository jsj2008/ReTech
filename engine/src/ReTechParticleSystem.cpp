#include "ReTechCommonIncludes.h"
#include "ReTechParticleSystem.h"

namespace rt
{
	ParticleSystem::ParticleSystem()
		: mSystem(0)
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

		mSystem2 = SPK::SFML::SFMLSystem::create();
		mSystem2->addGroup(sparkGroup);

		// Defines which objects will be shared by all systems
		sparkModel->setShared(true);
		sparkRenderer->setShared(true);
		sparkEmitter->setShared(true);
		sparkGroup->setShared(true);
	}

	ParticleSystem::~ParticleSystem()
	{
		SPK_Destroy(mSystem);
	}

	void ParticleSystem::UnSerialize( const YAML::Node& iNode )
	{
		WorldObject::UnSerialize(iNode);
	}

	void ParticleSystem::Serialize( YAML::Emitter& iEmitter ) const
	{

	}

	void ParticleSystem::Update( float iFrameTime )
	{
		//SetPosition(sf::Randomizer::Random(0, 1280), sf::Randomizer::Random(0, 720));

		if(mSystem)
		{
 			mSystem->SetPosition(GetPosition());
  			mSystem->SetScale(GetScale());
  			mSystem->SetOrigin(GetOrigin());
  			mSystem->SetRotation(GetRotation());

			mSystem2->SetPosition(GetPosition() + sf::Vector2f(200, 0));

			mSystem->update(iFrameTime * 0.1f);
			mSystem2->update(iFrameTime * 0.1f);
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
}