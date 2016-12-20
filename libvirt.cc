#include <node.h>
#include "virconnect.h"
#include "virdomain.h"

void __virConnectOpen(const FunctionCallbackInfo<Value>& args)
{
    __virConnect::New(args);
}

void InitAll(Local<Object> exports)
{
    NODE_SET_METHOD(exports,"open",__virConnectOpen);
    __virConnect::Init(exports);
    __virDomain::Init(exports);
}

NODE_MODULE(libvirt, InitAll)
