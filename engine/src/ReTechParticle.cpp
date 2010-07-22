#include "ReTechCommonIncludes.h"
#include "ReTechParticle.h"
#include "ReTechImage.h"
#include "ReTechCollectionIterator.h"

namespace rt
{
	Particle::Particle()
		: mSystem(0)
	{

	}

	Particle::Particle( const std::string& iResourceName )
		: mSystem(0)
	{
		Initialize(iResourceName);
	}

	Particle::~Particle()
	{

	}

	void Particle::Load()
	{
		if(!IsLoaded())
		{
			CollectionIterator particleFile(mResourceName);

			SystemDesc systemDesc;
			particleFile.Node() >> &systemDesc;

			mSystem = systemDesc.Create();
		}
	}

	void Particle::Unload()
	{
		SPK_Destroy(mSystem);
		mSystem = 0;
	}

	bool Particle::IsLoaded()
	{
		return mSystem != 0;
	}

	SPK::SPK_ID Particle::GetSystemID()
	{
		if(mSystem)
		{
			return mSystem->getID();
		}
		else
		{
			return -1;
		}
	}

	void SystemDesc::UnSerialize( const YAML::Node& iNode )
	{
		CollectionIterator particleFile(&iNode);
		CollectionIterator groups(particleFile.Extract("groups"));

		while(!groups.End())
		{
			GroupDesc groupDesc;

			groups.Node() >> &groupDesc;

			mGroupDescs.push_back(groupDesc);

			groups.Next();
		}
	}

	void SystemDesc::Serialize( YAML::Emitter& iEmitter ) const
	{

	}

	SPK::SFML::SFMLSystem* SystemDesc::Create()
	{
		SPK::SFML::SFMLSystem* newSystem = SPK::SFML::SFMLSystem::create();

		for(GroupDescVecIter iter = mGroupDescs.begin(); iter != mGroupDescs.end(); ++iter)
		{
			newSystem->addGroup((*iter).Create());
		}

		return newSystem;
	}

	GroupDesc::GroupDesc()
		: mFriction(0.0f), mCapacity(0)
	{

	}

	void GroupDesc::UnSerialize( const YAML::Node& iNode )
	{
		SafeGet(iNode, "name", mName);
		SafeGet(iNode, "gravity", mGravity);
		SafeGet(iNode, "friction", mFriction);
		SafeGet(iNode, "capacity", mCapacity);
		SafeGet(iNode, "model", &mModelDesc);
		SafeGet(iNode, "renderer", &mRendererDesc);
		
 		CollectionIterator particleFile(&iNode);

		CollectionIterator emitters(particleFile.Extract("emitters"));
		while(!emitters.End())
		{
			EmitterDesc emitterDesc;

			emitters.Node() >> &emitterDesc;

			mEmitterDescs.push_back(emitterDesc);

			emitters.Next();
		}

		CollectionIterator modifiers(particleFile.Extract("modifiers"));
		while(!modifiers.End())
		{
			ModifierDesc modifierDesc;

			modifiers.Node() >> &modifierDesc;

			mModifierDescs.push_back(modifierDesc);

			modifiers.Next();
		}
	}

	void GroupDesc::Serialize( YAML::Emitter& iEmitter ) const
	{

	}

	SPK::Group* GroupDesc::Create()
	{
		SPK::Group* newGroup = SPK::Group::create(mModelDesc.Create(), mCapacity);

		newGroup->setName(mName);
		newGroup->setGravity(mGravity);
		newGroup->setFriction(mFriction);
		newGroup->setRenderer(mRendererDesc.Create());

		for(EmmiterDescVecIter iter = mEmitterDescs.begin(); iter != mEmitterDescs.end(); ++iter)
		{
			newGroup->addEmitter((*iter).Create());
		}

		for(ModifierDescVecIter iter = mModifierDescs.begin(); iter != mModifierDescs.end(); ++iter)
		{
			newGroup->addModifier((*iter).Create());
		}

		return newGroup;
	}

	ParamDesc::ParamDesc()
		: mFlag(SPK::FLAG_NONE), mParam(SPK::PARAM_RED), mMutable(false), mRandom(false), mInterpolated(false)
	{

	}

	void ParamDesc::UnSerialize( const YAML::Node& iNode )
	{
		std::string paramName;
		SafeGet(iNode, "param", paramName);
		GetFlagAndParamByName(paramName, mFlag, mParam);

		SafeGet(iNode, "value", mValues);
		SafeGet(iNode, "mutable", mMutable);
		SafeGet(iNode, "random", mRandom);
		SafeGet(iNode, "interpolated", mInterpolated);
	}

	void ParamDesc::Serialize( YAML::Emitter& iEmitter ) const
	{

	}

