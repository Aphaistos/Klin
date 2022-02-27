@echo off
as program.s -o bin/program.o
ld bin/program.o -o bin/program.exe