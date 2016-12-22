#ifndef VIRCONNECT_H
#define VIRCONNECT_H

#include <iostream>
#include <node.h>
#include <libvirt/libvirt.h>
#include <node_object_wrap.h>
#include <string>
#include "virdomain.h"

using v8::Local;
using v8::Object;
using v8::FunctionCallbackInfo;
using v8::Value;
using v8::Isolate;
using v8::Context;
using v8::Function;
using v8::FunctionTemplate;
using v8::Number;
using v8::Persistent;
using v8::String;

class __virConnect : public node::ObjectWrap
{
    public:
        virConnectPtr _conn;
        static Persistent<Function> constructor;

        explicit __virConnect(std::string uri);
        static void Init(Local<Object> exports);
        static void New(const FunctionCallbackInfo<Value>& args);
        void wrap(const FunctionCallbackInfo<Value>& args);

    private:
        ~__virConnect();

        static void getURI(const FunctionCallbackInfo<Value>& args);
        static void lookupByID(const FunctionCallbackInfo<Value>& args);
};

#endif
