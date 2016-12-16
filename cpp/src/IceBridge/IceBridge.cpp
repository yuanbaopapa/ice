// **********************************************************************
//
// Copyright (c) 2003-2016 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <Ice/UUID.h>
#include <IceUtil/Options.h>
#include <Ice/Service.h>

using namespace std;
using namespace Ice;

namespace
{

//
// Represents a pending twoway invocation.
//
class Invocation : public IceUtil::Shared
{
public:

    Invocation(const AMD_Object_ice_invokePtr& cb) :
        _cb(cb)
    {
    }

    void success(bool ok, const pair<const Byte*, const Byte*>& results)
    {
        _cb->ice_response(ok, results);
    }

    void exception(const Exception& ex)
    {
        _cb->ice_exception(ex);
    }

private:

    AMD_Object_ice_invokePtr _cb;
};
typedef IceUtil::Handle<Invocation> InvocationPtr;

//
// Represents a pending oneway invocation.
//
class OnewayInvocation : public IceUtil::Shared
{
public:

    OnewayInvocation(const AMD_Object_ice_invokePtr& cb) :
        _cb(cb)
    {
    }

    void success(bool, const pair<const Byte*, const Byte*>&)
    {
        assert(false);
    }

    void exception(const Exception& ex)
    {
        _cb->ice_exception(ex);
    }

    void sent(bool sentSynchronously)
    {
        _cb->ice_response(true, vector<Byte>());
    }

private:

    AMD_Object_ice_invokePtr _cb;
};
typedef IceUtil::Handle<OnewayInvocation> OnewayInvocationPtr;

//
// Holds information about an incoming invocation that's been queued until an outgoing connection has
// been established.
//
struct QueuedInvocation : public IceUtil::Shared
{
    QueuedInvocation(const AMD_Object_ice_invokePtr& c, const pair<const Byte*, const Byte*>& p, const Current& curr) :
        cb(c), current(curr)
    {
        if(p.first)
        {
            //
            // The pointers in paramData refer to the Ice marshaling buffer and won't remain valid after
            // ice_invoke_async completes, so we have to make a copy of the parameter data.
            //
            vector<Byte> tmp(p.first, p.second);
            paramData.swap(tmp);
        }
    }

    const AMD_Object_ice_invokePtr cb;
    vector<Byte> paramData;
    const Current current;
};
typedef IceUtil::Handle<QueuedInvocation> QueuedInvocationPtr;

//
// This servant handles bidirectional traffic.
//
class BidirI : public Ice::BlobjectArrayAsync
{
public:

    BidirI(const ConnectionPtr&);

    virtual void ice_invoke_async(const AMD_Object_ice_invokePtr&, const pair<const Byte*, const Byte*>&,
                                  const Current&);

private:

    const ConnectionPtr _connection;
};

//
// Relays heartbeat messages.
//
class HeartbeatCallbackI : public HeartbeatCallback
{
public:

    HeartbeatCallbackI(const ConnectionPtr& con) :
        _connection(con)
    {
    }

    virtual void heartbeat(const ConnectionPtr&)
    {
        //
        // When a connection receives a heartbeat message, we send one over its corresponding connection.
        //
        try
        {
            _connection->begin_heartbeat();
        }
        catch(...)
        {
        }
    }

private:

    const ConnectionPtr _connection;
};

//
// Allows the bridge to be used as an Ice router.
//
class RouterI : public Router
{
public:

    virtual ObjectPrx getClientProxy(const Current&) const
    {
        return 0;
    }

    virtual ObjectPrx getServerProxy(const Current&) const
    {
        return 0;
    }

    virtual ObjectProxySeq addProxies(const ObjectProxySeq&, const Current&)
    {
        return ObjectProxySeq();
    }
};

class FinderI : public RouterFinder
{
public:

    FinderI(const RouterPrx& router) :
        _router(router)
    {
    }

    virtual RouterPrx getRouter(const Current&)
    {
        return _router;
    }

private:

    const RouterPrx _router;
};

//
// The main bridge servant.
//
class BridgeI : public Ice::BlobjectArrayAsync
{
public:

    BridgeI(const ObjectPrx&, bool);

    virtual void ice_invoke_async(const AMD_Object_ice_invokePtr&, const std::pair<const Byte*, const Byte*>&,
                                  const Current&);

