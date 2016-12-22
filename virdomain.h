#ifndef VIRDOMAIN_H
#define VIRDOMAIN_H

#include <iostream>
#include <node.h>
#include <libvirt/libvirt.h>
#include <node_object_wrap.h>
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

class __virDomain : public node::ObjectWrap
{
    public:
        virDomainPtr _dom;
        static Persistent<Function> constructor;

        explicit __virDomain(virDomainPtr dom);
        static void Init(Local<Object> exports);
        static void New(const FunctionCallbackInfo<Value>& args);
        void wrap(const FunctionCallbackInfo<Value>& args);

    private:
        ~__virDomain();

        static void getID(const FunctionCallbackInfo<Value>& args);
};

#endif