	void ParamDesc::AddParamTo( SPK::Model* iModel )
	{
		if(mRandom && mMutable)
		{
			if(mValues.size() >= 4)
				iModel->setParam(mParam, mValues[0], mValues[1], mValues[2], mValues[3]);
		}
		else if(mRandom || mMutable)
		{
			if(mValues.size() >= 2)
				iModel->setParam(mParam, mValues[0], mValues[1]);
		}
		else
		{
			if(mValues.size() >= 1)
				iModel->setParam(mParam, mValues[0]);
		}	
	}

	void ParamDesc::AddFlags( int& iEnableFlag, int& iMutableFlag, int& iRandomFlag, int& iInterpolatedFlag )
	{
		iEnableFlag |= mFlag;

		if(mMutable)
			iMutableFlag |= mFlag;

		if(mRandom)
			iRandomFlag |= mFlag;

		if(mInterpolated)
			iInterpolatedFlag |= mFlag;
	}

	void ParamDesc::GetFlagAndParamByName( const std::string& iName, SPK::ModelParamFlag& iFlag, SPK::ModelParam& iParam )
	{
		if(iName == "red")
		{
			iFlag = SPK::FLAG_RED;
			iParam = SPK::PARAM_RED;
		}
		else if(iName == "green")
		{
			iFlag = SPK::FLAG_GREEN;
			iParam = SPK::PARAM_GREEN;
		}
		else if(iName == "blue")
		{
			iFlag = SPK::FLAG_BLUE;
			iParam = SPK::PARAM_BLUE;
		}
		else if(iName == "alpha")
		{
			iFlag = SPK::FLAG_ALPHA;
			iParam = SPK::PARAM_ALPHA;
		}
	}

	void ModelDesc::UnSerialize( const YAML::Node& iNode )
	{
		SafeGet(iNode, "name", mName);
		SafeGet(iNode, "lifetime", mLifetime);

		CollectionIterator particleFile(&iNode);
		CollectionIterator params(particleFile.Extract("params"));
		while(!params.End())
		{
			ParamDesc paramDesc;

			params.Node() >> &paramDesc;

			mParams.push_back(paramDesc);

			params.Next();
		}
	}

	void ModelDesc::Serialize( YAML::Emitter& iEmitter ) const
	{
		
	}

	SPK::Model* ModelDesc::Create()
	{
		int enableFlag = 0;
		int mutableFlag = 0;
		int randomFlag = 0;
		int interpolatedFlag = 0;

		MakeFlags(enableFlag, mutableFlag, randomFlag, interpolatedFlag);

		SPK::Model* newModel = SPK::Model::create(enableFlag, mutableFlag, randomFlag, interpolatedFlag);

		newModel->setName(mName);
		
		if(mLifetime.size() >= 2)
			newModel->setLifeTime(mLifetime[0], mLifetime[1]);

		for(ParamDescVecIter iter = mParams.begin(); iter != mParams.end(); ++iter)
		{
			(*iter).AddParamTo(newModel);
		}

		newModel->setShared(true);

		return newModel;
	}

	void ModelDesc::MakeFlags( int& iEnableFlag, int& iMutableFlag, int& iRandomFlag, int& iInterpolatedFlag )
	{
		for(ParamDescVecIter iter = mParams.begin(); iter != mParams.end(); ++iter)
		{
			(*iter).AddFlags(iEnableFlag, iMutableFlag, iRandomFlag, iInterpolatedFlag);
		}
	}

	RendererDesc::RendererDesc()
		: mGroundCulling(false), mBlendingMode(sf::Blend::None), mZFactor(0.0f), mCustomOne(0.0f), mCustomTwo(0.0f)
	{

	}

	void RendererDesc::UnSerialize( const YAML::Node& iNode )
	{
		SafeGet(iNode, "name", mName);
		SafeGet(iNode, "type", mType);
		SafeGet(iNode, "ground_culling", mGroundCulling);
		std::string blendMode;
		SafeGet(iNode, "blend_mode", blendMode);
		mBlendingMode = GetModeByName(blendMode);
		SafeGet(iNode, "z_factor", mZFactor);

		SafeGet(iNode, "custom_one", mCustomOne);
		SafeGet(iNode, "custom_two", mCustomTwo);
		SafeGet(iNode, "image_name", mImageName);
	}

	void RendererDesc::Serialize( YAML::Emitter& iEmitter ) const
	{

	}

	SPK::SFML::SFMLRenderer* RendererDesc::Create()
	{
		SPK::SFML::SFMLRenderer* newRenderer = CreateRendererByName(mType);
		newRenderer->setName(mName);
		newRenderer->setGroundCulling(mGroundCulling);
		newRenderer->setBlendMode(mBlendingMode);
		newRenderer->setZFactor(mZFactor);

		newRenderer->setShared(true);

		return newRenderer;
	}

