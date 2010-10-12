/*
Copyright (c) 2010 Alexander Novitsky                                             

Permission is hereby granted, free of charge, to any person obtaining a copy  
of this software and associated documentation files (the "Software"), to deal 
in the Software without restriction, including without limitation the rights  
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell     
copies of the Software, and to permit persons to whom the Software is         
furnished to do so, subject to the following conditions:                      

The above copyright notice and this permission notice shall be included in    
all copies or substantial portions of the Software.                           

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR    
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,      
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE   
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER        
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN     
THE SOFTWARE.
*/

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