    void createOutgoingConnection(const ConnectionPtr&);

    void outgoingConnectionEstablished(const ConnectionPtr&, const ConnectionPtr&);
    void outgoingConnectionFailed(const ConnectionPtr&, const Exception&);

    void connectionClosed(const ConnectionPtr&, bool);

private:

    typedef vector<QueuedInvocationPtr> InvocationList;

    void flush(const ConnectionPtr&, const InvocationList&);

    void send(const ConnectionPtr&, const AMD_Object_ice_invokePtr&, const std::pair<const Byte*, const Byte*>&,
              const Current&);

    const ObjectPrx _target;
    const bool _bidir;

    //
    // These are the incoming connections for which we are currently attempting to establish corresponding
    // outgoing connections. The map value is a list of invocations that are awaiting the new connection.
    //
    typedef map<ConnectionPtr, InvocationList> PendingConnectionMap;
    PendingConnectionMap _pendingConnections;

    typedef map<ConnectionPtr, ConnectionPtr> ConnectionMap;

    //
    // Maps incoming connections to outgoing connections.
    //
    ConnectionMap _incomingConnections;

    //
    // Maps outgoing connections to incoming connections.
    //
    ConnectionMap _outgoingConnections;

    IceUtil::Mutex _lock;
};
typedef IceUtil::Handle<BridgeI> BridgeIPtr;

class GetConnectionCallback : public IceUtil::Shared
{
public:

    GetConnectionCallback(const BridgeIPtr& bridge, const ConnectionPtr& con) :
        _bridge(bridge), _incoming(con)
    {
    }

    void success(const ConnectionPtr& outgoing)
    {
        _bridge->outgoingConnectionEstablished(_incoming, outgoing);
    }

    void exception(const Exception& ex)
    {
        _bridge->outgoingConnectionFailed(_incoming, ex);
    }

private:

    const BridgeIPtr _bridge;
    const ConnectionPtr _incoming;
    const ObjectPrx _target;
};
typedef IceUtil::Handle<GetConnectionCallback> GetConnectionCallbackPtr;

class CloseCallbackI : public CloseCallback
{
public:

    CloseCallbackI(const BridgeIPtr& bridge, bool incoming) :
        _bridge(bridge), _incoming(incoming)
    {
    }

    virtual void closed(const ConnectionPtr& con)
    {
        _bridge->connectionClosed(con, _incoming);
    }

private:

    const BridgeIPtr _bridge;
    const bool _incoming;
};

class BridgeService : public Service
{
public:

    BridgeService();

protected:

    virtual bool start(int, char*[], int&);
    virtual bool stop();
    virtual CommunicatorPtr initializeCommunicator(int&, char*[], const InitializationData&);

private:

    void usage(const std::string&);
};

}

BidirI::BidirI(const ConnectionPtr& connection) :
    _connection(connection)
{
}

void
BidirI::ice_invoke_async(const AMD_Object_ice_invokePtr& cb, const pair<const Byte*, const Byte*>& paramData,
                               const Current& current)
{
    //
    // We've received a callback invocation over a bidirectional connection.
    //

    try
    {
        //
        // Ask the connection to create a fixed proxy having the target identity.
        //
        ObjectPrx proxy = _connection->createProxy(current.id);

        if(!current.requestId)
        {
            //
            // If the request id is zero, it means the request was sent as either oneway or batch oneway.
            // (It can't be datagram or batch datagram because bidirectional requests aren't possible
            // over datagram connections.) We have no way of knowing whether the request was originally
            // sent in a batch but we can at least forward it as a oneway.
            //
            OnewayInvocationPtr i = new OnewayInvocation(cb);
            Callback_Object_ice_invokePtr d =
                newCallback_Object_ice_invoke(i, &OnewayInvocation::success, &OnewayInvocation::exception,
                                              &OnewayInvocation::sent);
            proxy->ice_oneway()->begin_ice_invoke(current.operation, current.mode, paramData, current.ctx, d);
        }
        else
        {
            //
            // Keep track of the AMD callback so that we can forward the reply when we receive it.
            //
            InvocationPtr i = new Invocation(cb);
            Callback_Object_ice_invokePtr d =
                newCallback_Object_ice_invoke(i, &Invocation::success, &Invocation::exception);
            proxy->begin_ice_invoke(current.operation, current.mode, paramData, current.ctx, d);
        }
    }
    catch(const std::exception& ex)
    {
        cb->ice_exception(ex);
    }
}

