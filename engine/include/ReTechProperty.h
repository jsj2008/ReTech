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