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

	void SerializeYAML(const camp::UserObject& iObject, YAML::Emitter& iEmitter)
	{
		// Iterate over the object's properties using its metaclass
		const camp::Class& metaclass = iObject.getClass();
		for (std::size_t i = 0; i < metaclass.propertyCount(); ++i)
		{
			const camp::Property& property = metaclass.property(i);

			if(!property.readable(iObject))
			{
				continue;
			}

			// Create a child node for the new property
			iEmitter << YAML::Key << property.name();
			iEmitter << YAML::Value;

			if (property.type() == camp::userType)
			{
				// The current property is a composed type: serialize it recursively
				iEmitter << YAML::BeginMap;

				SerializeYAML(property.get(iObject).to<camp::UserObject>(), iEmitter);

				iEmitter << YAML::EndMap;
			}
			else if (property.type() == camp::arrayType)
			{
				// The current property is an array
				const camp::ArrayProperty& arrayProperty = static_cast<const camp::ArrayProperty&>(property);

				iEmitter <<YAML::BeginSeq;

				// Iterate over the array elements
				std::size_t count = arrayProperty.size(iObject);
				for (std::size_t j = 0; j < count; ++j)
				{
					iEmitter << YAML::Key << "Item";
					iEmitter << YAML::Value;

					if (arrayProperty.elementType() == camp::userType)
					{
						// The array elements are composed objects: serialize them recursively
						iEmitter << YAML::BeginMap;

						SerializeYAML(arrayProperty.get(iObject, j).to<camp::UserObject>(), iEmitter);

						iEmitter << YAML::EndMap;
					}
					else
					{
						// The array elements are simple properties: write them as the text of their XML node
						iEmitter <<  arrayProperty.get(iObject, j).to<std::string>();
					}
				}

				iEmitter << YAML::EndSeq;
			}
			else
			{
				// The current property is a simple property: write its value as the node's text
				iEmitter <<  property.get(iObject).to<std::string>();
			}
		}
	}

	void UnserializeYAML(const camp::UserObject& iObject, const YAML::Node& iNode)
	{
		// Iterate over the object's properties using its metaclass
		const camp::Class& metaclass = iObject.getClass();
		for (std::size_t i = 0; i < metaclass.propertyCount(); ++i)
		{
			const camp::Property& property = metaclass.property(i);

			if(!property.writable(iObject))
			{
				continue;
			}

			if (property.type() == camp::userType)
			{
				// The current property is a composed type: deserialize it recursively
				UnserializeYAML(property.get(iObject).to<camp::UserObject>(), (*iNode.FindValue(property.name())));
			}
			else if (property.type() == camp::arrayType)
			{
// 				// The current property is an array
// 				const ArrayProperty& arrayProperty = static_cast<const ArrayProperty&>(property);
// 
// 				// Iterate over the child XML node and extract all the array elements
// 				std::size_t index = 0;
// 				for (typename Proxy::NodeType item = Proxy::findFirstChild(child, "item")
// 					; Proxy::isValid(item)
// 					; item = Proxy::findNextSibling(item, "item"))
// 				{
// 					// Make sure that there are enough elements in the array
// 					std::size_t count = arrayProperty.size(object);
// 					if (index >= count)
// 					{
// 						if (arrayProperty.dynamic())
// 							arrayProperty.resize(object, index + 1);
// 						else
// 							break;
// 					}
// 
// 					if (arrayProperty.elementType() == userType)
// 					{
// 						// The array elements are composed objects: deserialize them recursively
// 						deserialize<Proxy>(arrayProperty.get(object, index).to<UserObject>(), item, exclude);
// 					}
// 					else
// 					{
// 						// The array elements are simple properties: read their value from the text of their XML node
// 						arrayProperty.set(object, index, Proxy::getText(item));
// 					}
// 
// 					index++;
// 				}
			}
			else
			{
				// The current property is a simple property: read its value from the node's text
				std::string valueString;
				valueString = property.name();
				(*iNode.FindValue(property.name())) >> valueString;
				property.set(iObject, valueString);
			}
		}
	}

}