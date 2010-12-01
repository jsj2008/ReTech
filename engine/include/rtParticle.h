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

#include "rtResource.h"

namespace rt
{
	class GroupDesc;
	class ModelDesc;
	class RendererDesc;
	class EmitterDesc;
	class ModifierDesc;
	class ZoneDesc;

	class SystemDesc
	{
	public:
		typedef std::vector<GroupDesc> GroupDescVec;
		typedef GroupDescVec::iterator GroupDescVecIter;

		virtual void UnSerialize(const YAML::Node& iNode);
		virtual void Serialize(YAML::Emitter& iEmitter) const;

		SPK::SFML::SFMLSystem* Create();

		static void RegisterMetaClass()
		{
			camp::Class::declare<SystemDesc>("SystemDesc")
				.constructor0()
				.property("Groups", &SystemDesc::mGroupDescs);
		}

	protected:
		GroupDescVec mGroupDescs;
	};

	class ParamDesc
	{
	public:
		ParamDesc();

		virtual void UnSerialize(const YAML::Node& iNode);
		virtual void Serialize(YAML::Emitter& iEmitter) const;

		void AddParamTo(SPK::Model* iModel);
		void AddFlags(int& iEnableFlag, int& iMutableFlag, int& iRandomFlag, int& iInterpolatedFlag);

		static void RegisterMetaClass()
		{
			camp::Class::declare<ParamDesc>("ParamDesc")
				.constructor0()
				//.property("ModelParamFlag", &ParamDesc::mFlag)
				//.property("ModelParam", &ParamDesc::mParam)
				.property("Mutable", &ParamDesc::mMutable)
				.property("Random", &ParamDesc::mRandom)
				.property("Interpolated", &ParamDesc::mInterpolated)
				.property("Values", &ParamDesc::mValues)
				;
		}

	protected:
		void GetFlagAndParamByName(const std::string& iName, SPK::ModelParamFlag& iFlag, SPK::ModelParam& iParam);

		SPK::ModelParamFlag mFlag;
		SPK::ModelParam		mParam;

		bool				mMutable;
		bool				mRandom;
		bool				mInterpolated;

		std::vector<float>	mValues;
	};

	class ModelDesc
	{
	public:
		typedef std::vector<ParamDesc> ParamDescVec;
		typedef ParamDescVec::iterator ParamDescVecIter;

		virtual void UnSerialize(const YAML::Node& iNode);
		virtual void Serialize(YAML::Emitter& iEmitter) const;

		SPK::Model* Create();

		static void RegisterMetaClass()
		{
			camp::Class::declare<ModelDesc>("ModelDesc")
				.constructor0();
		}

	protected:
		void MakeFlags(int& iEnableFlag, int& iMutableFlag, int& iRandomFlag, int& iInterpolatedFlag);

		std::string			mName;
		std::vector<float>	mLifetime;
		ParamDescVec		mParams;
	};

	class RendererDesc
	{
	public:
		RendererDesc();

		virtual void UnSerialize(const YAML::Node& iNode);
		virtual void Serialize(YAML::Emitter& iEmitter) const;

		SPK::SFML::SFMLRenderer* Create();

		static void RegisterMetaClass()
		{
			camp::Class::declare<RendererDesc>("RendererDesc")
				.constructor0();
		}

	protected:
		sf::Blend::Mode GetModeByName(const std::string& iName);
		SPK::SFML::SFMLRenderer* CreateRendererByName(const std::string& iName);

		std::string		mName;
		std::string		mType;
		bool			mGroundCulling;
		sf::Blend::Mode	mBlendingMode;
		float			mZFactor;

		float			mCustomOne;
		float			mCustomTwo;
		std::string		mImageName;
	};

	class GroupDesc
	{
	public:
		typedef std::vector<EmitterDesc> EmmiterDescVec;
		typedef EmmiterDescVec::iterator EmmiterDescVecIter;

		typedef std::vector<ModifierDesc> ModifierDescVec;
		typedef ModifierDescVec::iterator ModifierDescVecIter;

