#include "ReTechCommonIncludes.h"
#include "ReTechSequence.h"

#include "ReTechResourceManager.h"
#include "ReTechSerializer.h"

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
			Serializer serializer;
			serializer.SetFile(mResourceName);

			if(serializer.GetChunk().IsValid() && serializer.GetChunk().GetName() == "sequence")
			{
				if(serializer.GetChunk().HasSubChunks())
				{
					std::vector<DataChunk> dataChunks;

					serializer.GetChunk().GetSubChunks(dataChunks);
					
					for(std::vector<DataChunk>::iterator iter = dataChunks.begin(); iter != dataChunks.end(); ++iter)
					{
						if((*iter).GetName() == "frame")
						{
							mFrames.push_back(UResource(Image, (*iter).GetOption("file")));
						}
					}
				}
// 				serializer.NextChunk();
// 
// 				while(serializer.GetChunk().IsValid() && serializer.GetChunk().GetName() == "frame")
// 				{
// 					mFrames.push_back(UResource(Image, serializer.GetChunk().GetOption("file")));
// 
// 					serializer.NextChunk();
// 				}
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