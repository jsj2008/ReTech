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

#ifndef __rtObjectsFactory_H__
#define __rtObjectsFactory_H__

namespace rt
{
	template<class T>
	class BaseInstantiator
	{
	public:
		virtual T* CreateInstance() = 0;
	};

	template<class C, class T>
	class Instantiator : public BaseInstantiator<T>
	{
	public:
		virtual T* CreateInstance()
		{
			return new C();
		}
	};

	template<class T>
	class ObjectsFactory
	{
	public:
		ObjectsFactory(){}
		~ObjectsFactory(){}

		template<class C>
		static bool RegisterObject(const std::string& iTypeName)
		{
			if(mRegisteredClasses.find(iTypeName) != mRegisteredClasses.end())
			{
				return false;
			}
			
			mRegisteredClasses[iTypeName] = boost::shared_ptr<BaseInstantiator<T> >(new Instantiator<C, T>());

			return true;
		}

		static T* CreateObject(const std::string& iTypeName)
		{
			std::string realTypeName = iTypeName;

			if(mRedirects.find(iTypeName) != mRedirects.end())
			{
				realTypeName = mRedirects[iTypeName];
			}

			if(mRegisteredClasses.find(iTypeName) == mRegisteredClasses.end())
			{
				return 0;
			}

			return mRegisteredClasses[iTypeName]->CreateInstance();
		}

		static void AddRedirect(const std::string& iClassFrom, const std::string& iClassTo)
		{
			mRedirects[iClassFrom] = iClassTo;
		}

		static void RemoveRedirect(const std::string& iClassFrom)
		{
			mRedirects.erase(iClassFrom);
		}

	protected:
		static std::map<std::string, boost::shared_ptr<BaseInstantiator<T> > >	mRegisteredClasses;
		static std::map<std::string, std::string>								mRedirects;
	};
}

#endif