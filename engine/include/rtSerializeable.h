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

#pragma once

namespace rt
{
	class Serializeable
	{
	public:
		Serializeable();
		virtual ~Serializeable() = 0;

		virtual void UnSerialize(const YAML::Node& iNode){}
		virtual void Serialize(YAML::Emitter& iEmitter) const {}

		template<class T>
		bool SafeGet(const YAML::Node& iNode, const std::string iKey, T& iValue)
		{
			const YAML::Node* value = iNode.FindValue(iKey);

			if(value)
			{
				*value >> iValue;
				return true;
			}

			return false;
		}

		template<class T>
		bool SafeGet(const YAML::Node& iNode, const std::string iKey, T* iValue)
		{
			const YAML::Node* value = iNode.FindValue(iKey);

			if(value)
			{
				*value >> iValue;
				return true;
			}

			return false;
		}

		template<class T>
		bool SafeGet(const YAML::Node& iNode, const std::string iKey, fastdelegate::FastDelegate1<const T&, void> iSetter)
		{
			typename T tempValue;
			if(SafeGet(iNode, iKey, tempValue))
			{
				iSetter(tempValue);
				return true;
			}
			return false;
		}

		template<class T>
		bool SafeGet(const YAML::Node& iNode, const std::string iKey, fastdelegate::FastDelegate1<T, void> iSetter)
		{
			typename T tempValue;
			if(SafeGet(iNode, iKey, tempValue))
			{
				iSetter(tempValue);
				return true;
			}
			return false;			
		}

		static void RegisterMetaClass()
		{
			camp::Class::declare<Serializeable>("Serializeable");
		}
	};
}

CAMP_AUTO_TYPE(rt::Serializeable, &rt::Serializeable::RegisterMetaClass)

template<class T>
void operator>>( const YAML::Node& iNode, T* iSerializeable )
{
	iSerializeable->UnSerialize(iNode);
}

template<class T>
YAML::Emitter& operator<<( YAML::Emitter& iEmitter, const T* iSerializeable )
{
	iSerializeable->Serialize(iEmitter);

	return iEmitter;
}

void operator>>( const YAML::Node& iNode, sf::Vector2f& iVector );
YAML::Emitter& operator<<( YAML::Emitter& iEmitter, const sf::Vector2f& iVector );

void operator>>( const YAML::Node& iNode, sf::FloatRect& iRect );
YAML::Emitter& operator<<( YAML::Emitter& iEmitter, const sf::FloatRect& iRect );

void operator>>( const YAML::Node& iNode, sf::Color& iColor );
YAML::Emitter& operator<<( YAML::Emitter& iEmitter, const sf::Color& iColor );

void operator>>( const YAML::Node& iNode, SPK::Vector3D& iVector );
YAML::Emitter& operator<<( YAML::Emitter& iEmitter, const SPK::Vector3D& iVector );

void operator>>( const YAML::Node& iNode, sf::String& iString );