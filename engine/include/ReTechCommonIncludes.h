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

#ifndef __rtCommonIncludes_H__
#define __rtCommonIncludes_H__

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

#include "sfgui/GUI.hpp"
#include "sfgui/Align.hpp"
#include "sfgui/Label.hpp"

//Extensions
#include "yaml-cpp/yaml.h"
#include "fastdelegates/fastdelegate.h"
#include "micropather.h"
#include "SFMath.h"

#include "ReTechLogManager.h"
#include "ReTechGameCore.h"
#include "ReTechOption.h"
#include "ReTechOptionsManager.h"
#include "ReTechObjectsFactory.h"
#include "ReTechSingleton.h"

//utilities helpers
#define UResource(Type, Name) static_cast<Type*>(ResourceManager::Get()->GetResource(Name))

#define URegisterObject(Class) URegisterObjectName(Class, ""#Class)
#define URegisterObjectName(Class, Name) rt::ObjectsFactory<rt::Serializeable>::RegisterObject<Class>(Name)

#define URegisterSingleton(Class) rt::Class* rt::Singleton<rt::Class>::mInstance = 0;

#endif