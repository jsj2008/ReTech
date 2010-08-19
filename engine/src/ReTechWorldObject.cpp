#include "ReTechCommonIncludes.h"
#include "ReTechWorldObject.h"
#include "ReTechWorld.h"

#include "ReTechProperty.h"

namespace rt
{
	WorldObject::WorldObject()
		: mVisible(true), mEnabled(true), mLayer(0), mWorld(0), mUniqueID(GameCore::Get()->CreateUniqueId())
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
		RTID savedID = -1;
		if(SafeGet(iNode, "id", savedID))
		{
			mWorld->AddIDPair(savedID, mUniqueID);
		}

		for(SerializeableVecIter iter = mProperties.begin(); iter != mProperties.end(); ++iter)
		{
			(*iter)->UnSerialize(iNode);
		}
	}

	void WorldObject::Serialize( YAML::Emitter& iEmitter )
	{
		iEmitter << YAML::Key << "class";
		iEmitter << YAML::Value << GetClassName();
		iEmitter << YAML::Key << "id";
		iEmitter << YAML::Value << mUniqueID;

		for(SerializeableVec::const_iterator iter = mProperties.begin(); iter != mProperties.end(); ++iter)
		{
			(*iter)->Serialize(iEmitter);
		}
	}

	void WorldObject::Fix()
	{

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
		if(mWorld->GetLayer() != iOther->GetWorld()->GetLayer())
		{
			return mWorld->GetLayer() < iOther->GetWorld()->GetLayer();
		}
		else if(mLayer != iOther->mLayer)
		{
			return mLayer < iOther->mLayer;
		}
		
		return false;
	}

	bool WorldObject::IsMouseInside( const sf::Vector2f& iMousePos )
	{
		return false;
	}

	bool WorldObject::HandleFocusedEvent( const sf::Event& iEvent )
	{
		return false;
	}

	void WorldObject::MouseEnter()
	{

	}

	void WorldObject::MouseLeave()
	{

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

	World* WorldObject::GetWorld() const
	{
		return mWorld;
	}

	rt::RTID WorldObject::GetUniqueID()
	{
		return mUniqueID;
	}

	void WorldObject::Render( sf::RenderTarget& target, sf::Renderer& renderer ) const
	{

	}

	void WorldObject::AddProperty( Serializeable* iProperty )
	{
		mProperties.push_back(boost::shared_ptr<Serializeable>(iProperty));
	}
}