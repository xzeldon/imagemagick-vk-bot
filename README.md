# ImageBot
The simplest NodeJS bot that processes images sent to it using [ImageMagick 7](http://imagemagick.org/). Uses the [Magick++ API](https://imagemagick.org/script/magick++.php) and [node-addon-api](https://github.com/nodejs/node-addon-api).

For example, two commands are currently implemented:
* jpeg — strongly compresses the image.
* liquid — distorts the image using the Seam Carving algorithm.

## Setup
**Windows is now supported platform! Use [WSL](https://en.wikipedia.org/wiki/Windows_Subsystem_for_Linux) if you want to run the bot on Windows!**

First of all, preferably you should [install ImageMagick from source](https://imagemagick.org/script/install-source.php#linux).

You must also have the developer tools installed to compile C/C++ like GCC (if you use debian/ubuntu just type ``` apt install build-essential``` in terminal).

Then just clone this repository. Type ```npm i``` and all the dependencies will install.

Once you do that, you're almost up and running. Type ``` npm run build ```. This will build the bot and put the output files in the dist folder.

Finally, just go into the dist folder, and type ```npm start```.

