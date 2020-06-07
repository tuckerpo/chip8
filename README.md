# Yet another Chip-8 interpreter

## Dependencies
Depends on SDL2.

### Linux
(or using equivalent package manager for your disto)
```
apt install SDL2-dev
```
### Windows
You can get SDL2 from https://www.libsdl.org/download-2.0.php

## Building
### Linux
```
./build.sh
```

### Windows
There are a few options for building this project on Windows.
If building using one of the provided .bat files, you'll need to `set SDL2DIR` to your SDL2 path.
From the Developer Command Prompt for VS, run:
```
git clone https://github.com/tuckerpo/chip8.git
cd chip8
call build86.bat // 32 bit build
call build64.bat // 64 bit build
```
You can alternatively build it using `CMake` from the VS Dev Prompt, specifiying a generator for the build system you'd like to use.

For example, building with CMake using MSVC with the Visual Studio 2019 toolchain installed and in your path:
```
cd chip8
mkdir build
pushd build
cmake -F "Visual Studio 16 2019"
cmake --build .\ --config Release --target ALL_BUILD -- /maxcpucount:8
popd
```
You'll need to copy the `SDL2.dll` shared library to the same directory as the `chip8.exe` binary.

### Roms
There are some Chip8 bytecode ROMs provided in the `roms` directory. I obtained these from https://www.zophar.net/pdroms/chip8.html

It is able to play all of the Chip-8 games provided in the `Chip-8 Games Pack` from the above link.

