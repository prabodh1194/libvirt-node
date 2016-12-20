#include <node.h>
#include "virconnect.h"

void __virConnectOpen(const FunctionCallbackInfo<Value>& args)
{
    std::string uri = "qemu:///system";

    if(!args[0]->IsUndefined())
    {
        v8::String::Utf8Value a1(args[0]->ToString());
        uri = std::string(*a1);
    }
    __virConnect *conn = new __virConnect(uri);
    conn->New(args);
}

void InitAll(Local<Object> exports)
{
    NODE_SET_METHOD(exports,"open",__virConnectOpen);
    __virConnect::Init(exports);
}

NODE_MODULE(libvirt, InitAll)
