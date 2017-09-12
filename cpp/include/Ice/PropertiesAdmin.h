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
// Generated from file `PropertiesAdmin.ice'
//
// Warning: do not edit this file.
//
// </auto-generated>
//

#ifndef __Ice_PropertiesAdmin_h__
#define __Ice_PropertiesAdmin_h__

#include <IceUtil/PushDisableWarnings.h>
#include <Ice/ProxyF.h>
#include <Ice/ObjectF.h>
#include <Ice/ValueF.h>
#include <Ice/Exception.h>
#include <Ice/LocalObject.h>
#include <Ice/StreamHelpers.h>
#include <Ice/Comparable.h>
#include <Ice/Proxy.h>
#include <Ice/Object.h>
#include <Ice/GCObject.h>
#include <Ice/Value.h>
#include <Ice/Incoming.h>
#include <Ice/FactoryTableInit.h>
#include <IceUtil/ScopedArray.h>
#include <Ice/Optional.h>
#include <Ice/BuiltinSequences.h>
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

class PropertiesAdmin;
class PropertiesAdminPrx;

}

namespace Ice
{

using PropertyDict = ::std::map<::std::string, ::std::string>;

}

namespace Ice
{

class ICE_API PropertiesAdmin : public virtual ::Ice::Object
{
public:

    using ProxyType = PropertiesAdminPrx;

    virtual bool ice_isA(::std::string, const ::Ice::Current&) const override;
    virtual ::std::vector<::std::string> ice_ids(const ::Ice::Current&) const override;
    virtual ::std::string ice_id(const ::Ice::Current&) const override;

    static const ::std::string& ice_staticId();

