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

void operator>>( const YAML::Node& iNode, sf::FloatRect& iRect )
{
	iNode[0] >> iRect.Left;
	iNode[1] >> iRect.Top;
	iNode[2] >> iRect.Width;
	iNode[3] >> iRect.Height;
}

YAML::Emitter& operator<<( YAML::Emitter& iEmitter, const sf::FloatRect& iRect )
{
	iEmitter << YAML::Flow;
	iEmitter << YAML::BeginSeq << iRect.Left << iRect.Top << iRect.Width << iRect.Height  << YAML::EndSeq;

	return iEmitter;
}

void operator>>( const YAML::Node& iNode, sf::Color& iColor )
{
	int r, g, b, a;
	iNode[0] >> r;
	iNode[1] >> g;
	iNode[2] >> b;
	iNode[3] >> a;

	iColor.r = static_cast<sf::Uint8>(r);
	iColor.g = static_cast<sf::Uint8>(g);
	iColor.b = static_cast<sf::Uint8>(b);
	iColor.a = static_cast<sf::Uint8>(a);
}

YAML::Emitter& operator<<( YAML::Emitter& iEmitter, const sf::Color& iColor )
{
	iEmitter << YAML::Flow;
	iEmitter << YAML::BeginSeq << iColor.r << iColor.g << iColor.b << iColor.a  << YAML::EndSeq;

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
