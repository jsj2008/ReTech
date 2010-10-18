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

namespace rt
{
	class CollectionIterator
	{
	public:
		CollectionIterator(const std::string& iFileName);
		CollectionIterator(const YAML::Node* iSectionNode);

		void Next();
		bool End();

		const YAML::Node& Node();

		float Progress();

		CollectionIterator Extract(const std::string& iSectionName);

		void Clear();

		template<class T>
		void SafeGet(const std::string iKey, T& iValue)
		{
			const YAML::Node* value = 0;

			switch(mSectionNode->GetType())
			{
			case YAML::CT_MAP:
				value = mSectionNode->FindValue(iKey);
				break;
			case YAML::CT_SEQUENCE:
				value = (*mSectionNode)[mCurrentIndex].FindValue(iKey);
				break;
			}		

			if(value)
			{
				*value >> iValue;
			}
		}

		template<class T>
		void SafeGet(const std::string iKey, fastdelegate::FastDelegate1<const T&, void> iSetter)
		{
			typename T tempValue;
			SafeGet(iKey, tempValue);

			iSetter(tempValue);
		}

		template<class T>
		void SafeGet(const std::string iKey, fastdelegate::FastDelegate1<T, void> iSetter)
		{
			typename T tempValue;
			SafeGet(iKey, tempValue);

			iSetter(tempValue);
		}

	protected:
		YAML::Node			mDocument;
		const YAML::Node*	mSectionNode;

		int					mCurrentIndex;
	};

	void SerializeYAML(const camp::UserObject& iObject, YAML::Emitter& iEmitter);
 	void UnserializeYAML(const camp::UserObject& iObject, const YAML::Node& iNode);
}