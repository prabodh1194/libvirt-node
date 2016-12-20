#ifndef VIRDOMAIN_H
#define VIRDOMAIN_H

#include <iostream>
#include <node.h>
#include <libvirt/libvirt.h>
#include <node_object_wrap.h>
#include <string>
#include "virconnect.h"

using v8::Local;
using v8::Object;
using v8::FunctionCallbackInfo;
using v8::Value;
using v8::Local;
using v8::Object;
using v8::Isolate;

class __virDomain : public node::ObjectWrap
{
    public:
        virDomainPtr _dom;
        static void Init(Local<Object> exports);
        static void New(const v8::FunctionCallbackInfo<v8::Value>& args);

    private:
        explicit __virDomain(virDomainPtr dom);
        ~__virDomain();

        static void getID(const v8::FunctionCallbackInfo<v8::Value>& args);
        static v8::Persistent<v8::Function> constructor;
};

#endif