	sf::Blend::Mode RendererDesc::GetModeByName( const std::string& iName )
	{
		if(iName == "add")
		{
			return sf::Blend::Add;
		}
		else if(iName == "alpha")
		{
			return sf::Blend::Alpha;
		}
		else if(iName == "multiply")
		{
			return sf::Blend::Multiply;
		}

		return sf::Blend::None;
	}

	SPK::SFML::SFMLRenderer* RendererDesc::CreateRendererByName( const std::string& iName )
	{
		if(iName == "point")
		{
			return SPK::SFML::SFMLPointRenderer::create(mCustomOne);
		}
		else if(iName == "line")
		{
			return SPK::SFML::SFMLLineRenderer::create(mCustomOne, mCustomTwo);
		}

		Image* image = UResource(Image, mImageName);
		image->Load();
		return SPK::SFML::SFMLQuadRenderer::create(image, mCustomOne, mCustomTwo);
	}

	EmitterDesc::EmitterDesc()
		: mFlow(0.0f), mTank(0), mCustomFloatOne(0.0f), mCustomFloatTwo(0.0f), mUseBorders(false)
	{

	}

	void EmitterDesc::UnSerialize( const YAML::Node& iNode )
	{
		SafeGet(iNode, "name", mName);
		SafeGet(iNode, "type", mType);
		SafeGet(iNode, "flow", mFlow);
		SafeGet(iNode, "force", mForce);
		SafeGet(iNode, "tank", mTank);
		SafeGet(iNode, "use_borders", mUseBorders);
		SafeGet(iNode, "zone", &mZoneDesc);

		SafeGet(iNode, "custom_vec_one", mCustomVecOne);
		SafeGet(iNode, "custom_float_one", mCustomFloatOne);
		SafeGet(iNode, "custom_float_two", mCustomFloatTwo);
	}

	void EmitterDesc::Serialize( YAML::Emitter& iEmitter ) const
	{

	}

	SPK::Emitter* EmitterDesc::Create()
	{
		SPK::Emitter* newEmitter;
		newEmitter = CreateEmitterByName(mType);
		newEmitter->setName(mName);

		newEmitter->setFlow(mFlow);
		if(mForce.size() >= 2)
			newEmitter->setForce(mForce[0], mForce[1]);
		newEmitter->setTank(mTank);
		newEmitter->setZone(mZoneDesc.Create(), !mUseBorders);

		return newEmitter;
	}

	SPK::Emitter* EmitterDesc::CreateEmitterByName( const std::string& iName )
	{
		if(iName == "random")
		{
			return SPK::RandomEmitter::create();
		}
		else if(iName == "spheric")
		{
			return SPK::SphericEmitter::create(mCustomVecOne, mCustomFloatOne, mCustomFloatTwo);
		}
		else if(iName == "static")
		{
			return SPK::StaticEmitter::create();
		}
		else if(iName == "straight")
		{
			return SPK::StraightEmitter::create(mCustomVecOne);
		}

		return SPK::NormalEmitter::create();
	}

	void ZoneDesc::UnSerialize( const YAML::Node& iNode )
	{
		SafeGet(iNode, "type", mType);
		SafeGet(iNode, "custom_vec_one", mCustomVecOne);
		SafeGet(iNode, "custom_vec_two", mCustomVecTwo);
		SafeGet(iNode, "custom_float_one", mCustomFloatOne);
		SafeGet(iNode, "custom_float_two", mCustomFloatTwo);
	}

	void ZoneDesc::Serialize( YAML::Emitter& iEmitter ) const
	{

	}

	SPK::Zone* ZoneDesc::Create()
	{
		return CreateZoneByName(mType);
	}

	SPK::Zone* ZoneDesc::CreateZoneByName( const std::string& iName )
	{
		if(iName == "aabox")
		{
			return SPK::AABox::create(mCustomVecOne, mCustomVecTwo);
		}
		else if(iName == "line")
		{
			return SPK::Line::create(mCustomVecOne, mCustomVecTwo);
		}
		else if(iName == "plane")
		{
			return SPK::Plane::create(mCustomVecOne, mCustomVecTwo);
		}
		else if(iName == "ring")
		{
			return SPK::Ring::create(mCustomVecOne, mCustomVecTwo, mCustomFloatOne, mCustomFloatTwo);
		}
		else if(iName == "sphere")
		{
			return SPK::Sphere::create(mCustomVecOne, mCustomFloatOne);
		}

		return SPK::Point::create(mCustomVecOne);
	}

	void ModifierDesc::UnSerialize( const YAML::Node& iNode )
	{

	}

	void ModifierDesc::Serialize( YAML::Emitter& iEmitter ) const
	{

	}

	SPK::Modifier* ModifierDesc::Create()
	{
		return SPK::LinearForce::create();
	}
}