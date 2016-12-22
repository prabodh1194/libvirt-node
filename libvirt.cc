#include <node.h>
#include "virconnect.h"
#include "virdomain.h"

void __virConnectOpen(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();

    std::string uri = "qemu:///system";

    if(!args[0]->IsUndefined())
    {
        v8::String::Utf8Value a1(args[0]->ToString());
        uri = std::string(*a1);
    }
    __virConnect* conn = new __virConnect(uri);
    conn->wrap(args);
}

void InitAll(Local<Object> exports)
{
    Isolate* isolate = exports->GetIsolate();
    Local<v8::Context> context = isolate->GetCurrentContext();

    //set enum
    exports->DefineOwnProperty(context, v8::String::NewFromUtf8(isolate,"ENUM"), v8::Number::New(isolate,1), v8::ReadOnly);

    //set libvirt calls
    NODE_SET_METHOD(exports,"open",__virConnectOpen);

    //set classes
    __virConnect::Init(exports);
    __virDomain::Init(exports);
}

NODE_MODULE(libvirt, InitAll)
