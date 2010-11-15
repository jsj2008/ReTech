#include "rtCommonIncludes.h"
#include "rtPhysicsManager.h"
#include "rtOptionsManager.h"

URegisterSingleton(PhysicsManager)

namespace rt
{
	PhysicsManager::PhysicsManager()
	{
		cpInitChipmunk();
	}

	PhysicsManager::~PhysicsManager()
	{

	}

	void PhysicsManager::Update( float iTimeElapsed )
	{

	}
}