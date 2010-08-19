#ifndef __rtCommonIncludes_H__
#define __rtCommonIncludes_H__

#include <time.h>
#include <assert.h>
#include <fstream>
#include <sstream>

#include "boost/shared_ptr.hpp"
#include "boost/weak_ptr.hpp"

#define POCO_STATIC
#include "POCO/SharedPtr.h"
#include "POCO/DynamicFactory.h"
#include "POCO/FileStream.h"
#include "poco/SingletonHolder.h"
#include "poco/NumberFormatter.h"
#include "poco/NumberParser.h"
#include "poco/Glob.h"
#include "poco/Path.h"
#include "poco/Any.h"
#include "poco/HashMap.h"
#include "poco/StringTokenizer.h"

#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"

#include "spark/SPK.h"
#include "spark/SPK_SFML.h"

#include "yaml-cpp/yaml.h"
#include "fastdelegates/fastdelegate.h"
#include "SFMath.h"

#include "ReTechLogManager.h"
#include "ReTechGameCore.h"
#include "ReTechOption.h"
#include "ReTechOptionsManager.h"
#include "ReTechObjectsFactory.h"
#include "ReTechSingleton.h"

//utilities helpers
#define UResource(Type, Name) static_cast<Type*>(ResourceManager::Get()->GetResource(Name))

#define URegisterObject(Class) rt::ObjectsFactory::RegisterObject<Class>(""#Class)

#define URegisterSingleton(Class) rt::Class* rt::Singleton<rt::Class>::mInstance = 0;

#endif