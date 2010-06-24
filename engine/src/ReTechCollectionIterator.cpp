#include "ReTechCommonIncludes.h"
#include "ReTechCollectionIterator.h"

namespace rt
{
	CollectionIterator::CollectionIterator( const std::string& iFileName )
		: mSectionNode(0), mCurrentIndex(0)
	{
		std::ifstream inFile(iFileName.c_str());

		if(inFile.is_open())
		{
			YAML::Parser parser(inFile);
			parser.GetNextDocument(mDocument);

			mSectionNode = &mDocument;
		}
	}

	CollectionIterator::CollectionIterator( const YAML::Node* iSectionNode )
		: mSectionNode(iSectionNode), mCurrentIndex(0)
	{
		
	}

	void CollectionIterator::Next()
	{
		++mCurrentIndex;
	}

	bool CollectionIterator::End()
	{
		return mSectionNode ? mCurrentIndex >= mSectionNode->size() : true;
	}

	const YAML::Node& CollectionIterator::Node()
	{
		return (*mSectionNode)[mCurrentIndex];
	}

	float CollectionIterator::Progress()
	{
		return mSectionNode->size() ? mCurrentIndex / mSectionNode->size() : 1.0f;
	}

	CollectionIterator CollectionIterator::Extract( const std::string& iSectionName )
	{
		return CollectionIterator(mSectionNode->FindValue(iSectionName));
	}

	void CollectionIterator::Clear()
	{
		mDocument.Clear();
		mSectionNode = 0;
	}
}