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

//utilities helpers
#define UResource(Type, Name) static_cast<Type*>(ResourceManager::Get()->GetResource(Name))

#define URegisterObject(Class) camp::classByType<Class>()
#define UDeclareUserObject virtual camp::UserObject ToUserObject(){ return camp::UserObject(this); }

#define URegisterSingleton(Class) rt::Class* rt::Singleton<rt::Class>::mInstance = 0;

#define UStringify(x) #x
#define UToString(x) UStringify(x)
#define ULocation __FILE__ "(" UToString(__LINE__) ") - " __FUNCTION__

#define ULogCritical(Message) rt::LogManager::Get()->Critical(Message, ULocation)
#define ULogError(Message) rt::LogManager::Get()->Error(Message, ULocation)
#define ULogWarning(Message) rt::LogManager::Get()->Warning(Message, ULocation)
#define ULogNotice(Message) rt::LogManager::Get()->Notice(Message, ULocation)

//Properties & type description helpers
#define UWriteablePropery(Property, Type) \
		public: \
		Type Get##Property(){ return m##Property; } \
		void Set##Property(const Type& i##Property){ m##Property = i##Property; } \
	 	protected: \
		Type m##Property;

#define UWriteableProperyOverride(Property, Type, Member) \
		public: \
		Type Get##Property(){ return Member; } \
		void Set##Property(const Type& i##Property){ Member = i##Property; }

#define UReadablePropery(Property, Type) \
		public: \
		Type Get##Property(){ return m##Property; } \
		protected: \
		Type m##Property;

#define UReadableProperyOverride(Property, Type, Member) \
		public: \
		Type Get##Property(){ return Member; }


#define UDesc_Begin(Type) \
	public: \
	static void RegisterMetaClass() \
	{ \
 	typedef Type LocalType; \
 	camp::Class::declare<Type>(UToString(Type))
	
#define UDesc_End ;}

#define UDesc_BaseClass(Base) \
	.base<Base>()

#define UDesc_Constructor \
	.constructor0()

#define UDesc_WriteableProperty(Property) \
	.property(UToString(Property), &LocalType::Get##Property, &LocalType::Set##Property)

#define UDesc_ReadableProperty(Property) \
	.property(UToString(Property), &LocalType::Get##Property)

#define UDesc_AutoType(Type) CAMP_AUTO_TYPE(rt::Type, &rt::Type::RegisterMetaClass)
