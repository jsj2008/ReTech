#include "ReTechCommonIncludes.h"
#include "ReTechDataChunk.h"
#include "ReTechObjectsFactory.h"
#include "ReTechWorldObject.h"

namespace rt
{
	DataChunk::DataChunk()
		: mNode(0)
	{

	}

	DataChunk::DataChunk( Poco::XML::Node* iNode )
		: mNode(iNode)
	{

	}

	DataChunk::~DataChunk()
	{

	}

	void DataChunk::SetNode( Poco::XML::Node* iNode )
	{
		if(iNode == 0)
		{
			iNode = 0;
		}
		mNode = iNode;
	}

	std::string DataChunk::GetName()
	{
		return mNode->nodeName();
	}

	std::string DataChunk::GetValue()
	{
		return mNode->nodeValue();
	}

	std::string DataChunk::GetOption( const std::string& iOptionName )
	{
		std::string option;

		if(mNode->hasAttributes())
		{
			Poco::XML::NamedNodeMap* attributesMap = mNode->attributes();
			Poco::XML::Node* attributeNode = attributesMap->getNamedItem(iOptionName);

			if(attributeNode != 0)
			{
				option =  attributeNode->nodeValue();
			}

			attributesMap->release();
		}

		return option;
	}

	bool DataChunk::IsValid()
	{
		return mNode != 0 && mNode->nodeName() != "#document";
	}

	bool DataChunk::HasSubChunks()
	{
		return mNode->hasChildNodes();
	}

	void DataChunk::GetSubChunks( std::vector<DataChunk>& iSubChunks )
	{
		if(HasSubChunks())
		{
			Poco::XML::Node* currentNode = mNode->firstChild();
			if(currentNode->nodeName() != "#text")
			{
				iSubChunks.push_back(DataChunk(currentNode));
			}

			while(currentNode != mNode->lastChild())
			{
				currentNode = currentNode->nextSibling();
				if(currentNode->nodeName() != "#text")
				{
					iSubChunks.push_back(DataChunk(currentNode));
				}
			}
		}
	}

	WorldObject* DataChunk::CreateWorldObject()
	{
		WorldObject* worldObject = static_cast<WorldObject*>(ObjectsFactory::CreateObject(GetOption("class")));
		worldObject->UnSerialize(*this);

		return worldObject;
	}
}