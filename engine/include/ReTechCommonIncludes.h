#ifndef __rtCommonIncludes_H__
#define __rtCommonIncludes_H__

#include <time.h>
#include <assert.h>
#include <fstream>
#include <sstream>

//External libs
#define BOOST_ALL_DYN_LINK
#include "boost/shared_ptr.hpp"
#include "boost/weak_ptr.hpp"
#include "boost/any.hpp"
#include "boost/tokenizer.hpp"
#include "boost/filesystem/path.hpp"
#include "boost/lexical_cast.hpp"

#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"

#include "spark/SPK.h"
#include "spark/SPK_SFML.h"

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