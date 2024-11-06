# ToneGen
ToneGen is a simple sine wave tone generator written in C, using the PortAudio library for audio output. The program allows users to specify the frequency and duration of the sine wave, and outputs the generated tone to the default audio device.

## Features
- Generate sine wave tones at a specified frequency (in Hz)
- Set the duration of the tone (in milliseconds)
- Simple command-line interface
- Uses PortAudio for audio output

## Building/Running Prerequisites
To build and run ToneGen, you will need:
- A C compiler (e.g., `gcc`)
- PortAudio Installed (view "Install PortAudio heading")

### Installing PortAudio
#### Windows
The simplest way to install PortAudio on Windows is through the MinGW64 packaging system (pacman). The currently library and header file includes rely on this method. To download the necessary PortAudio files, run the following command:
```bash
pacman -S mingw-w64-x86_64-portaudio
```
For all other ways of download, refer to https://www.portaudio.com/

#### Linux (Ubuntu/Debian)
The Linux PortAudio download is much simpler. Just run the following command:
```bash
sudo apt install portaudio19-dev
```

## Building the Project
First ensure that PortAudio is installed and configured correctly. If so, run the following commands:
```bash
git clone https://github.com/rullo24/ToneGen.git
cd ToneGen
make
```

## Licence
PortAudio Portable Real-Time Audio Library
Copyright (c) 1999-2011 Ross Bencina and Phil Burk

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