		GroupDesc();

		virtual void UnSerialize(const YAML::Node& iNode);
		virtual void Serialize(YAML::Emitter& iEmitter) const;

		SPK::Group* Create();

		static void RegisterMetaClass()
		{
			camp::Class::declare<GroupDesc>("GroupDesc")
				.constructor0();
		}

	protected:
		std::string		mName;

		SPK::Vector3D	mGravity;
		float			mFriction;
		size_t			mCapacity;

		ModelDesc		mModelDesc;
		RendererDesc	mRendererDesc;
		EmmiterDescVec	mEmitterDescs;
		ModifierDescVec	mModifierDescs;
	};

	class ZoneDesc
	{
	public:
		virtual void UnSerialize(const YAML::Node& iNode);
		virtual void Serialize(YAML::Emitter& iEmitter) const;

		SPK::Zone* Create();

		static void RegisterMetaClass()
		{
			camp::Class::declare<ZoneDesc>("ZoneDesc")
				.constructor0();
		}

	protected:
		SPK::Zone* CreateZoneByName(const std::string& iName);

		std::string		mType;

		SPK::Vector3D	mCustomVecOne;
		SPK::Vector3D	mCustomVecTwo;

		float			mCustomFloatOne;
		float			mCustomFloatTwo;
	};

	class EmitterDesc
	{
	public:
		EmitterDesc();

		virtual void UnSerialize(const YAML::Node& iNode);
		virtual void Serialize(YAML::Emitter& iEmitter) const;

		SPK::Emitter* Create();

		static void RegisterMetaClass()
		{
			camp::Class::declare<EmitterDesc>("EmitterDesc")
				.constructor0();
		}

	protected:
		SPK::Emitter* CreateEmitterByName(const std::string& iName);

		std::string			mName;
		std::string			mType;

		float				mFlow;
		std::vector<float>	mForce;
		int					mTank;

		ZoneDesc			mZoneDesc;

		bool				mUseBorders;

		SPK::Vector3D		mCustomVecOne;

		float				mCustomFloatOne;
		float				mCustomFloatTwo;
	};

	class ModifierDesc
	{
	public:
		virtual void UnSerialize(const YAML::Node& iNode);
		virtual void Serialize(YAML::Emitter& iEmitter) const;

		SPK::Modifier* Create();

		static void RegisterMetaClass()
		{
			camp::Class::declare<ModifierDesc>("ModifierDesc")
				.constructor0();
		}

	protected:
	};

	class Particle : public Resource
	{
	public:
		Particle();
		Particle(const std::string& iResourceName);
		virtual ~Particle();

		virtual void Load();
		virtual void Unload();

		virtual bool IsLoaded();

		SPK::SPK_ID GetSystemID();

		static void RegisterMetaClass()
		{
			camp::Class::declare<Particle>("Particle")
				.base<rt::Resource>()
				.constructor0();
		}

	protected:
		SPK::SFML::SFMLSystem*	mSystem;
	};
}

CAMP_AUTO_TYPE(rt::Particle, &rt::Particle::RegisterMetaClass)
CAMP_AUTO_TYPE(rt::SystemDesc, &rt::SystemDesc::RegisterMetaClass)
CAMP_AUTO_TYPE(rt::ModelDesc, &rt::ModelDesc::RegisterMetaClass)
CAMP_AUTO_TYPE(rt::GroupDesc, &rt::GroupDesc::RegisterMetaClass)
CAMP_AUTO_TYPE(rt::ParamDesc, &rt::ParamDesc::RegisterMetaClass)
CAMP_AUTO_TYPE(rt::RendererDesc, &rt::RendererDesc::RegisterMetaClass)
CAMP_AUTO_TYPE(rt::EmitterDesc, &rt::EmitterDesc::RegisterMetaClass)
CAMP_AUTO_TYPE(rt::ModifierDesc, &rt::ModifierDesc::RegisterMetaClass)
CAMP_AUTO_TYPE(rt::ZoneDesc, &rt::ZoneDesc::RegisterMetaClass)