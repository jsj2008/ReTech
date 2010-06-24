#include "ReTechCommonIncludes.h"
#include "ReTechSequence.h"

#include "ReTechResourceManager.h"
#include "ReTechCollectionIterator.h"

namespace rt
{
	Sequence::Sequence()
		: mDefaultFrameImageName("./media/default/no_texture.tga")
	{

	}

	Sequence::Sequence( const std::string& iResourceName )
		: mDefaultFrameImageName("./media/default/no_texture.tga")
	{
		Initialize(iResourceName);
	}

	Sequence::~Sequence()
	{

	}

	void Sequence::Load()
	{
		if(!IsLoaded())
		{
			CollectionIterator frames(mResourceName);

			while(!frames.End())
			{
				std::string frameFile;
				frames.SafeGet("file", frameFile);

				if(!frameFile.empty())
				{
					mFrames.push_back(UResource(Image, frameFile));
				}
				
				frames.Next();
			}
		}
	}

	void Sequence::Unload()
	{
		mFrames.clear();
	}

	bool Sequence::IsLoaded()
	{
		return !mFrames.empty();
	}

	Image* Sequence::Frame( int iFrameIndex )
	{
		return mFrames[iFrameIndex];
	}

	int Sequence::Lenght()
	{
		return mFrames.size();
	}
}