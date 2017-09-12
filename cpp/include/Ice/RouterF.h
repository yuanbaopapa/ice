// **********************************************************************
//
// Copyright (c) 2003-2017 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************
//
// Ice version 3.7.0
//
// <auto-generated>
//
// Generated from file `RouterF.ice'
//
// Warning: do not edit this file.
//
// </auto-generated>
//

#ifndef __Ice_RouterF_h__
#define __Ice_RouterF_h__

#include <IceUtil/PushDisableWarnings.h>
#include <Ice/ProxyF.h>
#include <Ice/ObjectF.h>
#include <Ice/ValueF.h>
#include <Ice/Exception.h>
#include <Ice/LocalObject.h>
#include <Ice/StreamHelpers.h>
#include <Ice/Comparable.h>
#include <Ice/Proxy.h>
#include <IceUtil/ScopedArray.h>
#include <Ice/Optional.h>
#include <IceUtil/UndefSysMacros.h>

#ifndef ICE_IGNORE_VERSION
#   if ICE_INT_VERSION / 100 != 307
#       error Ice version mismatch!
#   endif
#   if ICE_INT_VERSION % 100 > 50
#       error Beta header file detected
#   endif
#   if ICE_INT_VERSION % 100 < 0
#       error Ice patch level mismatch!
#   endif
#endif

#ifndef ICE_API
#   if defined(ICE_STATIC_LIBS)
#       define ICE_API /**/
#   elif defined(ICE_API_EXPORTS)
#       define ICE_API ICE_DECLSPEC_EXPORT
#   else
#       define ICE_API ICE_DECLSPEC_IMPORT
#   endif
#endif

#ifdef ICE_CPP11_MAPPING // C++11 mapping

namespace Ice
{

class Router;
class RouterPrx;

}

namespace Ice
{

}

namespace Ice
{

using RouterPtr = ::std::shared_ptr<Router>;
using RouterPrxPtr = ::std::shared_ptr<RouterPrx>;

}

#else // C++98 mapping

namespace IceProxy
{

namespace Ice
{

class Router;
ICE_API void _readProxy(::Ice::InputStream*, ::IceInternal::ProxyHandle< ::IceProxy::Ice::Router>&);
ICE_API ::IceProxy::Ice::Object* upCast(::IceProxy::Ice::Router*);

}

}

namespace Ice
{

class Router;
ICE_API ::Ice::Object* upCast(::Ice::Router*);
typedef ::IceInternal::Handle< ::Ice::Router> RouterPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::Ice::Router> RouterPrx;
typedef RouterPrx RouterPrxPtr;
ICE_API void _icePatchObjectPtr(RouterPtr&, const ::Ice::ObjectPtr&);

}

namespace Ice
{

}

#endif

#include <IceUtil/PopDisableWarnings.h>
#endif
