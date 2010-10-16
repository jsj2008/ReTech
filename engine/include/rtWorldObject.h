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

#pragma once

#include "rtSerializeable.h"
#include "rtProperty.h"

namespace rt
{
	class WorldObject : public Serializeable/*, public sf::Drawable*/
	{
	public:
		typedef std::vector<boost::shared_ptr<Serializeable>> SerializeableVec;
		typedef SerializeableVec::iterator SerializeableVecIter;

		WorldObject();
		virtual ~WorldObject();

		virtual void UnSerialize(const YAML::Node& iNode);
		virtual void Serialize(YAML::Emitter& iEmitter);

		virtual void Fix();

		virtual std::string GetClassName() const;

		virtual void Update(float iFrameTime);
		virtual void Draw(sf::RenderWindow* iRenderWindow);

		virtual bool LowerThen(const WorldObject* const iOther); 

		virtual bool IsPointInside(const sf::Vector2f& iMousePos);
		virtual bool HandleFocusedEvent(const sf::Event& iEvent);

		virtual void MouseEnter();
		virtual void MouseLeave();

		void SetPosition(const Vector2f& iPosition);
		Vector2f GetPosition();

		void SetOrigin(const Vector2f& iOrigin);
		Vector2f GetOrigin();

		void SetScale(const Vector2f& iScale);
		Vector2f GetScale();

		void SetRotation(float iAngle);
		float GetRotation();

		void SetLayer(int iLayer);
		int GetLayer();

		bool IsVisible();
		void SetVisible(bool iVisible);

		bool IsEnabled();
		void SetEnabled(bool iEnabled);

		void SetTag(const std::string& iTag);
		std::string GetTag();

		void SetWorld(World* iWorld);
		World* GetWorld() const;

		RTID GetUniqueID();

		template<class T>
		void CreateVarProperty(const std::string& iName, T& iVariable)
		{
			mProperties.push_back(boost::shared_ptr<Serializeable>(new Property<T>(iName, iVariable)));
		}

		template<class T>
		void CreateFuncProperty(const std::string& iName, fastdelegate::FastDelegate1<T> iSetter, fastdelegate::FastDelegate0<T> iGetter)
		{
			mProperties.push_back(boost::shared_ptr<Serializeable>(new Property<T>(iName, iSetter, iGetter)));
		}

		template<class T>
		void CreateFuncProperty(const std::string& iName, fastdelegate::FastDelegate1<const T&> iSetter, fastdelegate::FastDelegate0<const T&> iGetter)
		{
			mProperties.push_back(boost::shared_ptr<Serializeable>(new Property<T>(iName, iSetter, iGetter)));
		}

		void AddProperty(Serializeable* iProperty);

		static void RegisterMetaClass()
		{
			camp::Class::declare<WorldObject>("WorldObject")
				.constructor0()
				.property("Position", &WorldObject::GetPosition, &WorldObject::SetPosition)
				.property("Origin", &WorldObject::GetOrigin, &WorldObject::SetOrigin)
				.property("Scale", &WorldObject::GetScale, &WorldObject::SetScale)
				.property("Rotation", &WorldObject::GetRotation, &WorldObject::SetRotation)
				.property("Visible", &WorldObject::IsVisible, &WorldObject::SetVisible)
				.property("Enabled", &WorldObject::IsEnabled, &WorldObject::SetEnabled)
				.property("Layer", &WorldObject::GetLayer, &WorldObject::SetLayer)
				.property("Tag", &WorldObject::GetTag, &WorldObject::SetTag)
				.property("ClassName", &WorldObject::GetClassName)
				.property("ID", &WorldObject::GetUniqueID);
		}

	protected:
		virtual void Render(sf::RenderTarget& target, sf::Renderer& renderer) const;

		Vector2f		mPosition;
		Vector2f		mOrigin;
		Vector2f		mScale;
		float				mRotation;				

		bool				mVisible;
		bool				mEnabled;
		int					mLayer;
		std::string			mTag;
		World*				mWorld;

		std::string			mClassName;

		SerializeableVec	mProperties;

		RTID				mUniqueID;
	};
}

CAMP_AUTO_TYPE(rt::WorldObject, &rt::WorldObject::RegisterMetaClass)