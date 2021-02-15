#include <napi.h>
#include <Magick++.h>

using namespace std;
using namespace Magick;

class JpegWorker : public Napi::AsyncWorker {
  public:
  JpegWorker(Napi::Function& callback, string path)
      : Napi::AsyncWorker(callback), path(path) {}
  ~JpegWorker() {}

  void Execute() {
    Image image;
    image.read(path);
    image.quality(1);
    image.magick("JPEG");
    image.write(&blob);
  }

  void OnOK() {
    Callback().Call({Env().Undefined(), Napi::Buffer<char>::Copy(Env(), (char *)blob.data(), blob.length())});
  }

  private:
  string path;
  Blob blob;
};

Napi::Value Jpeg(const Napi::CallbackInfo& args) {
  Napi::Env env = args.Env();

  if (!args[0].IsString()) {
    Napi::TypeError::New(env, "This needs to be a string").ThrowAsJavaScriptException();
  }

  string path = args[0].As<Napi::String>().Utf8Value();
  Napi::Function callback = args[1].As<Napi::Function>();

  JpegWorker* jpegWorker = new JpegWorker(callback, path);
  jpegWorker->Queue();
  return env.Undefined();
};