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
using v8::Local;
using v8::Object;
using v8::Isolate;

class __virConnect : public node::ObjectWrap
{
    public:
        virConnectPtr _conn;
        static void Init(Local<Object> exports);
        static void New(const v8::FunctionCallbackInfo<v8::Value>& args);

    private:
        explicit __virConnect(std::string uri);
        ~__virConnect();

        static void getURI(const v8::FunctionCallbackInfo<v8::Value>& args);
        static void lookupByID(const FunctionCallbackInfo<Value>& args);
        static v8::Persistent<v8::Function> constructor;
};

#endif
