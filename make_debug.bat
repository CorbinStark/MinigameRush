@echo off

mkdir build
pushd build
cls
cl /Zi /EHsc -I..\include ..\*.cpp ..\*.c ..\libs\*.lib msvcrt.lib shell32.lib user32.lib gdi32.lib opengl32.lib
popd
