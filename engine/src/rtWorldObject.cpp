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
#include "rtWorldObject.h"
#include "rtWorld.h"

#include "rtProperty.h"

namespace rt
{
	WorldObject::WorldObject()
		: mRotation(0.0f), mVisible(true), mEnabled(true), mLayer(0), mWorld(0), mUniqueID(GameCore::Get()->CreateUniqueId())
	{
		mClassName = "WorldObject";
	}

	WorldObject::~WorldObject()
	{
	}

	void WorldObject::UnSerialize( const YAML::Node& iNode )
	{
// 		RTID savedID = -1;
// 		if(SafeGet(iNode, "id", savedID))
// 		{
// 			mWorld->AddIDPair(savedID, mUniqueID);
// 		}
// 
// 		for(SerializeableVecIter iter = mProperties.begin(); iter != mProperties.end(); ++iter)
// 		{
// 			(*iter)->UnSerialize(iNode);
// 		}
	}

	void WorldObject::Serialize( YAML::Emitter& iEmitter )
	{
// 		iEmitter << YAML::Key << "class";
// 		iEmitter << YAML::Value << GetClassName();
// 		iEmitter << YAML::Key << "id";
// 		iEmitter << YAML::Value << mUniqueID;
// 
// 		for(SerializeableVec::const_iterator iter = mProperties.begin(); iter != mProperties.end(); ++iter)
// 		{
// 			(*iter)->Serialize(iEmitter);
// 		}
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

	bool WorldObject::IsPointInside( const sf::Vector2f& iMousePos )
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

	void WorldObject::SetPosition( const Vector2f& iPosition )
	{
		mPosition = iPosition;
	}

	Vector2f WorldObject::GetPosition()
	{
		return mPosition;
	}

	void WorldObject::SetOrigin( const Vector2f& iOrigin )
	{
		mOrigin = iOrigin;
	}

	Vector2f WorldObject::GetOrigin()
	{
		return mOrigin;
	}

	void WorldObject::SetScale( const Vector2f& iScale )
	{
		mScale = iScale;
	}

	Vector2f WorldObject::GetScale()
	{
		return mScale;
	}

	void WorldObject::SetRotation( float iAngle )
	{
		mRotation = iAngle;
	}

	float WorldObject::GetRotation()
	{
		return mRotation;
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