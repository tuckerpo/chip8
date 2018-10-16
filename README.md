### Yet another CHIP8 interpreter.

Uses SDL2-2.0.8

Despite my efforts to make this an entirely platform independent implementation, the ROM validation test depends on C++17 ``` std::experimental::filesystem::v1 ``` which, despite the fact that this is October 2018, is still in the ``` <experimental/filesystem> ``` header for most compilers except for GCC v > 8. 

Additionally, the ```filesystem``` implementation is very buggy (read: not functional) on non-POSIX systems, namely Windows, as it lacks proper bindings to Windows system calls. So, until MinGW decides to start supporting modern compiler versions (still stuck with g++ 6.3...), and the STL developers stop letting Windows be an afterthought, Windows users will just have to trust me when I say all the included ROMs are functional and proper chip8 programs.