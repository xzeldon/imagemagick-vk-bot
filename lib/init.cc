#include "./jpeg/jpeg.h"
#include "./liquid/liquid.h"

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
  exports.Set(Napi::String::New(env, "jpeg"), Napi::Function::New(env, Jpeg));
  exports.Set(Napi::String::New(env, "liquid"), Napi::Function::New(env, Liquid));
  return exports;
}

NODE_API_MODULE(addon, Init);