BridgeI::BridgeI(const ObjectPrx& target, bool bidir) :
    _target(target), _bidir(bidir)
{
}

void
BridgeI::ice_invoke_async(const AMD_Object_ice_invokePtr& cb, const pair<const Byte*, const Byte*>& paramData,
                          const Current& current)
{
    ConnectionPtr outgoing;

    {
        IceUtil::Mutex::Lock lock(_lock);

        ConnectionMap::iterator p = _incomingConnections.find(current.con);
        if(p != _incomingConnections.end())
        {
            outgoing = p->second;
        }
        else
        {
            //
            // Check if we're currently waiting for a corresponding outgoing connection to be established.
            //
            PendingConnectionMap::iterator q = _pendingConnections.find(current.con);
            if(q != _pendingConnections.end())
            {
                //
                // Queue the invocation until the connection is established.
                //
                q->second.push_back(new QueuedInvocation(cb, paramData, current));
            }
            else
            {
                //
                // The incoming connection is unknown to us.
                //

                //
                // Register a callback so that we can clean up when this connection closes.
                //
                current.con->setCloseCallback(new CloseCallbackI(this, true));

                //
                // Try to create a corresponding outgoing connection.
                //
                try
                {
                    createOutgoingConnection(current.con);

                    InvocationList l;
                    l.push_back(new QueuedInvocation(cb, paramData, current));
                    _pendingConnections.insert(make_pair(current.con, l));
                }
                catch(const std::exception& ex)
                {
                    cb->ice_exception(ex);
                }
            }
        }
    }

    if(outgoing)
    {
        send(outgoing, cb, paramData, current);
    }
}

void
BridgeI::createOutgoingConnection(const ConnectionPtr& incoming)
{
    EndpointInfoPtr info = incoming->getEndpoint()->getInfo();

    //
    // Create a target proxy that matches the configuration of the incoming connection.
    //
    ObjectPrx target;
    if(info->datagram())
    {
        target = _target->ice_datagram();
    }
    else if(info->secure())
    {
        target = _target->ice_secure(true);
    }
    else
    {
        target = _target;
    }

    //
    // Force the proxy to establish a new connection by using a unique connection ID.
    //
    target = target->ice_connectionId(Ice::generateUUID());

    //
    // Begin the connection establishment process asynchronously. This can take a while to complete,
    // especially when using Bluetooth.
    //
    GetConnectionCallbackPtr gc = new GetConnectionCallback(this, incoming);
    Callback_Object_ice_getConnectionPtr d =
        newCallback_Object_ice_getConnection(gc, &GetConnectionCallback::success, &GetConnectionCallback::exception);
    target->begin_ice_getConnection(d);
}

void
BridgeI::outgoingConnectionEstablished(const ConnectionPtr& incoming, const ConnectionPtr& outgoing)
{
    InvocationList queuedInvocations;

    //
    // Create a fixed proxy from the outgoing connection. We'll use this to forward all
    // requests from the incoming connection.
    //
    ObjectPrx target = outgoing->createProxy(stringToIdentity("dummy"));

    {
        IceUtil::Mutex::Lock lock(_lock);

        PendingConnectionMap::iterator p = _pendingConnections.find(incoming);
        if(p == _pendingConnections.end())
        {
            //
            // The incoming connection must have already been closed.
            //
            outgoing->close(false);
        }
        else
        {
            //
            // Save the queued invocations.
            //
            queuedInvocations.swap(p->second);
            _pendingConnections.erase(p);

            assert(_incomingConnections.find(incoming) == _incomingConnections.end());
            assert(_outgoingConnections.find(outgoing) == _outgoingConnections.end());

            _incomingConnections.insert(make_pair(incoming, outgoing));
            _outgoingConnections.insert(make_pair(outgoing, incoming));

            //
            // Register a callback so that we can clean up when this connection closes.
            //
            outgoing->setCloseCallback(new CloseCallbackI(this, false));

            //
            // Register hearbeat callbacks on both connections.
            //
            incoming->setHeartbeatCallback(new HeartbeatCallbackI(outgoing));
            outgoing->setHeartbeatCallback(new HeartbeatCallbackI(incoming));

            if(_bidir && !outgoing->getEndpoint()->getInfo()->datagram())
            {
                //
                // Configure the outgoing connection for bidirectional requests.
                //
                assert(!outgoing->getAdapter());

                ObjectAdapterPtr bidirOA = target->ice_getCommunicator()->createObjectAdapter("");
                bidirOA->addDefaultServant(new BidirI(incoming), "");
                bidirOA->activate();
                outgoing->setAdapter(bidirOA);
            }
        }
    }

    flush(outgoing, queuedInvocations);
}

