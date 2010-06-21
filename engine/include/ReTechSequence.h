#ifndef __rtSequence_H__
#define __rtSequence_H__

#include "ReTechResource.h"
#include "ReTechImage.h"

namespace rt
{
	class Sequence : public Resource
	{
	public:
		typedef std::vector<Image*> FramesVect;

		Sequence();
		Sequence(const std::string& iResourceName);
		virtual ~Sequence();

		virtual void Load();
		virtual void Unload();

		virtual bool IsLoaded();

		Image* Frame(int iFrameIndex);
		int Lenght();

	protected:
		FramesVect	mFrames;

		std::string mDefaultFrameImageName;
	};
}

#endif