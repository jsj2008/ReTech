#include "rtCommonIncludes.h"
#include "rtPhysicsManager.h"
#include "rtOptionsManager.h"

URegisterSingleton(PhysicsManager)

namespace rt
{
	PhysicsManager::PhysicsManager()
		: mStepTime(30.0f), mBufferedTime(0.0f)
	{
		cpInitChipmunk();
	}

	PhysicsManager::~PhysicsManager()
	{

	}

	void PhysicsManager::Update( float iTimeElapsed )
	{
		mSpaces.erase(std::remove(mSpaces.begin(), mSpaces.end(), static_cast<cpSpace*>(0)), mSpaces.end());

		mBufferedTime += iTimeElapsed;

		while(mBufferedTime >= mStepTime)
		{
			mBufferedTime -= mStepTime;

			for(SpaceVecIter iter = mSpaces.begin(); iter != mSpaces.end(); ++iter)
			{
				cpSpaceStep(*iter, mStepTime);
			}
		}
	}

	cpSpace* PhysicsManager::CreatePhysicsSpace()
	{
		cpSpace* newSpace = cpSpaceNew();
		mSpaces.push_back(newSpace);

		return newSpace;
	}

	void PhysicsManager::DestroyPhysicsSpace(cpSpace* iSpace)
	{
		SpaceVecIter finded = std::find(mSpaces.begin(), mSpaces.end(), iSpace);

		if(finded != mSpaces.end())
		{
			cpSpaceFree(*finded);
			*finded = 0;
		}
	}

	void PhysicsManager::SetStepTime(float iTime)
	{
		mStepTime = iTime;
	}

	float PhysicsManager::GetStepTime()
	{
		return mStepTime;
	}
}