void
BridgeI::outgoingConnectionFailed(const ConnectionPtr& incoming, const Exception&)
{
    //
    // Forcefully close the incoming connection. connectionClosed() will eventually be called for it.
    //
    // TBD: It would be better to gracefully close without waiting for pending invocations to complete (ICE-7468).
    //
    incoming->close(true);
}

void
BridgeI::connectionClosed(const ConnectionPtr& con, bool incoming)
{
    InvocationList queuedInvocations;
    ObjectAdapterPtr oa;
    ConnectionPtr toBeClosed;

    {
        IceUtil::Mutex::Lock lock(_lock);

        if(incoming)
        {
            //
            // An incoming connection was closed. It must be present in either _incomingConnections or
            // _pendingConnections.
            //
            ConnectionMap::iterator p = _incomingConnections.find(con);
            if(p != _incomingConnections.end())
            {
                toBeClosed = p->second;
                _incomingConnections.erase(p);
            }
            else
            {
                PendingConnectionMap::iterator q = _pendingConnections.find(con);
                assert(q != _pendingConnections.end());
                queuedInvocations.swap(q->second);
                _pendingConnections.erase(q);
            }
        }
        else
        {
            //
            // An outgoing connection was closed. It must be present in _outgoingConnections.
            //
            ConnectionMap::iterator p = _outgoingConnections.find(con);
            if(p != _outgoingConnections.end())
            {
                toBeClosed = p->second;
                _outgoingConnections.erase(p);
            }

            oa = con->getAdapter();
        }
    }

    if(oa)
    {
        oa->destroy();
    }

    //
    // Forcefully close the corresponding connection.
    //
    // TBD: It would be better to gracefully close without waiting for pending invocations to complete (ICE-7468).
    //
    if(toBeClosed)
    {
        toBeClosed->close(true);
    }

    //
    // Even though the connection is already closed, we still need to "complete" the pending invocations so
    // that the connection's dispatch count is updated correctly.
    //
    // TBD: We can remove this when ICE-7468 is fixed.
    //
    for(InvocationList::iterator p = queuedInvocations.begin(); p != queuedInvocations.end(); ++p)
    {
        QueuedInvocationPtr i = *p;
        i->cb->ice_exception(ConnectionLostException(__FILE__, __LINE__));
    }
}

void
BridgeI::flush(const ConnectionPtr& outgoing, const InvocationList& invocations)
{
    for(InvocationList::const_iterator p = invocations.begin(); p != invocations.end(); ++p)
    {
        QueuedInvocationPtr i = *p;

        pair<const Byte*, const Byte*> paramData;
        if(i->paramData.empty())
        {
            paramData.first = paramData.second = 0;
        }
        else
        {
            paramData.first = &i->paramData[0];
            paramData.second = paramData.first + i->paramData.size();
        }

        send(outgoing, i->cb, paramData, i->current);
    }
}

void
BridgeI::send(const ConnectionPtr& outgoing, const AMD_Object_ice_invokePtr& cb,
              const pair<const Byte*, const Byte*>& paramData, const Current& current)
{
    //
    // The target proxy's mode has already been (mostly) configured to match the incoming connection.
    //

    try
    {
        //
        // Create a proxy having the same identity as the incoming request.
        //
        ObjectPrx prx = outgoing->createProxy(current.id);

        if(!prx->ice_isTwoway() || !current.requestId)
        {
            if(prx->ice_isTwoway())
            {
                prx = prx->ice_oneway();
            }
            OnewayInvocationPtr i = new OnewayInvocation(cb);
            Callback_Object_ice_invokePtr d =
                newCallback_Object_ice_invoke(i, &OnewayInvocation::success, &OnewayInvocation::exception,
                                              &OnewayInvocation::sent);
            prx->begin_ice_invoke(current.operation, current.mode, paramData, current.ctx, d);
        }
        else
        {
            InvocationPtr i = new Invocation(cb);
            Callback_Object_ice_invokePtr d =
                newCallback_Object_ice_invoke(i, &Invocation::success, &Invocation::exception);
            prx->begin_ice_invoke(current.operation, current.mode, paramData, current.ctx, d);
        }
    }
    catch(const std::exception& ex)
    {
        cb->ice_exception(ex);
    }
}

