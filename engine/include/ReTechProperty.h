#ifndef __rtProperty_H__
#define __rtProperty_H__

namespace rt
{
	template<class T>
	class Property : public Serializeable
	{
	public:
		Property(const std::string iName, T& iVariable)
			: mName(iName), mVariable(&iVariable)
		{

		}

		Property(const std::string iName, fastdelegate::FastDelegate1<const T&, void> iSetter, fastdelegate::FastDelegate0<const T&> iGetter)
			: mName(iName), mVariable(0), mSetterConst(iSetter), mGetterConst(iGetter)
		{

		}

		Property(const std::string iName, fastdelegate::FastDelegate1<T, void> iSetter, fastdelegate::FastDelegate0<T> iGetter)
			: mName(iName), mVariable(0), mSetter(iSetter), mGetter(iGetter)
		{

		}

		~Property()
		{

		}

		void UnSerialize( const YAML::Node& iNode )
		{
			T tempVariable;
			if(SafeGet(iNode, mName, tempVariable))
			{
				Set(tempVariable);
			}
		}

		void Serialize( YAML::Emitter& iEmitter ) const
		{
			iEmitter << YAML::Key << mName;
			iEmitter << YAML::Value << Get();
		}

		void Set(const T& iVariable)
		{
			if(mVariable)
			{
				*mVariable = iVariable;
			}
			else if(mSetter)
			{
				mSetter(iVariable);
			}
			else if(mSetterConst)
			{
				mSetterConst(iVariable);
			}
		}

		T Get() const
		{
			T retValue;

			if(mVariable)
			{
				retValue = *mVariable;
			}
			else if(mSetter)
			{
				retValue = mGetter();
			}
			else if(mSetterConst)
			{
				retValue = mGetterConst();
			}

			return retValue;
		}

	protected:
		std::string									mName;
		T*											mVariable;
		fastdelegate::FastDelegate1<const T&, void> mSetterConst;
		fastdelegate::FastDelegate0<const T&>		mGetterConst;
		fastdelegate::FastDelegate1<T, void>		mSetter;
		fastdelegate::FastDelegate0<T>				mGetter;
	};
}

#endif