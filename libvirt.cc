#include <node.h>
#include "virconnect.h"

void InitAll(Local<Object> exports) {
    __virConnect::Init(exports);
}

NODE_MODULE(libvirt_addon, InitAll)
