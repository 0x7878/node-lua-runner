#include <node.h>
#include <v8.h>
#include <nan.h>

#include "luastate.h"
#ifndef WIN32
# include <unistd.h>
#else
//TODO
#endif

extern "C" {
	#include <lua.h>
}

using namespace v8;

void init_info_constants(v8::Local<v8::Object> target){
v8::Isolate* isolate = v8::Isolate::GetCurrent();
  v8::Local<v8::Context> context = isolate->GetCurrentContext();
  Local<Object> constants = Nan::New<v8::Object>();
    constants->Set(context, Nan::New("VERSION").ToLocalChecked(),Nan::New(LUA_VERSION).ToLocalChecked());
    constants->Set(context, Nan::New("VERSION_NUM").ToLocalChecked(), Nan::New(LUA_VERSION_NUM));
    constants->Set(context, Nan::New("COPYRIGHT").ToLocalChecked(), Nan::New(LUA_COPYRIGHT).ToLocalChecked());
    constants->Set(context, Nan::New("AUTHORS").ToLocalChecked(), Nan::New(LUA_AUTHORS).ToLocalChecked());
    target->Set(context, Nan::New("INFO").ToLocalChecked(), constants);
}

void init_status_constants(Local<Object> target){
v8::Isolate* isolate = v8::Isolate::GetCurrent();
  v8::Local<v8::Context> context = isolate->GetCurrentContext();
    Local<Object> constants = Nan::New<v8::Object>();
    constants->Set(context, Nan::New("YIELD").ToLocalChecked(), Nan::New(LUA_YIELD));
    constants->Set(context, Nan::New("ERRRUN").ToLocalChecked(), Nan::New(LUA_ERRRUN));
    constants->Set(context, Nan::New("ERRSYNTAX").ToLocalChecked(), Nan::New(LUA_ERRSYNTAX));
    constants->Set(context, Nan::New("ERRMEM").ToLocalChecked(), Nan::New(LUA_ERRMEM));
    constants->Set(context, Nan::New("ERRERR").ToLocalChecked(), Nan::New(LUA_ERRERR));
    target->Set(context, Nan::New("STATUS").ToLocalChecked(), constants);
}

void init_gc_constants(Local<Object> target){
v8::Isolate* isolate = v8::Isolate::GetCurrent();
  v8::Local<v8::Context> context = isolate->GetCurrentContext();
    Local<Object> constants = Nan::New<v8::Object>();
    constants->Set(context, Nan::New("STOP").ToLocalChecked(), Nan::New(LUA_GCSTOP));
    constants->Set(context, Nan::New("RESTART").ToLocalChecked(), Nan::New(LUA_GCRESTART));
    constants->Set(context, Nan::New("COLLECT").ToLocalChecked(), Nan::New(LUA_GCCOLLECT));
    constants->Set(context, Nan::New("COUNT").ToLocalChecked(), Nan::New(LUA_GCCOUNT));
    constants->Set(context, Nan::New("COUNTB").ToLocalChecked(), Nan::New(LUA_GCCOUNTB));
    constants->Set(context, Nan::New("STEP").ToLocalChecked(), Nan::New(LUA_GCSTEP));
    constants->Set(context, Nan::New("SETPAUSE").ToLocalChecked(), Nan::New(LUA_GCSETPAUSE));
    constants->Set(context, Nan::New("SETSTEPMUL").ToLocalChecked(), Nan::New(LUA_GCSETSTEPMUL));
    target->Set(context, Nan::New("GC").ToLocalChecked(), constants);
}

void init_lua_constants(Local<Object> target){
v8::Isolate* isolate = v8::Isolate::GetCurrent();
  v8::Local<v8::Context> context = isolate->GetCurrentContext();
    Local<Object> constants = Nan::New<v8::Object>();
    constants->Set(context, Nan::New("GLOBALSINDEX").ToLocalChecked(), Nan::New(LUA_GLOBALSINDEX));
    target->Set(context, Nan::New("LUA").ToLocalChecked(), constants);
}

void init(v8::Local<v8::Object> exports, v8::Local<v8::Object> module) {

 	LuaState::Init(exports);
    init_gc_constants(exports);
    init_status_constants(exports);
    init_info_constants(exports);
	init_lua_constants(exports);
    // printf("node-lua loaded\n");
    fflush(stdout);
}
NODE_MODULE(nodelua, init)
