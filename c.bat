@echo off
set arg=./c/%1/%1.c

gcc -Wall -o c/%1/%1 %arg%

start /d "c/%1" %1.exe


