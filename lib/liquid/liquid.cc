#include <napi.h>
#include <list>
#include <Magick++.h>

using namespace std;
using namespace Magick;

class LiquidWorker : public Napi::AsyncWorker {
 public:
  LiquidWorker(Napi::Function& callback, string path, string type, int delay)
      : Napi::AsyncWorker(callback), path(path), type(type), delay(delay) {}
  ~LiquidWorker() {}

  void Execute() {
    list <Image> frames;
    list <Image> coalesced;
    list <Image> blurred;
    list <Image> result;
    readImages(&frames, path);
    coalesceImages(&coalesced, frames.begin(), frames.end());

    for (Image &image : coalesced) {
      int imageWeight = image.baseColumns();
      int imageHeight = image.baseRows();
      image.strip();
      image.resize(Geometry(to_string(imageWeight / 2) + "x" + to_string(imageHeight / 2)));
      image.liquidRescale(Geometry("400!x400!"));
      image.liquidRescale(Geometry("200x1200"));
      image.resize(Geometry(to_string(imageWeight) + "x" + to_string(imageHeight)));
      image.magick(type);
      blurred.push_back(image);
    }

    optimizeImageLayers(&result, blurred.begin(), blurred.end());
    if (delay != 0) for_each(result.begin(), result.end(), animationDelayImage(delay));
    writeImages(result.begin(), result.end(), &blob);
  }

  void OnOK() {
    Callback().Call({Env().Undefined(), Napi::Buffer<char>::Copy(Env(), (char *)blob.data(), blob.length())});
  }

 private:
  string path, type;
  int delay;
  Blob blob;
};

Napi::Value Liquid(const Napi::CallbackInfo &args)
{
  Napi::Env env = args.Env();

  if (!args[0].IsString()) {
    Napi::TypeError::New(env, "The first argument must be a string").ThrowAsJavaScriptException();
  }

  if (!args[1].IsString()) {
    Napi::TypeError::New(env, "The second argument must be a string").ThrowAsJavaScriptException();
  }

  if (!args[2].IsNumber()) {
    Napi::TypeError::New(env, "The third argument must be a number").ThrowAsJavaScriptException();
  }

  string path = args[0].As<Napi::String>().Utf8Value();
  string type = args[1].As<Napi::String>().Utf8Value();
  int delay = args[2].As<Napi::Number>().Int32Value();
  Napi::Function callback = args[3].As<Napi::Function>();


  LiquidWorker* liquidWorker = new LiquidWorker(callback, path, type, delay);
  liquidWorker->Queue();
  return env.Undefined();
}