cl.exe /EHsc /I ..\include /I %SDL2DIR%\include chip8.cpp main.cpp /std:c++latest /link /LIBPATH:%SDL2DIR%\lib\x64 SDL2main.lib SDL2.lib /SUBSYSTEM:CONSOLE
copy %SDL2DIR%\lib\x64\SDL2.dll .
