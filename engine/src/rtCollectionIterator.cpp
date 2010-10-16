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

#include "rtCommonIncludes.h"
#include "rtCollectionIterator.h"

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
		return mSectionNode ? mCurrentIndex >= static_cast<int>(mSectionNode->size()) : true;
	}

	const YAML::Node& CollectionIterator::Node()
	{
		switch(mSectionNode->GetType())
		{
		case YAML::CT_MAP:
			return (*mSectionNode);
			break;
		case YAML::CT_SEQUENCE:
			return (*mSectionNode)[mCurrentIndex];
			break;
		}

		return (*mSectionNode);
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