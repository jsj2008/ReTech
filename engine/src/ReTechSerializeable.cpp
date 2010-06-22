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