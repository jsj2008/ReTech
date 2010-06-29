#include "ReTechCommonIncludes.h"
#include "ReTechWorldObject.h"
#include "ReTechWorld.h"

namespace rt
{
	WorldObject::WorldObject()
		: mVisible(true), mEnabled(true), mLayer(0), mWorld(0)
	{
	}

	WorldObject::~WorldObject()
	{
	}

	void WorldObject::UnSerialize( const YAML::Node& iNode )
	{
		sf::Vector2f position;
		SafeGet(iNode, "position", position);
		SetPosition(position);

		SafeGet(iNode, "layer", mLayer);
		SafeGet(iNode, "tag", mTag);
	}

	void WorldObject::Serialize( YAML::Emitter& iEmitter ) const
	{

	}

	void WorldObject::Update( float iFrameTime )
	{

	}

	void WorldObject::Draw( sf::RenderWindow* iRenderWindow )
	{

	}

	bool WorldObject::LowerThen (const WorldObject* const iOther)
	{
		if(mLayer != iOther->mLayer)
		{
			return mLayer < iOther->mLayer;
		}
		
		return false;
	}

	void WorldObject::SetLayer(int iLayer)
	{
		mLayer = iLayer;
	}

	int WorldObject::GetLayer()
	{
		return mLayer;
	}

	bool WorldObject::IsVisible()
	{
		return mVisible;
	}

	void WorldObject::SetVisible( bool iVisible )
	{
		mVisible = iVisible;
	}

	bool WorldObject::IsEnabled()
	{
		return mEnabled;
	}

	void WorldObject::SetEnabled( bool iEnabled )
	{
		mEnabled = iEnabled;
	}

	void WorldObject::SetTag( const std::string& iTag )
	{
		mTag = iTag;
	}

	std::string WorldObject::GetTag()
	{
		return mTag;
	}

	void WorldObject::SetWorld( World* iWorld )
	{
		mWorld = iWorld;
	}

	void WorldObject::Render( sf::RenderTarget& target, sf::Renderer& renderer ) const
	{

	}
}