BridgeService::BridgeService()
{
}

bool
BridgeService::start(int argc, char* argv[], int& status)
{
    IceUtilInternal::Options opts;
    opts.addOpt("h", "help");
    opts.addOpt("v", "version");

    vector<string> args;
    try
    {
        args = opts.parse(argc, const_cast<const char**>(argv));
    }
    catch(const IceUtilInternal::BadOptException& e)
    {
        error(e.reason);
        usage(argv[0]);
        return false;
    }

    if(opts.isSet("help"))
    {
        usage(argv[0]);
        status = EXIT_SUCCESS;
        return false;
    }
    if(opts.isSet("version"))
    {
        print(ICE_STRING_VERSION);
        status = EXIT_SUCCESS;
        return false;
    }

    if(!args.empty())
    {
        cerr << argv[0] << ": too many arguments" << endl;
        usage(argv[0]);
        return false;
    }

    PropertiesPtr properties = communicator()->getProperties();

    const string targetProperty = "IceBridge.Target.Endpoints";
    const string targetEndpoints = properties->getProperty(targetProperty);
    if(targetEndpoints.empty())
    {
        error("property '" + targetProperty + "' is not set");
        return false;
    }

    Ice::ObjectPrx target;

    try
    {
        target = communicator()->stringToProxy("dummy:" + targetEndpoints);
    }
    catch(const std::exception& ex)
    {
        ServiceError err(this);
        err << "setting for target endpoints '" << targetEndpoints << "' is invalid:\n" << ex;
        return false;
    }

    //
    // Support for bidirectional is always enabled.
    //
    const bool bidir = true;

    //
    // Initialize the object adapter.
    //
    const string endpointsProperty = "IceBridge.Source.Endpoints";
    if(properties->getProperty(endpointsProperty).empty())
    {
        error("property '" + endpointsProperty + "' is not set");
        return false;
    }

    ObjectAdapterPtr adapter = communicator()->createObjectAdapter("IceBridge.Source");

    adapter->addDefaultServant(new BridgeI(target, bidir), "");

    if(properties->getPropertyAsIntWithDefault("IceBridge.Router", 0) > 0)
    {
        RouterPrx router = RouterPrx::uncheckedCast(adapter->add(new RouterI, stringToIdentity("IceBridge/router")));
        adapter->add(new FinderI(router), stringToIdentity("Ice/RouterFinder"));
    }

    try
    {
        adapter->activate();
    }
    catch(const std::exception& ex)
    {
        {
            ServiceError err(this);
            err << "caught exception activating object adapter\n" << ex;
        }

        stop();
        return false;
    }

    return true;
}

bool
BridgeService::stop()
{
    return true;
}

CommunicatorPtr
BridgeService::initializeCommunicator(int& argc, char* argv[], const InitializationData& initializationData)
{
    InitializationData initData = initializationData;
    initData.properties = createProperties(argc, argv, initializationData.properties);

    StringSeq args = argsToStringSeq(argc, argv);
    args = initData.properties->parseCommandLineOptions("IceBridge", args);
    stringSeqToArgs(args, argc, argv);

    return Service::initializeCommunicator(argc, argv, initData);
}

void
BridgeService::usage(const string& appName)
{
    string options =
        "Options:\n"
        "-h, --help           Show this message.\n"
        "-v, --version        Display the Ice version.\n";
#ifndef _WIN32
    options.append(
        "--daemon             Run as a daemon.\n"
        "--pidfile FILE       Write process ID into FILE.\n"
        "--noclose            Do not close open file descriptors.\n"
        "--nochdir            Do not change the current working directory.\n"
    );
#endif
    print("Usage: " + appName + " [options]\n" + options);
}

#ifdef _WIN32

int
wmain(int argc, wchar_t* argv[])

#else

int
main(int argc, char* argv[])

#endif
{
    BridgeService svc;
    return svc.main(argc, argv);
}
