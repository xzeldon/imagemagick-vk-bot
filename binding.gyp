{
  "targets": [
    {
      "target_name": "image",
      "sources": [ "<!@(node -p \"var fs=require('fs'),path=require('path'),walk=function(r){let t,e=[],n=null;try{t=fs.readdirSync(r)}catch(r){n=r.toString()}if(n)return n;var a=0;return function n(){var i=t[a++];if(!i)return e;let u=path.resolve(r,i);i=r+'/'+i;let c=fs.statSync(u);if(c&&c.isDirectory()){let r=walk(i);return e=e.concat(r),n()}return e.push(i),n()}()};walk('./lib').join(' ');\")" ],
      "cflags!": [ "-fno-exceptions", "<!(pkg-config --cflags Magick++)" ],
      "cflags_cc!": [ "-fno-exceptions", "<!(pkg-config --cflags Magick++)" ],
      "include_dirs": [
        "<!@(node -p \"require('node-addon-api').include\")",
        "<!@(pkg-config --cflags-only-I Magick++ | sed 's/^.\{2\}//')"
      ],
      "libraries": [
        "<!(pkg-config --libs Magick++)",
      ],
      "defines": ["NAPI_DISABLE_CPP_EXCEPTIONS", "MAGICKCORE_HDRI_ENABLE=false", "MAGICKCORE_QUANTUM_DEPTH=8"]
    }
  ]
}