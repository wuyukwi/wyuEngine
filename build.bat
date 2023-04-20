@echo off

cmake -B build -A x64
cmake --build build --config Debug

pause