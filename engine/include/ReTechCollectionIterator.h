#ifndef __rtCollectionIterator_H__
#define __rtCollectionIterator_H__

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
			const YAML::Node* value = (*mSectionNode)[mCurrentIndex].FindValue(iKey);

			if(value)
			{
				*value >> iValue;
			}
		}

		template<class T>
		void SafeGet(const std::string iKey, fastdelegate::FastDelegate1<const T&, void> iSetter)
		{
			typename T tempValue;
			SafeGet((*mSectionNode)[mCurrentIndex], iKey, tempValue);

			iSetter(tempValue);
		}

		template<class T>
		void SafeGet(const std::string iKey, fastdelegate::FastDelegate1<T, void> iSetter)
		{
			typename T tempValue;
			SafeGet((*mSectionNode)[mCurrentIndex], iKey, tempValue);

			iSetter(tempValue);
		}

	protected:
		YAML::Node			mDocument;
		const YAML::Node*	mSectionNode;

		int					mCurrentIndex;
	};
}

#endif