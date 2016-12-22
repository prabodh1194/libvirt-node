// __virConnect.cc
#include "virconnect.h"

Persistent<Function> __virConnect::constructor;

__virConnect::__virConnect(std::string uri) 
{
    _conn = virConnectOpen(uri.c_str());
}

__virConnect::~__virConnect()
{
    virConnectClose(_conn);
}

void __virConnect::Init(Local<Object> exports)
{
    Isolate* isolate = exports->GetIsolate();

    // Prepare constructor template
    Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
    tpl->SetClassName(String::NewFromUtf8(isolate, "__virConnect"));
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    // Prototype
    NODE_SET_PROTOTYPE_METHOD(tpl, "getURI", getURI);
    NODE_SET_PROTOTYPE_METHOD(tpl, "lookupByID", lookupByID);

    constructor.Reset(isolate, tpl->GetFunction());
    exports->Set(String::NewFromUtf8(isolate, "__virConnect"), tpl->GetFunction());
}

void __virConnect::New(const FunctionCallbackInfo<Value>& args)
{
    // Invoked as constructor: `new __virConnect(...)`
    if (args.IsConstructCall())
    {
        args.GetReturnValue().Set(args.This());
    }
}

void __virConnect::getURI(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();

    __virConnect* obj = ObjectWrap::Unwrap<__virConnect>(args.Holder());
    std::string a = virConnectGetURI(obj->_conn);
    args.GetReturnValue().Set(String::NewFromUtf8(isolate, a.c_str()));
}

void __virConnect::lookupByID(const FunctionCallbackInfo<Value>& args)
{

    int domID = args[0]->NumberValue();
    __virConnect* obj = ObjectWrap::Unwrap<__virConnect>(args.Holder());

    virDomainPtr domain = virDomainLookupByID(obj->_conn, domID);
    __virDomain *dom = new __virDomain(domain);

    dom->wrap(args);
}

void __virConnect::wrap(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();

    Local<Function> cons = Local<Function>::New(isolate, constructor);
    Local<Context> context = isolate->GetCurrentContext();
    Local<Object> instance = cons->NewInstance(context).ToLocalChecked();

    this->Wrap(instance);
    args.GetReturnValue().Set(instance);
}
