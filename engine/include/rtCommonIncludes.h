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

#include <time.h>
#include <assert.h>
#include <fstream>
#include <sstream>

//External libs
#include "boost/shared_ptr.hpp"
#include "boost/weak_ptr.hpp"
#include "boost/any.hpp"
#include "boost/tokenizer.hpp"
#include "boost/filesystem.hpp"
#include "boost/lexical_cast.hpp"

#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"

#include "spark/SPK.h"
#include "spark/SPK_SFML.h"

#include "camp/camptype.hpp"
#include "camp\class.hpp"
#include "camp\enum.hpp"
#include "camp\valuemapper.hpp"

#include "sfgui/GUI.hpp"
#include "sfgui/Align.hpp"
#include "sfgui/Label.hpp"
#include "sfgui/Spritebox.hpp"
#include "sfgui/DefaultImage.hpp"
#include "sfgui/Listbox.hpp"
#include "sfgui/Editbox.hpp"

//Extensions
#include "yaml-cpp/yaml.h"
#include "fastdelegates/fastdelegate.h"
#include "micropather.h"
#include "SFMath.h"

#include "rtLogManager.h"
#include "rtGameCore.h"
#include "rtOption.h"
#include "rtOptionsManager.h"
#include "rtSingleton.h"

#include "rtExternalTypes.h"

//utilities helpers
#define UResource(Type, Name) static_cast<Type*>(ResourceManager::Get()->GetResource(Name))

#define URegisterObject(Class) camp::classByType<Class>()
#define UDeclareUserObject virtual camp::UserObject ToUserObject(){ return camp::UserObject(this); }
#define UDeclareDynamicType(Type) namespace camp_ext{template <>struct ValueMapper<Type*>{static const int type = camp::userType;static camp::UserObject to(Type* const source){return source->ToUserObject();}template <typename T>static Type* from(const T& source){return 0;}};}

#define URegisterSingleton(Class) rt::Class* rt::Singleton<rt::Class>::mInstance = 0;