    virtual ::std::string getProperty(::std::string, const ::Ice::Current&) = 0;
    bool _iceD_getProperty(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::PropertyDict getPropertiesForPrefix(::std::string, const ::Ice::Current&) = 0;
    bool _iceD_getPropertiesForPrefix(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void setProperties(::Ice::PropertyDict, const ::Ice::Current&) = 0;
    bool _iceD_setProperties(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool _iceDispatch(::IceInternal::Incoming&, const ::Ice::Current&) override;
};

}

namespace Ice
{

class ICE_CLASS(ICE_API) PropertiesAdminPrx : public virtual ::Ice::Proxy<PropertiesAdminPrx, ::Ice::ObjectPrx>
{
public:

    ::std::string getProperty(const ::std::string& iceP_key, const ::Ice::Context& context = Ice::noExplicitContext)
    {
        return _makePromiseOutgoing<::std::string>(true, this, &Ice::PropertiesAdminPrx::_iceI_getProperty, iceP_key, context).get();
    }

    template<template<typename> class P = ::std::promise>
    auto getPropertyAsync(const ::std::string& iceP_key, const ::Ice::Context& context = Ice::noExplicitContext)
        -> decltype(::std::declval<P<::std::string>>().get_future())
    {
        return _makePromiseOutgoing<::std::string, P>(false, this, &Ice::PropertiesAdminPrx::_iceI_getProperty, iceP_key, context);
    }

    ::std::function<void()>
    getPropertyAsync(const ::std::string& iceP_key,
                     ::std::function<void(::std::string)> response,
                     ::std::function<void(::std::exception_ptr)> ex = nullptr,
                     ::std::function<void(bool)> sent = nullptr,
                     const ::Ice::Context& context = Ice::noExplicitContext)
    {
        return _makeLamdaOutgoing<::std::string>(response, ex, sent, this, &Ice::PropertiesAdminPrx::_iceI_getProperty, iceP_key, context);
    }

    ICE_MEMBER(ICE_API) void _iceI_getProperty(const ::std::shared_ptr<::IceInternal::OutgoingAsyncT<::std::string>>&, const ::std::string&, const ::Ice::Context&);

    ::Ice::PropertyDict getPropertiesForPrefix(const ::std::string& iceP_prefix, const ::Ice::Context& context = Ice::noExplicitContext)
    {
        return _makePromiseOutgoing<::Ice::PropertyDict>(true, this, &Ice::PropertiesAdminPrx::_iceI_getPropertiesForPrefix, iceP_prefix, context).get();
    }

    template<template<typename> class P = ::std::promise>
    auto getPropertiesForPrefixAsync(const ::std::string& iceP_prefix, const ::Ice::Context& context = Ice::noExplicitContext)
        -> decltype(::std::declval<P<::Ice::PropertyDict>>().get_future())
    {
        return _makePromiseOutgoing<::Ice::PropertyDict, P>(false, this, &Ice::PropertiesAdminPrx::_iceI_getPropertiesForPrefix, iceP_prefix, context);
    }

    ::std::function<void()>
    getPropertiesForPrefixAsync(const ::std::string& iceP_prefix,
                                ::std::function<void(::Ice::PropertyDict)> response,
                                ::std::function<void(::std::exception_ptr)> ex = nullptr,
                                ::std::function<void(bool)> sent = nullptr,
                                const ::Ice::Context& context = Ice::noExplicitContext)
    {
        return _makeLamdaOutgoing<::Ice::PropertyDict>(response, ex, sent, this, &Ice::PropertiesAdminPrx::_iceI_getPropertiesForPrefix, iceP_prefix, context);
    }

    ICE_MEMBER(ICE_API) void _iceI_getPropertiesForPrefix(const ::std::shared_ptr<::IceInternal::OutgoingAsyncT<::Ice::PropertyDict>>&, const ::std::string&, const ::Ice::Context&);

    void setProperties(const ::Ice::PropertyDict& iceP_newProperties, const ::Ice::Context& context = Ice::noExplicitContext)
    {
        _makePromiseOutgoing<void>(true, this, &Ice::PropertiesAdminPrx::_iceI_setProperties, iceP_newProperties, context).get();
    }

    template<template<typename> class P = ::std::promise>
    auto setPropertiesAsync(const ::Ice::PropertyDict& iceP_newProperties, const ::Ice::Context& context = Ice::noExplicitContext)
        -> decltype(::std::declval<P<void>>().get_future())
    {
        return _makePromiseOutgoing<void, P>(false, this, &Ice::PropertiesAdminPrx::_iceI_setProperties, iceP_newProperties, context);
    }

    ::std::function<void()>
    setPropertiesAsync(const ::Ice::PropertyDict& iceP_newProperties,
                       ::std::function<void()> response,
                       ::std::function<void(::std::exception_ptr)> ex = nullptr,
                       ::std::function<void(bool)> sent = nullptr,
                       const ::Ice::Context& context = Ice::noExplicitContext)
    {
        return _makeLamdaOutgoing<void>(response, ex, sent, this, &Ice::PropertiesAdminPrx::_iceI_setProperties, iceP_newProperties, context);
    }

    ICE_MEMBER(ICE_API) void _iceI_setProperties(const ::std::shared_ptr<::IceInternal::OutgoingAsyncT<void>>&, const ::Ice::PropertyDict&, const ::Ice::Context&);

    ICE_MEMBER(ICE_API) static const ::std::string& ice_staticId();

protected:

    PropertiesAdminPrx() = default;
    friend ::std::shared_ptr<PropertiesAdminPrx> IceInternal::createProxy<PropertiesAdminPrx>();

    ICE_MEMBER(ICE_API) virtual ::std::shared_ptr<::Ice::ObjectPrx> _newInstance() const override;
};

}

namespace Ice
{

}

namespace Ice
{

using PropertiesAdminPtr = ::std::shared_ptr<PropertiesAdmin>;
using PropertiesAdminPrxPtr = ::std::shared_ptr<PropertiesAdminPrx>;

}

#else // C++98 mapping

namespace IceProxy
{

namespace Ice
{

class PropertiesAdmin;
ICE_API void _readProxy(::Ice::InputStream*, ::IceInternal::ProxyHandle< ::IceProxy::Ice::PropertiesAdmin>&);
ICE_API ::IceProxy::Ice::Object* upCast(::IceProxy::Ice::PropertiesAdmin*);

}

}

namespace Ice
{

class PropertiesAdmin;
ICE_API ::Ice::Object* upCast(::Ice::PropertiesAdmin*);
typedef ::IceInternal::Handle< ::Ice::PropertiesAdmin> PropertiesAdminPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::Ice::PropertiesAdmin> PropertiesAdminPrx;
typedef PropertiesAdminPrx PropertiesAdminPrxPtr;
ICE_API void _icePatchObjectPtr(PropertiesAdminPtr&, const ::Ice::ObjectPtr&);

}

namespace Ice
{

typedef ::std::map< ::std::string, ::std::string> PropertyDict;

}

namespace Ice
{

class Callback_PropertiesAdmin_getProperty_Base : public virtual ::IceInternal::CallbackBase { };
typedef ::IceUtil::Handle< Callback_PropertiesAdmin_getProperty_Base> Callback_PropertiesAdmin_getPropertyPtr;

class Callback_PropertiesAdmin_getPropertiesForPrefix_Base : public virtual ::IceInternal::CallbackBase { };
typedef ::IceUtil::Handle< Callback_PropertiesAdmin_getPropertiesForPrefix_Base> Callback_PropertiesAdmin_getPropertiesForPrefixPtr;

class Callback_PropertiesAdmin_setProperties_Base : public virtual ::IceInternal::CallbackBase { };
typedef ::IceUtil::Handle< Callback_PropertiesAdmin_setProperties_Base> Callback_PropertiesAdmin_setPropertiesPtr;

}

namespace IceProxy
{

namespace Ice
{

class ICE_CLASS(ICE_API) PropertiesAdmin : public virtual ::Ice::Proxy<PropertiesAdmin, ::IceProxy::Ice::Object>
{
public:

    ICE_MEMBER(ICE_API) ::std::string getProperty(const ::std::string& iceP_key, const ::Ice::Context& context = ::Ice::noExplicitContext)
    {
        return end_getProperty(_iceI_begin_getProperty(iceP_key, context, ::IceInternal::dummyCallback, 0, true));
    }

    ::Ice::AsyncResultPtr begin_getProperty(const ::std::string& iceP_key, const ::Ice::Context& context = ::Ice::noExplicitContext)
    {
        return _iceI_begin_getProperty(iceP_key, context, ::IceInternal::dummyCallback, 0);
    }

    ::Ice::AsyncResultPtr begin_getProperty(const ::std::string& iceP_key, const ::Ice::CallbackPtr& del, const ::Ice::LocalObjectPtr& cookie = 0)
    {
        return _iceI_begin_getProperty(iceP_key, ::Ice::noExplicitContext, del, cookie);
    }

    ::Ice::AsyncResultPtr begin_getProperty(const ::std::string& iceP_key, const ::Ice::Context& context, const ::Ice::CallbackPtr& del, const ::Ice::LocalObjectPtr& cookie = 0)
    {
        return _iceI_begin_getProperty(iceP_key, context, del, cookie);
    }

    ::Ice::AsyncResultPtr begin_getProperty(const ::std::string& iceP_key, const ::Ice::Callback_PropertiesAdmin_getPropertyPtr& del, const ::Ice::LocalObjectPtr& cookie = 0)
    {
        return _iceI_begin_getProperty(iceP_key, ::Ice::noExplicitContext, del, cookie);
    }

    ::Ice::AsyncResultPtr begin_getProperty(const ::std::string& iceP_key, const ::Ice::Context& context, const ::Ice::Callback_PropertiesAdmin_getPropertyPtr& del, const ::Ice::LocalObjectPtr& cookie = 0)
    {
        return _iceI_begin_getProperty(iceP_key, context, del, cookie);
    }

    ICE_MEMBER(ICE_API) ::std::string end_getProperty(const ::Ice::AsyncResultPtr&);

private:

    ICE_MEMBER(ICE_API) ::Ice::AsyncResultPtr _iceI_begin_getProperty(const ::std::string&, const ::Ice::Context&, const ::IceInternal::CallbackBasePtr&, const ::Ice::LocalObjectPtr& cookie = 0, bool sync = false);

public:

    ICE_MEMBER(ICE_API) ::Ice::PropertyDict getPropertiesForPrefix(const ::std::string& iceP_prefix, const ::Ice::Context& context = ::Ice::noExplicitContext)
    {
        return end_getPropertiesForPrefix(_iceI_begin_getPropertiesForPrefix(iceP_prefix, context, ::IceInternal::dummyCallback, 0, true));
    }

    ::Ice::AsyncResultPtr begin_getPropertiesForPrefix(const ::std::string& iceP_prefix, const ::Ice::Context& context = ::Ice::noExplicitContext)
    {
        return _iceI_begin_getPropertiesForPrefix(iceP_prefix, context, ::IceInternal::dummyCallback, 0);
    }

    ::Ice::AsyncResultPtr begin_getPropertiesForPrefix(const ::std::string& iceP_prefix, const ::Ice::CallbackPtr& del, const ::Ice::LocalObjectPtr& cookie = 0)
    {
        return _iceI_begin_getPropertiesForPrefix(iceP_prefix, ::Ice::noExplicitContext, del, cookie);
    }

    ::Ice::AsyncResultPtr begin_getPropertiesForPrefix(const ::std::string& iceP_prefix, const ::Ice::Context& context, const ::Ice::CallbackPtr& del, const ::Ice::LocalObjectPtr& cookie = 0)
    {
        return _iceI_begin_getPropertiesForPrefix(iceP_prefix, context, del, cookie);
    }

    ::Ice::AsyncResultPtr begin_getPropertiesForPrefix(const ::std::string& iceP_prefix, const ::Ice::Callback_PropertiesAdmin_getPropertiesForPrefixPtr& del, const ::Ice::LocalObjectPtr& cookie = 0)
    {
        return _iceI_begin_getPropertiesForPrefix(iceP_prefix, ::Ice::noExplicitContext, del, cookie);
    }

    ::Ice::AsyncResultPtr begin_getPropertiesForPrefix(const ::std::string& iceP_prefix, const ::Ice::Context& context, const ::Ice::Callback_PropertiesAdmin_getPropertiesForPrefixPtr& del, const ::Ice::LocalObjectPtr& cookie = 0)
    {
        return _iceI_begin_getPropertiesForPrefix(iceP_prefix, context, del, cookie);
    }

    ICE_MEMBER(ICE_API) ::Ice::PropertyDict end_getPropertiesForPrefix(const ::Ice::AsyncResultPtr&);

private:

    ICE_MEMBER(ICE_API) ::Ice::AsyncResultPtr _iceI_begin_getPropertiesForPrefix(const ::std::string&, const ::Ice::Context&, const ::IceInternal::CallbackBasePtr&, const ::Ice::LocalObjectPtr& cookie = 0, bool sync = false);

public:

    ICE_MEMBER(ICE_API) void setProperties(const ::Ice::PropertyDict& iceP_newProperties, const ::Ice::Context& context = ::Ice::noExplicitContext)
    {
        end_setProperties(_iceI_begin_setProperties(iceP_newProperties, context, ::IceInternal::dummyCallback, 0, true));
    }

    ::Ice::AsyncResultPtr begin_setProperties(const ::Ice::PropertyDict& iceP_newProperties, const ::Ice::Context& context = ::Ice::noExplicitContext)
    {
        return _iceI_begin_setProperties(iceP_newProperties, context, ::IceInternal::dummyCallback, 0);
    }

    ::Ice::AsyncResultPtr begin_setProperties(const ::Ice::PropertyDict& iceP_newProperties, const ::Ice::CallbackPtr& del, const ::Ice::LocalObjectPtr& cookie = 0)
    {
        return _iceI_begin_setProperties(iceP_newProperties, ::Ice::noExplicitContext, del, cookie);
    }

    ::Ice::AsyncResultPtr begin_setProperties(const ::Ice::PropertyDict& iceP_newProperties, const ::Ice::Context& context, const ::Ice::CallbackPtr& del, const ::Ice::LocalObjectPtr& cookie = 0)
    {
        return _iceI_begin_setProperties(iceP_newProperties, context, del, cookie);
    }

    ::Ice::AsyncResultPtr begin_setProperties(const ::Ice::PropertyDict& iceP_newProperties, const ::Ice::Callback_PropertiesAdmin_setPropertiesPtr& del, const ::Ice::LocalObjectPtr& cookie = 0)
    {
        return _iceI_begin_setProperties(iceP_newProperties, ::Ice::noExplicitContext, del, cookie);
    }

    ::Ice::AsyncResultPtr begin_setProperties(const ::Ice::PropertyDict& iceP_newProperties, const ::Ice::Context& context, const ::Ice::Callback_PropertiesAdmin_setPropertiesPtr& del, const ::Ice::LocalObjectPtr& cookie = 0)
    {
        return _iceI_begin_setProperties(iceP_newProperties, context, del, cookie);
    }

    ICE_MEMBER(ICE_API) void end_setProperties(const ::Ice::AsyncResultPtr&);

private:

    ICE_MEMBER(ICE_API) ::Ice::AsyncResultPtr _iceI_begin_setProperties(const ::Ice::PropertyDict&, const ::Ice::Context&, const ::IceInternal::CallbackBasePtr&, const ::Ice::LocalObjectPtr& cookie = 0, bool sync = false);

public:

    ICE_MEMBER(ICE_API) static const ::std::string& ice_staticId();

protected:

    ICE_MEMBER(ICE_API) virtual ::IceProxy::Ice::Object* _newInstance() const;
};

}

}

namespace Ice
{

class ICE_API PropertiesAdmin : public virtual ::Ice::Object
{
public:

    typedef PropertiesAdminPrx ProxyType;
    typedef PropertiesAdminPtr PointerType;

    virtual ~PropertiesAdmin();

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::emptyCurrent) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::emptyCurrent) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::emptyCurrent) const;

