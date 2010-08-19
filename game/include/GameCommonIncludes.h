#ifndef __GameCommonIncludes_H__
#define __GameCommonIncludes_H__

#include "ReTech.h"
#undef URegisterSingleton
#define URegisterSingleton(Class) Class* rt::Singleton<Class>::mInstance = 0;

#endif