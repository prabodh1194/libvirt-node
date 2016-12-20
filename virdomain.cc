// __virDomain.cc
#include <string>
#include "virdomain.h"

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

Persistent<Function> __virDomain::constructor;

__virDomain::__virDomain(virDomainPtr dom):
    _dom(dom)
{
}

__virDomain::~__virDomain()
{
}

void __virDomain::Init(Local<Object> exports)
{
    Isolate* isolate = exports->GetIsolate();

    // Prepare constructor template
    Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
    tpl->SetClassName(String::NewFromUtf8(isolate, "__virDomain"));
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    // Prototype
    NODE_SET_PROTOTYPE_METHOD(tpl, "ID", getID);

    constructor.Reset(isolate, tpl->GetFunction());
    exports->Set(String::NewFromUtf8(isolate, "__virDomain"), tpl->GetFunction());
}

void __virDomain::New(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();

    // Invoked as plain function `__virDomain(...)`, turn into construct call.
    if (args.IsConstructCall())
    {
        int domID = args[0]->NumberValue();
        __virConnect* obj = ObjectWrap::Unwrap<__virConnect>(args[1]->ToObject());
        virDomainPtr domain = virDomainLookupByID(obj->_conn, domID);
        __virDomain *dom = new __virDomain(domain);
        dom->Wrap(args.This());
        args.GetReturnValue().Set(args.This());
    }
    else
    {
        const int argc = 2;
        Local<Value> argv[argc] = {args[0], args.Holder()};
        Local<Function> cons = Local<Function>::New(isolate, constructor);
        Local<Context> context = isolate->GetCurrentContext();
        Local<Object> instance = cons->NewInstance(context, argc, argv).ToLocalChecked();
        args.GetReturnValue().Set(instance);
    }
}

void __virDomain::getID(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();

    __virDomain* obj = ObjectWrap::Unwrap<__virDomain>(args.Holder());
    unsigned int a = virDomainGetID(obj->_dom);
    args.GetReturnValue().Set(Number::New(isolate, a));
}