    static const ::std::string& ice_staticId();

    virtual ::std::string getProperty(const ::std::string&, const ::Ice::Current& = ::Ice::emptyCurrent) = 0;
    bool _iceD_getProperty(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::PropertyDict getPropertiesForPrefix(const ::std::string&, const ::Ice::Current& = ::Ice::emptyCurrent) = 0;
    bool _iceD_getPropertiesForPrefix(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void setProperties(const ::Ice::PropertyDict&, const ::Ice::Current& = ::Ice::emptyCurrent) = 0;
    bool _iceD_setProperties(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool _iceDispatch(::IceInternal::Incoming&, const ::Ice::Current&);

protected:

    virtual void _iceWriteImpl(::Ice::OutputStream*) const;
    virtual void _iceReadImpl(::Ice::InputStream*);
};

inline bool operator==(const PropertiesAdmin& lhs, const PropertiesAdmin& rhs)
{
    return static_cast<const ::Ice::Object&>(lhs) == static_cast<const ::Ice::Object&>(rhs);
}

inline bool operator<(const PropertiesAdmin& lhs, const PropertiesAdmin& rhs)
{
    return static_cast<const ::Ice::Object&>(lhs) < static_cast<const ::Ice::Object&>(rhs);
}

}

namespace Ice
{

}

namespace Ice
{

template<class T>
class CallbackNC_PropertiesAdmin_getProperty : public Callback_PropertiesAdmin_getProperty_Base, public ::IceInternal::TwowayCallbackNC<T>
{
public:

    typedef IceUtil::Handle<T> TPtr;

    typedef void (T::*Exception)(const ::Ice::Exception&);
    typedef void (T::*Sent)(bool);
    typedef void (T::*Response)(const ::std::string&);

    CallbackNC_PropertiesAdmin_getProperty(const TPtr& obj, Response cb, Exception excb, Sent sentcb)
        : ::IceInternal::TwowayCallbackNC<T>(obj, cb != 0, excb, sentcb), _response(cb)
    {
    }

    virtual void completed(const ::Ice::AsyncResultPtr& result) const
    {
        ::Ice::PropertiesAdminPrx proxy = ::Ice::PropertiesAdminPrx::uncheckedCast(result->getProxy());
        ::std::string ret;
        try
        {
            ret = proxy->end_getProperty(result);
        }
        catch(const ::Ice::Exception& ex)
        {
            ::IceInternal::CallbackNC<T>::exception(result, ex);
            return;
        }
        if(_response)
        {
            (::IceInternal::CallbackNC<T>::_callback.get()->*_response)(ret);
        }
    }

private:

    Response _response;
};

template<class T> Callback_PropertiesAdmin_getPropertyPtr
newCallback_PropertiesAdmin_getProperty(const IceUtil::Handle<T>& instance, void (T::*cb)(const ::std::string&), void (T::*excb)(const ::Ice::Exception&), void (T::*sentcb)(bool) = 0)
{
    return new CallbackNC_PropertiesAdmin_getProperty<T>(instance, cb, excb, sentcb);
}

template<class T> Callback_PropertiesAdmin_getPropertyPtr
newCallback_PropertiesAdmin_getProperty(T* instance, void (T::*cb)(const ::std::string&), void (T::*excb)(const ::Ice::Exception&), void (T::*sentcb)(bool) = 0)
{
    return new CallbackNC_PropertiesAdmin_getProperty<T>(instance, cb, excb, sentcb);
}

template<class T, typename CT>
class Callback_PropertiesAdmin_getProperty : public Callback_PropertiesAdmin_getProperty_Base, public ::IceInternal::TwowayCallback<T, CT>
{
public:

    typedef IceUtil::Handle<T> TPtr;

    typedef void (T::*Exception)(const ::Ice::Exception& , const CT&);
    typedef void (T::*Sent)(bool , const CT&);
    typedef void (T::*Response)(const ::std::string&, const CT&);

    Callback_PropertiesAdmin_getProperty(const TPtr& obj, Response cb, Exception excb, Sent sentcb)
        : ::IceInternal::TwowayCallback<T, CT>(obj, cb != 0, excb, sentcb), _response(cb)
    {
    }

    virtual void completed(const ::Ice::AsyncResultPtr& result) const
    {
        ::Ice::PropertiesAdminPrx proxy = ::Ice::PropertiesAdminPrx::uncheckedCast(result->getProxy());
        ::std::string ret;
        try
        {
            ret = proxy->end_getProperty(result);
        }
        catch(const ::Ice::Exception& ex)
        {
            ::IceInternal::Callback<T, CT>::exception(result, ex);
            return;
        }
        if(_response)
        {
            (::IceInternal::Callback<T, CT>::_callback.get()->*_response)(ret, CT::dynamicCast(result->getCookie()));
        }
    }

private:

    Response _response;
};

template<class T, typename CT> Callback_PropertiesAdmin_getPropertyPtr
newCallback_PropertiesAdmin_getProperty(const IceUtil::Handle<T>& instance, void (T::*cb)(const ::std::string&, const CT&), void (T::*excb)(const ::Ice::Exception&, const CT&), void (T::*sentcb)(bool, const CT&) = 0)
{
    return new Callback_PropertiesAdmin_getProperty<T, CT>(instance, cb, excb, sentcb);
}

template<class T, typename CT> Callback_PropertiesAdmin_getPropertyPtr
newCallback_PropertiesAdmin_getProperty(T* instance, void (T::*cb)(const ::std::string&, const CT&), void (T::*excb)(const ::Ice::Exception&, const CT&), void (T::*sentcb)(bool, const CT&) = 0)
{
    return new Callback_PropertiesAdmin_getProperty<T, CT>(instance, cb, excb, sentcb);
}

template<class T>
class CallbackNC_PropertiesAdmin_getPropertiesForPrefix : public Callback_PropertiesAdmin_getPropertiesForPrefix_Base, public ::IceInternal::TwowayCallbackNC<T>
{
public:

    typedef IceUtil::Handle<T> TPtr;

    typedef void (T::*Exception)(const ::Ice::Exception&);
    typedef void (T::*Sent)(bool);
    typedef void (T::*Response)(const ::Ice::PropertyDict&);

    CallbackNC_PropertiesAdmin_getPropertiesForPrefix(const TPtr& obj, Response cb, Exception excb, Sent sentcb)
        : ::IceInternal::TwowayCallbackNC<T>(obj, cb != 0, excb, sentcb), _response(cb)
    {
    }

    virtual void completed(const ::Ice::AsyncResultPtr& result) const
    {
        ::Ice::PropertiesAdminPrx proxy = ::Ice::PropertiesAdminPrx::uncheckedCast(result->getProxy());
        ::Ice::PropertyDict ret;
        try
        {
            ret = proxy->end_getPropertiesForPrefix(result);
        }
        catch(const ::Ice::Exception& ex)
        {
            ::IceInternal::CallbackNC<T>::exception(result, ex);
            return;
        }
        if(_response)
        {
            (::IceInternal::CallbackNC<T>::_callback.get()->*_response)(ret);
        }
    }

private:

    Response _response;
};

template<class T> Callback_PropertiesAdmin_getPropertiesForPrefixPtr
newCallback_PropertiesAdmin_getPropertiesForPrefix(const IceUtil::Handle<T>& instance, void (T::*cb)(const ::Ice::PropertyDict&), void (T::*excb)(const ::Ice::Exception&), void (T::*sentcb)(bool) = 0)
{
    return new CallbackNC_PropertiesAdmin_getPropertiesForPrefix<T>(instance, cb, excb, sentcb);
}

template<class T> Callback_PropertiesAdmin_getPropertiesForPrefixPtr
newCallback_PropertiesAdmin_getPropertiesForPrefix(T* instance, void (T::*cb)(const ::Ice::PropertyDict&), void (T::*excb)(const ::Ice::Exception&), void (T::*sentcb)(bool) = 0)
{
    return new CallbackNC_PropertiesAdmin_getPropertiesForPrefix<T>(instance, cb, excb, sentcb);
}

template<class T, typename CT>
class Callback_PropertiesAdmin_getPropertiesForPrefix : public Callback_PropertiesAdmin_getPropertiesForPrefix_Base, public ::IceInternal::TwowayCallback<T, CT>
{
public:

    typedef IceUtil::Handle<T> TPtr;

    typedef void (T::*Exception)(const ::Ice::Exception& , const CT&);
    typedef void (T::*Sent)(bool , const CT&);
    typedef void (T::*Response)(const ::Ice::PropertyDict&, const CT&);

    Callback_PropertiesAdmin_getPropertiesForPrefix(const TPtr& obj, Response cb, Exception excb, Sent sentcb)
        : ::IceInternal::TwowayCallback<T, CT>(obj, cb != 0, excb, sentcb), _response(cb)
    {
    }

    virtual void completed(const ::Ice::AsyncResultPtr& result) const
    {
        ::Ice::PropertiesAdminPrx proxy = ::Ice::PropertiesAdminPrx::uncheckedCast(result->getProxy());
        ::Ice::PropertyDict ret;
        try
        {
            ret = proxy->end_getPropertiesForPrefix(result);
        }
        catch(const ::Ice::Exception& ex)
        {
            ::IceInternal::Callback<T, CT>::exception(result, ex);
            return;
        }
        if(_response)
        {
            (::IceInternal::Callback<T, CT>::_callback.get()->*_response)(ret, CT::dynamicCast(result->getCookie()));
        }
    }

private:

    Response _response;
};

template<class T, typename CT> Callback_PropertiesAdmin_getPropertiesForPrefixPtr
newCallback_PropertiesAdmin_getPropertiesForPrefix(const IceUtil::Handle<T>& instance, void (T::*cb)(const ::Ice::PropertyDict&, const CT&), void (T::*excb)(const ::Ice::Exception&, const CT&), void (T::*sentcb)(bool, const CT&) = 0)
{
    return new Callback_PropertiesAdmin_getPropertiesForPrefix<T, CT>(instance, cb, excb, sentcb);
}

template<class T, typename CT> Callback_PropertiesAdmin_getPropertiesForPrefixPtr
newCallback_PropertiesAdmin_getPropertiesForPrefix(T* instance, void (T::*cb)(const ::Ice::PropertyDict&, const CT&), void (T::*excb)(const ::Ice::Exception&, const CT&), void (T::*sentcb)(bool, const CT&) = 0)
{
    return new Callback_PropertiesAdmin_getPropertiesForPrefix<T, CT>(instance, cb, excb, sentcb);
}

template<class T>
class CallbackNC_PropertiesAdmin_setProperties : public Callback_PropertiesAdmin_setProperties_Base, public ::IceInternal::OnewayCallbackNC<T>
{
public:

    typedef IceUtil::Handle<T> TPtr;

    typedef void (T::*Exception)(const ::Ice::Exception&);
    typedef void (T::*Sent)(bool);
    typedef void (T::*Response)();

    CallbackNC_PropertiesAdmin_setProperties(const TPtr& obj, Response cb, Exception excb, Sent sentcb)
        : ::IceInternal::OnewayCallbackNC<T>(obj, cb, excb, sentcb)
    {
    }
};

template<class T> Callback_PropertiesAdmin_setPropertiesPtr
newCallback_PropertiesAdmin_setProperties(const IceUtil::Handle<T>& instance, void (T::*cb)(), void (T::*excb)(const ::Ice::Exception&), void (T::*sentcb)(bool) = 0)
{
    return new CallbackNC_PropertiesAdmin_setProperties<T>(instance, cb, excb, sentcb);
}

template<class T> Callback_PropertiesAdmin_setPropertiesPtr
newCallback_PropertiesAdmin_setProperties(const IceUtil::Handle<T>& instance, void (T::*excb)(const ::Ice::Exception&), void (T::*sentcb)(bool) = 0)
{
    return new CallbackNC_PropertiesAdmin_setProperties<T>(instance, 0, excb, sentcb);
}

template<class T> Callback_PropertiesAdmin_setPropertiesPtr
newCallback_PropertiesAdmin_setProperties(T* instance, void (T::*cb)(), void (T::*excb)(const ::Ice::Exception&), void (T::*sentcb)(bool) = 0)
{
    return new CallbackNC_PropertiesAdmin_setProperties<T>(instance, cb, excb, sentcb);
}

template<class T> Callback_PropertiesAdmin_setPropertiesPtr
newCallback_PropertiesAdmin_setProperties(T* instance, void (T::*excb)(const ::Ice::Exception&), void (T::*sentcb)(bool) = 0)
{
    return new CallbackNC_PropertiesAdmin_setProperties<T>(instance, 0, excb, sentcb);
}

template<class T, typename CT>
class Callback_PropertiesAdmin_setProperties : public Callback_PropertiesAdmin_setProperties_Base, public ::IceInternal::OnewayCallback<T, CT>
{
public:

    typedef IceUtil::Handle<T> TPtr;

    typedef void (T::*Exception)(const ::Ice::Exception& , const CT&);
    typedef void (T::*Sent)(bool , const CT&);
    typedef void (T::*Response)(const CT&);

    Callback_PropertiesAdmin_setProperties(const TPtr& obj, Response cb, Exception excb, Sent sentcb)
        : ::IceInternal::OnewayCallback<T, CT>(obj, cb, excb, sentcb)
    {
    }
};

template<class T, typename CT> Callback_PropertiesAdmin_setPropertiesPtr
newCallback_PropertiesAdmin_setProperties(const IceUtil::Handle<T>& instance, void (T::*cb)(const CT&), void (T::*excb)(const ::Ice::Exception&, const CT&), void (T::*sentcb)(bool, const CT&) = 0)
{
    return new Callback_PropertiesAdmin_setProperties<T, CT>(instance, cb, excb, sentcb);
}

template<class T, typename CT> Callback_PropertiesAdmin_setPropertiesPtr
newCallback_PropertiesAdmin_setProperties(const IceUtil::Handle<T>& instance, void (T::*excb)(const ::Ice::Exception&, const CT&), void (T::*sentcb)(bool, const CT&) = 0)
{
    return new Callback_PropertiesAdmin_setProperties<T, CT>(instance, 0, excb, sentcb);
}

template<class T, typename CT> Callback_PropertiesAdmin_setPropertiesPtr
newCallback_PropertiesAdmin_setProperties(T* instance, void (T::*cb)(const CT&), void (T::*excb)(const ::Ice::Exception&, const CT&), void (T::*sentcb)(bool, const CT&) = 0)
{
    return new Callback_PropertiesAdmin_setProperties<T, CT>(instance, cb, excb, sentcb);
}

template<class T, typename CT> Callback_PropertiesAdmin_setPropertiesPtr
newCallback_PropertiesAdmin_setProperties(T* instance, void (T::*excb)(const ::Ice::Exception&, const CT&), void (T::*sentcb)(bool, const CT&) = 0)
{
    return new Callback_PropertiesAdmin_setProperties<T, CT>(instance, 0, excb, sentcb);
}

}

#endif

#include <IceUtil/PopDisableWarnings.h>
#endif