cl.exe /EHsc /I ..\include /I %SDL2DIR%\include chip8.cpp chip8factory.cpp main.cpp /link /LIBPATH:%SDL2DIR%\lib\x86 SDL2main.lib SDL2.lib /SUBSYSTEM:CONSOLE
copy %SDL2DIR%\lib\x86\SDL2.dll .
