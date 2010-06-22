#include "ReTechCommonIncludes.h"
#include "ReTechWorldObject.h"
#include "ReTechWorld.h"

namespace rt
{
	WorldObject::WorldObject()
		: mVisible(true), mEnabled(true), mWorldPosition(0.0f, 0.0f), mLayer(0), mWorldRotation(0), mWorldSize(0.0f, 0.0f), 
		mAttachedTo(0), mWorld(0)
	{

	}

	WorldObject::~WorldObject()
	{
		if(!mAttaches.empty())
		{
			for(ObjectsVec::iterator iter = mAttaches.begin(); iter != mAttaches.end(); ++iter)
			{
				mWorld->DestroyObject((*iter));
			}
		}
	}

	void WorldObject::UnSerialize( const YAML::Node& iNode )
	{
		SafeGet(iNode, "position", mWorldPosition);
		SafeGet(iNode, "size", mWorldSize);
		SafeGet(iNode, "layer", mLayer);
		SafeGet(iNode, "tag", mTag);

		//load sub objects
		const YAML::Node* subObjects = iNode.FindValue("objects");
		if(subObjects)
		{
			for(YAML::Iterator iter = subObjects->begin(); iter != subObjects->end(); ++iter)
			{
				WorldObject* worldObject = static_cast<WorldObject*>(ObjectsFactory::CreateObject((*iter)["class"]));
				*iter >> worldObject;

				mPendingAttaches.push_back(worldObject);
			}
		}
	}

	void WorldObject::Serialize( YAML::Emitter& iEmitter ) const
	{

	}

	void WorldObject::OnAddToWorld()
	{
		if(!mPendingAttaches.empty())
		{
			for(ObjectsVec::iterator iter = mPendingAttaches.begin(); iter != mPendingAttaches.end(); ++iter)
			{
				mWorld->AddObject((*iter), this);
			}
		}
	}

	void WorldObject::Update( float iFrameTime )
	{

	}

	void WorldObject::Draw( sf::RenderWindow* iRenderWindow )
	{

	}

	bool WorldObject::LowerThen (const WorldObject* const iOther)
	{
		if(mAttachedTo != 0 && iOther->mAttachedTo != 0)
		{
			if(mAttachedTo->mLayer != iOther->mAttachedTo->mLayer)
			{
				return mAttachedTo->mLayer < iOther->mAttachedTo->mLayer;
			}
			else if(mLayer != iOther->mLayer)
			{
				return mLayer < iOther->mLayer;
			}
		}
		
		return false;
	}

	void WorldObject::SetWorldPosition( const sf::Vector2f& iPosition )
	{
		mWorldPosition = iPosition;

		OnSetWorldPosition();

		for(ObjectsVec::iterator iter = mAttaches.begin(); iter != mAttaches.end(); ++iter)
		{
			(*iter)->OnSetWorldPosition();
		}
	}

	void WorldObject::SetWorldScale( const sf::Vector2f& iScale )
	{
		mWorldScale = iScale;

		OnSetWorldScale();

		for(ObjectsVec::iterator iter = mAttaches.begin(); iter != mAttaches.end(); ++iter)
		{
			(*iter)->OnSetWorldScale();
		}
	}

	void WorldObject::SetWorldRotation( float iAngle )
	{
		mWorldRotation = iAngle;

		OnSetWorldRotation();

		for(ObjectsVec::iterator iter = mAttaches.begin(); iter != mAttaches.end(); ++iter)
		{
			(*iter)->OnSetWorldRotation();
		}
	}

	void WorldObject::SetWorldSize( const sf::Vector2f& iSize )
	{
		mWorldSize = iSize;
	}

	sf::Vector2f WorldObject::GetWorldPosition()
	{
		return mWorldPosition;
	}

	sf::Vector2f WorldObject::GetWorldScale()
	{
		return mWorldScale;
	}

	float WorldObject::GetWorldRotation()
	{
		return mWorldRotation;
	}

	sf::Vector2f WorldObject::GetWorldSize()
	{
		return mWorldSize;
	}

	sf::Vector2f WorldObject::GetInheritedWorldPosition()
	{
		return mAttachedTo ? mAttachedTo->GetInheritedWorldPosition() + mWorldPosition : mWorldPosition;
	}

	sf::Vector2f WorldObject::GetInheritedWorldScale()
	{
		return mAttachedTo ? sf::Vector2f(mAttachedTo->GetInheritedWorldScale().x * mWorldScale.x, mAttachedTo->GetInheritedWorldScale().y * mWorldScale.y) : mWorldScale;
	}

	float WorldObject::GetInheritedWorldRotation()
	{
		return mAttachedTo ? mAttachedTo->GetInheritedWorldRotation() + mWorldRotation : mWorldRotation;
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

		for(ObjectsVec::iterator iter = mAttaches.begin(); iter != mAttaches.end(); ++iter)
		{
			(*iter)->SetVisible(iVisible);
		}
	}

	bool WorldObject::IsEnabled()
	{
		return mEnabled;
	}

	void WorldObject::SetEnabled( bool iEnabled )
	{
		mEnabled = iEnabled;

		for(ObjectsVec::iterator iter = mAttaches.begin(); iter != mAttaches.end(); ++iter)
		{
			(*iter)->SetEnabled(iEnabled);
		}
	}

	void WorldObject::Attach( WorldObject* iWorldObject )
	{
		iWorldObject->SetParent(this);
		mAttaches.push_back(iWorldObject);
	}

	void WorldObject::Detach( WorldObject* iWorldObject )
	{
		mAttaches.erase(std::remove(mAttaches.begin(), mAttaches.end(), iWorldObject), mAttaches.end());
	}

	void WorldObject::SetParent( WorldObject* iParent )
	{
		mAttachedTo = iParent;
		OnSetWorldPosition();
		OnSetWorldRotation();
		OnSetWorldScale();
	}

	WorldObject* WorldObject::GetParent()
	{
		return mAttachedTo;
	}

	void WorldObject::SetTag( const std::string& iTag )
	{
		mTag = iTag;
	}

	std::string WorldObject::GetTag()
	{
		return mTag;
	}

	WorldObject* WorldObject::GetSubObjectByTag( const std::string& iTag )
	{
		if(!mAttaches.empty())
		{
			for(ObjectsVec::iterator iter = mAttaches.begin(); iter != mAttaches.end(); ++iter)
			{
				if((*iter)->GetTag() == iTag)
				{
					return (*iter);
				}
			}
		}

		return 0;
	}

	void WorldObject::SetWorld( World* iWorld )
	{
		mWorld = iWorld;
	}
}