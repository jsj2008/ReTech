#include "ReTechCommonIncludes.h"
#include "ReTechSerializer.h"

namespace rt
{
	Serializer::Serializer()
	{

	}

	Serializer::~Serializer()
	{
		mDocument->release();
	}

	void Serializer::SetFile( const std::string& iFileName )
	{
		Poco::XML::DOMParser parser;
		mDocument = parser.parse(iFileName);
		mCurrentChunk.SetNode(mDocument->firstChild());
	}

	rt::DataChunk& Serializer::GetChunk()
	{
		return mCurrentChunk;
	}
}