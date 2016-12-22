// __virDomain.cc
#include "virdomain.h"

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
    // Invoked as plain function `__virDomain(...)`, turn into construct call.
    if (args.IsConstructCall())
    {
        args.GetReturnValue().Set(args.This());
    }
}

void __virDomain::getID(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();

    __virDomain* obj = ObjectWrap::Unwrap<__virDomain>(args.Holder());
    unsigned int a = virDomainGetID(obj->_dom);
    args.GetReturnValue().Set(Number::New(isolate, a));
}

void __virDomain::wrap(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();

    Local<Function> cons = Local<Function>::New(isolate, constructor);
    Local<Context> context = isolate->GetCurrentContext();
    Local<Object> instance = cons->NewInstance(context).ToLocalChecked();

    this->Wrap(instance);
    args.GetReturnValue().Set(instance);
}
