#include "ReTechCommonIncludes.h"
#include "ReTechSerializeable.h"
#include "ReTechWorldObject.h"

namespace rt
{
	Serializeable::Serializeable()
	{

	}

	Serializeable::~Serializeable()
	{

	}
}

void operator>>( const YAML::Node& iNode, sf::Vector2f& iVector )
{
	iNode[0] >> iVector.x;
	iNode[1] >> iVector.y;
}

YAML::Emitter& operator<<( YAML::Emitter& iEmitter, const sf::Vector2f& iVector )
{
	iEmitter << YAML::Flow;
	iEmitter << YAML::BeginSeq << iVector.x << iVector.y  << YAML::EndSeq;

	return iEmitter;
}

void operator>>( const YAML::Node& iNode, SPK::Vector3D& iVector )
{
	iNode[0] >> iVector.x;
	iNode[1] >> iVector.y;
	iNode[2] >> iVector.z;
}

YAML::Emitter& operator<<( YAML::Emitter& iEmitter, const SPK::Vector3D& iVector )
{
	iEmitter << YAML::Flow;
	iEmitter << YAML::BeginSeq << iVector.x << iVector.y  << iVector.z << YAML::EndSeq;

	return iEmitter;
}

void operator>>( const YAML::Node& iNode, sf::String& iString )
{
	std::string temp;
	iNode >> temp;
	iString = temp;
}
