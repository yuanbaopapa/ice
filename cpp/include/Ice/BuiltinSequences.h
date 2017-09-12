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
// Generated from file `BuiltinSequences.ice'
//
// Warning: do not edit this file.
//
// </auto-generated>
//

#ifndef __Ice_BuiltinSequences_h__
#define __Ice_BuiltinSequences_h__

#include <IceUtil/PushDisableWarnings.h>
#include <Ice/ProxyF.h>
#include <Ice/ObjectF.h>
#include <Ice/ValueF.h>
#include <Ice/Exception.h>
#include <Ice/LocalObject.h>
#include <Ice/StreamHelpers.h>
#include <Ice/Comparable.h>
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

using BoolSeq = ::std::vector<bool>;

using ByteSeq = ::std::vector<::Ice::Byte>;

using ShortSeq = ::std::vector<short>;

using IntSeq = ::std::vector<int>;

using LongSeq = ::std::vector<long long int>;

using FloatSeq = ::std::vector<float>;

using DoubleSeq = ::std::vector<double>;

using StringSeq = ::std::vector<::std::string>;

using ObjectSeq = ::std::vector<::std::shared_ptr<::Ice::Value>>;

using ObjectProxySeq = ::std::vector<::std::shared_ptr<::Ice::ObjectPrx>>;

}

#else // C++98 mapping

namespace Ice
{

typedef ::std::vector<bool> BoolSeq;

typedef ::std::vector< ::Ice::Byte> ByteSeq;

typedef ::std::vector< ::Ice::Short> ShortSeq;

typedef ::std::vector< ::Ice::Int> IntSeq;

typedef ::std::vector< ::Ice::Long> LongSeq;

typedef ::std::vector< ::Ice::Float> FloatSeq;

typedef ::std::vector< ::Ice::Double> DoubleSeq;

typedef ::std::vector< ::std::string> StringSeq;

typedef ::std::vector< ::Ice::ObjectPtr> ObjectSeq;

typedef ::std::vector< ::Ice::ObjectPrx> ObjectProxySeq;

}

#endif

#include <IceUtil/PopDisableWarnings.h>
#endif