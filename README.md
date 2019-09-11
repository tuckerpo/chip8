### Yet another CHIP8 interpreter.

Uses SDL2-2.0.8

# Building on Linux (working on Ubuntu 18.04 & Debian 10)
```
cd ~/
git clone https://github.com/tuckerpo/chip8.git
cd chip8
./build.sh
```

# Building on Windows (working on Windows 10 cl.exe version 19.22.27905)
From the Developer Command Prompt for VS, run:
```
git clone https://github.com/tuckerpo/chip8.git
cd chip8
call build86.bat // 32 bit build
call build64.bat // 64 bit build
```
You'll need to `set SDL2DIR` to your SDL2 path.

