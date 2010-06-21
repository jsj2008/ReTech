#include "ReTechCommonIncludes.h"
#include "ReTechFrameAnimation.h"
#include "ReTechResourceManager.h"
#include "ReTechSequence.h"

namespace rt
{
	FrameAnimation::FrameAnimation( const std::string& iAnimationName, sf::Sprite* iTargetSprite )
		: mTargetSprite(iTargetSprite), mFrameTime(0.4f), mElapsedTime(0.0f), mCurrentFrame(0), mMaxFrame(0)
	{
		mSequenceResource = UResource(Sequence, iAnimationName);

		mSequenceResource->Load();

		mMaxFrame = mSequenceResource->Lenght();

		Image* imageResource = mSequenceResource->Frame(mCurrentFrame);
		if(!imageResource->IsLoaded())
		{
			imageResource->Load();
		}

		mTargetSprite->SetImage(*imageResource);
	}

	FrameAnimation::~FrameAnimation()
	{

	}

	void FrameAnimation::Update( float iFrameTime )
	{
		mElapsedTime += iFrameTime;

		if(mElapsedTime > mFrameTime)
		{
			mElapsedTime -= mFrameTime;

			++mCurrentFrame;

			if(mCurrentFrame >= mMaxFrame)
			{
				mCurrentFrame = 0;
			}

			Image* imageResource = mSequenceResource->Frame(mCurrentFrame);
			if(!imageResource->IsLoaded())
			{
				imageResource->Load();
			}

			mTargetSprite->SetImage(*imageResource);
		}
	}
}