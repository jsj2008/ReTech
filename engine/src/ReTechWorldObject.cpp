#include "ReTechCommonIncludes.h"
#include "ReTechWorldObject.h"
#include "ReTechWorld.h"

#include "ReTechProperty.h"

namespace rt
{
	WorldObject::WorldObject()
		: mVisible(true), mEnabled(true), mLayer(0), mWorld(0)
	{
		mClassName = "WorldObject";

		CreateFuncProperty("position", fastdelegate::FastDelegate1<const sf::Vector2f&>(this, &WorldObject::SetPosition), fastdelegate::MakeDelegate(this, &WorldObject::GetPosition));
		CreateVarProperty("layer", mLayer);
		CreateVarProperty("tag", mTag);
	}

	WorldObject::~WorldObject()
	{
	}

	void WorldObject::UnSerialize( const YAML::Node& iNode )
	{
		for(SerializeableVecIter iter = mProperties.begin(); iter != mProperties.end(); ++iter)
		{
			(*iter)->UnSerialize(iNode);
		}
	}

	void WorldObject::Serialize( YAML::Emitter& iEmitter ) const
	{
		iEmitter << YAML::BeginMap;

		iEmitter << YAML::Key << "class";
		iEmitter << YAML::Value << GetClassName();

		for(SerializeableVec::const_iterator iter = mProperties.begin(); iter != mProperties.end(); ++iter)
		{
			(*iter)->Serialize(iEmitter);
		}

		iEmitter << YAML::EndMap;
	}

	std::string WorldObject::GetClassName() const
	{
		return mClassName;
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

	void WorldObject::AddProperty( Serializeable* iProperty )
	{
		mProperties.push_back(iProperty);
	}
}