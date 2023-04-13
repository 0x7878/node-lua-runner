#include <stdlib.h>
#include "utils.h"
#include <nan.h>

char* get_str(v8::Local<v8::Value> val) {
  if (!val->IsString()) {
    Nan::ThrowError("Argument Must Be A String");
    return NULL;
  }

  v8::Isolate* isolate = v8::Isolate::GetCurrent();
  v8::Local<v8::Context> context = isolate->GetCurrentContext();
  v8::Local<v8::String> val_string = val->ToString(context).ToLocalChecked();
  v8::String::Utf8Value val_utf8(isolate, val_string);
  char* val_char_ptr = (char*)malloc(val_utf8.length() + 1);
  strcpy(val_char_ptr, *val_utf8);
  return val_char_ptr;
}




v8::Local<v8::Value> lua_to_value(lua_State* L, int i){
 switch(lua_type(L, i)){
 case LUA_TBOOLEAN:
	 return Nan::New((int)lua_toboolean(L, i));
   break;
 case LUA_TNUMBER:
	 return Nan::New(lua_tonumber(L, i));
   break;
 case LUA_TSTRING:
	 return Nan::New((char *)lua_tostring(L, i)).ToLocalChecked();
   break;
 case LUA_TTABLE:
   {
     v8::Local<v8::Object> obj = Nan::New<v8::Object>();
     lua_pushnil(L);
     while(lua_next(L, -2) != 0){
	v8::Local<v8::Value> key = lua_to_value(L, -2);
	v8::Local<v8::Value> value = lua_to_value(L, -1);
Nan::Set(obj, key, value);
	lua_pop(L, 1);
     }
     return obj;
     break;
   }
 default:
	 return Nan::Undefined();
   break;
 }
}

void push_value_to_lua(lua_State* L, v8::Local<v8::Value> value){
  v8::Isolate* isolate = v8::Isolate::GetCurrent(); 
 v8::Local<v8::Context> context = isolate->GetCurrentContext();
	if (value->IsString()){  v8::Local<v8::String> str = value->ToString(context).ToLocalChecked();
lua_pushstring(L, get_str(str));
 }else if(value->IsNumber()){
   int i_value = Nan::To<int32_t>(value).FromMaybe(0);
   lua_pushinteger(L, i_value);
 }else if(value->IsBoolean()){
   int b_value = (int)value->ToBoolean(isolate)->Value();
   lua_pushboolean(L, b_value);
 }else if(value->IsObject()){
   lua_newtable(L);
   v8::Local<v8::Object> obj = value->ToObject(context).ToLocalChecked();

  v8::Local<v8::Array> keys = obj->GetPropertyNames(context).ToLocalChecked();

   for(uint32_t i = 0; i < keys->Length(); ++i){
     v8::Local<v8::Value> key = keys->Get(context, i).ToLocalChecked();

     v8::Local<v8::Value> val = obj->Get(context, key).ToLocalChecked();
     push_value_to_lua(L, key);
     push_value_to_lua(L, val);
     lua_settable(L, -3);
   }
 }else{
   lua_pushnil(L);
 }
}
