g++ -std=c++14 ../chip8.cpp validate_roms.cpp -O3 -o validate_roms
ls ../roms/ | ./validate_roms

