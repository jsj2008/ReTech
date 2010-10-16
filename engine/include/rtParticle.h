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

#ifndef __rtParticle_H__
#define __rtParticle_H__

#include "rtResource.h"

namespace rt
{
	class GroupDesc;
	class ModelDesc;
	class RendererDesc;
	class EmitterDesc;
	class ModifierDesc;
	class ZoneDesc;

	class SystemDesc : public Serializeable
	{
	public:
		typedef std::vector<GroupDesc> GroupDescVec;
		typedef GroupDescVec::iterator GroupDescVecIter;

		virtual void UnSerialize(const YAML::Node& iNode);
		virtual void Serialize(YAML::Emitter& iEmitter) const;

		SPK::SFML::SFMLSystem* Create();

	protected:
		GroupDescVec mGroupDescs;
	};

	class ParamDesc : public Serializeable
	{
	public:
		ParamDesc();

		virtual void UnSerialize(const YAML::Node& iNode);
		virtual void Serialize(YAML::Emitter& iEmitter) const;

		void AddParamTo(SPK::Model* iModel);
		void AddFlags(int& iEnableFlag, int& iMutableFlag, int& iRandomFlag, int& iInterpolatedFlag);

	protected:
		void GetFlagAndParamByName(const std::string& iName, SPK::ModelParamFlag& iFlag, SPK::ModelParam& iParam);

		SPK::ModelParamFlag mFlag;
		SPK::ModelParam		mParam;

		bool				mMutable;
		bool				mRandom;
		bool				mInterpolated;

		std::vector<float>	mValues;
	};

	class ModelDesc : public Serializeable
	{
	public:
		typedef std::vector<ParamDesc> ParamDescVec;
		typedef ParamDescVec::iterator ParamDescVecIter;

		virtual void UnSerialize(const YAML::Node& iNode);
		virtual void Serialize(YAML::Emitter& iEmitter) const;

		SPK::Model* Create();

	protected:
		void MakeFlags(int& iEnableFlag, int& iMutableFlag, int& iRandomFlag, int& iInterpolatedFlag);

		std::string			mName;
		std::vector<float>	mLifetime;
		ParamDescVec		mParams;
	};

	class RendererDesc : public Serializeable
	{
	public:
		RendererDesc();

		virtual void UnSerialize(const YAML::Node& iNode);
		virtual void Serialize(YAML::Emitter& iEmitter) const;

		SPK::SFML::SFMLRenderer* Create();

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

	class GroupDesc : public Serializeable
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

	class ZoneDesc : public Serializeable
	{
	public:
		virtual void UnSerialize(const YAML::Node& iNode);
		virtual void Serialize(YAML::Emitter& iEmitter) const;

		SPK::Zone* Create();

	protected:
		SPK::Zone* CreateZoneByName(const std::string& iName);

		std::string		mType;

		SPK::Vector3D	mCustomVecOne;
		SPK::Vector3D	mCustomVecTwo;

		float			mCustomFloatOne;
		float			mCustomFloatTwo;
	};

	class EmitterDesc : public Serializeable
	{
	public:
		EmitterDesc();

		virtual void UnSerialize(const YAML::Node& iNode);
		virtual void Serialize(YAML::Emitter& iEmitter) const;

		SPK::Emitter* Create();

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

	class ModifierDesc : public Serializeable
	{
	public:
		virtual void UnSerialize(const YAML::Node& iNode);
		virtual void Serialize(YAML::Emitter& iEmitter) const;

		SPK::Modifier* Create();

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

	protected:
		SPK::SFML::SFMLSystem* mSystem;
	};
}

#endif