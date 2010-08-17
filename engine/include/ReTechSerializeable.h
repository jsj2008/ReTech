#ifndef __rtSerializeable_H__
#define __rtSerializeable_H__

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
	};
}

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

#endif