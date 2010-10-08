#include "ReTechCommonIncludes.h"
#include "ReTechObjectsFactory.h"
#include "ReTechSerializeable.h"

template<> std::map<std::string, boost::shared_ptr<rt::BaseInstantiator<rt::Serializeable> > >	rt::ObjectsFactory<rt::Serializeable>::mRegisteredClasses;
template<> std::map<std::string, std::string> rt::ObjectsFactory<rt::Serializeable>::mRedirects;