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
