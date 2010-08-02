#ifndef __rtWorldObject_H__
#define __rtWorldObject_H__

#include "ReTechSerializeable.h"
#include "ReTechProperty.h"

namespace rt
{
	class WorldObject : public Serializeable, public sf::Drawable
	{
	public:
		typedef std::vector<Poco::SharedPtr<Serializeable>> SerializeableVec;
		typedef SerializeableVec::iterator SerializeableVecIter;

		WorldObject();
		virtual ~WorldObject();

		virtual void UnSerialize(const YAML::Node& iNode);
		virtual void Serialize(YAML::Emitter& iEmitter) const;

		virtual void Update(float iFrameTime);
		virtual void Draw(sf::RenderWindow* iRenderWindow);

		virtual bool LowerThen(const WorldObject* const iOther); 

		void SetLayer(int iLayer);
		int GetLayer();

		bool IsVisible();
		void SetVisible(bool iVisible);

		bool IsEnabled();
		void SetEnabled(bool iEnabled);

		void SetTag(const std::string& iTag);
		std::string GetTag();

		void SetWorld(World* iWorld);

		template<class T>
		void CreateVarProperty(const std::string& iName, T& iVariable)
		{
			mProperties.push_back(new Property<T>(iName, iVariable));
		}

		template<class T>
		void CreateFuncProperty(const std::string& iName, fastdelegate::FastDelegate1<T> iSetter, fastdelegate::FastDelegate0<T> iGetter)
		{
			mProperties.push_back(new Property<T>(iName, iSetter, iGetter));
		}

		template<class T>
		void CreateFuncProperty(const std::string& iName, fastdelegate::FastDelegate1<const T&> iSetter, fastdelegate::FastDelegate0<const T&> iGetter)
		{
			mProperties.push_back(new Property<T>(iName, iSetter, iGetter));
		}

		void AddProperty(Serializeable* iProperty);

	protected:
		virtual void Render(sf::RenderTarget& target, sf::Renderer& renderer) const;

		bool				mVisible;
		bool				mEnabled;
		int					mLayer;
		std::string			mTag;
		World*				mWorld;

		SerializeableVec	mProperties;	
	};
}

#endif