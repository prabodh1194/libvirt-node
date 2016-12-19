// __virConnect.cc
#include <string>
#include "virconnect.h"

using v8::Context;
using v8::Function;
using v8::FunctionCallbackInfo;
using v8::FunctionTemplate;
using v8::Isolate;
using v8::Local;
using v8::Number;
using v8::Object;
using v8::Persistent;
using v8::String;
using v8::Value;

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

    constructor.Reset(isolate, tpl->GetFunction());
    exports->Set(String::NewFromUtf8(isolate, "__virConnect"), tpl->GetFunction());
}

void __virConnect::New(const FunctionCallbackInfo<Value>& args)
{
    //Isolate* isolate = args.GetIsolate();

    if (args.IsConstructCall()) {
        // Invoked as constructor: `new __virConnect(...)`
        std::string uri = "qemu:///system";

        if(!args[0]->IsUndefined())
        {
            v8::String::Utf8Value a1(args[0]->ToString());
            uri = std::string(*a1);
        }
        __virConnect* obj = new __virConnect(uri);
        obj->Wrap(args.This());
        args.GetReturnValue().Set(args.This());
    }
    /*
    else {
        // Invoked as plain function `__virConnect(...)`, turn into construct call.
        const int argc = 1;
        Local<Value> argv[argc] = { args[0] };
        Local<Function> cons = Local<Function>::New(isolate, constructor);
        Local<Context> context = isolate->GetCurrentContext();
        Local<Object> instance = cons->NewInstance(context, argc, argv).ToLocalChecked();
        args.GetReturnValue().Set(instance);
    }
    */
}

void __virConnect::NewInstance(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();

    const unsigned argc = 1;
    Local<Value> argv[argc] = { args[0] };
    Local<Function> cons = Local<Function>::New(isolate, constructor);
    Local<Context> context = isolate->GetCurrentContext();
    Local<Object> instance = cons->NewInstance(context, argc, argv).ToLocalChecked();

    args.GetReturnValue().Set(instance);
}

void __virConnect::getURI(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();

    __virConnect* obj = ObjectWrap::Unwrap<__virConnect>(args.Holder());
    std::string a = virConnectGetURI(obj->_conn);
    args.GetReturnValue().Set(String::NewFromUtf8(isolate, a.c_str()));
}
