#ifndef __rtSerializer_H__
#define __rtSerializer_H__

#include "ReTechDataChunk.h"

namespace rt
{
	class Serializer
	{
	public:
		Serializer();
		~Serializer();

		void SetFile(const std::string& iFileName);

		DataChunk& GetChunk();

	protected:
		Poco::XML::Document*	mDocument;
 		DataChunk				mCurrentChunk;
	};
}

#endif