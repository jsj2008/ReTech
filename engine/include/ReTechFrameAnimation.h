#ifndef __rtFrameAnimation_H__
#define __rtFrameAnimation_H__

namespace rt
{
	class Sequence;

	class FrameAnimation
	{
	public:
		FrameAnimation(const std::string& iAnimationName, sf::Sprite* iTargetSprite);
		~FrameAnimation();

		void Update(float iFrameTime);

	protected:
		Sequence*	mSequenceResource;

		sf::Sprite*	mTargetSprite;

		float		mFrameTime;
		float		mElapsedTime;
		int			mCurrentFrame;
		int			mMaxFrame;
	};
}

#endif