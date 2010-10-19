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
#include "rtComponent.h"

namespace rt
{
	WorldObject::WorldObject()
		: mRotation(0.0f), mVisible(true), mEnabled(true), mLayer(0), mWorld(0), mUniqueID(GameCore::Get()->CreateUniqueId())
	{
	}

	WorldObject::~WorldObject()
	{
	}

	void WorldObject::Fix()
	{

	}

	void WorldObject::Update( float iFrameTime )
	{
		mComponents.erase(std::remove(mComponents.begin(), mComponents.end(), static_cast<Component*>(0)), mComponents.end());

		std::for_each(mComponents.begin(), mComponents.end(), [iFrameTime](Component* iComponent)->void
		{
			if(iComponent)
			{
				iComponent->Update(iFrameTime);
			}
		});
	}

	void WorldObject::Draw( sf::RenderWindow* iRenderWindow )
	{
		std::for_each(mComponents.begin(), mComponents.end(), [iRenderWindow](Component* iComponent)->void
		{
			iComponent->Draw(iRenderWindow);
		});
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

	void WorldObject::AddComponent( Component* iComponent )
	{
		if(std::find(mComponents.begin(), mComponents.end(), iComponent) != mComponents.end())
		{
			//TODO log
			return;
		}

		iComponent->SetOwner(this);

		mComponents.push_back(iComponent);
	}

	void WorldObject::RemoveComponent( Component* iComponent )
	{
		ComponentVecIter finded = std::find(mComponents.begin(), mComponents.end(), iComponent);
		if(finded == mComponents.end())
		{
			//TODO log
			return;
		}

		(*finded) = 0;
	}

	void WorldObject::Render( sf::RenderTarget& target, sf::Renderer& renderer ) const
	{

	}
}