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
#include "rtSerializeable.h"

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

				if(property.get(iObject).isCompatible<rt::Serializeable*>())
				{
					SerializeYAML(property.get(iObject).to<rt::Serializeable*>()->ToUserObject(), iEmitter);
				}
				else
				{
					SerializeYAML(property.get(iObject).to<camp::UserObject>(), iEmitter);
				}

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
					if (arrayProperty.elementType() == camp::userType)
					{
						// The array elements are composed objects: serialize them recursively
						iEmitter << YAML::BeginMap;

						if(property.get(iObject).isCompatible<rt::Serializeable*>())
						{
							SerializeYAML(arrayProperty.get(iObject, j).to<rt::Serializeable*>()->ToUserObject(), iEmitter);
						}
						else
						{
							SerializeYAML(arrayProperty.get(iObject, j).to<camp::UserObject>(), iEmitter);
						}

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
				if(property.get(iObject).isCompatible<Serializeable*>())
				{

				}
				else
				{
					UnserializeYAML(property.get(iObject).to<camp::UserObject>(), (*iNode.FindValue(property.name())));
				}
			}
			else if (property.type() == camp::arrayType)
			{
				// The current property is an array
 				const camp::ArrayProperty& arrayProperty = static_cast<const camp::ArrayProperty&>(property);
 
				const YAML::Node* arrayNode = iNode.FindValue(property.name());
				std::size_t index = 0;

 				for (YAML::Iterator iter = arrayNode->begin(); iter != arrayNode->end(); ++iter)
 				{
					std::size_t arraySize = arrayProperty.size(iObject);

  					if (arrayProperty.elementType() == camp::userType)
 					{
						std::string className;
						const YAML::Node* classNode;

						classNode = iter->FindValue("ClassName");
						if(classNode)
						{
							*classNode >> className;
						}

						if(!className.empty())
						{
							Serializeable* newObject = 0;
							const camp::Class& metaClass = camp::classByName(className);
							newObject = metaClass.construct<Serializeable>();

							if (index >= arraySize)
							{
								if (arrayProperty.dynamic())
									arrayProperty.insert(iObject, index, newObject);
								else
									break;
							}

							UnserializeYAML(arrayProperty.get(iObject, index).to<Serializeable*>()->ToUserObject(), *iter);
						}
						else
						{
							if (index >= arraySize)
							{
								if (arrayProperty.dynamic())
									arrayProperty.resize(iObject, index + 1);
								else
									break;
							}

							UnserializeYAML(arrayProperty.get(iObject, index).to<camp::UserObject>(), *iter);
						}			
 					}
 					else
 					{
						if (index >= arraySize)
						{
							if (arrayProperty.dynamic())
								arrayProperty.resize(iObject, index + 1);
							else
								break;
						}

 						
						std::string valueString;
						iter->GetScalar(valueString);
						arrayProperty.set(iObject, index, valueString);
 					}

					++index;
 				}
			}
			else
			{
				// The current property is a simple property: read its value from the node's text
				std::string valueString;
				(*iNode.FindValue(property.name())) >> valueString;
				property.set(iObject, valueString);
			}
		}
	}

}