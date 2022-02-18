@echo off
for %%f in (src\*.c) do (
    if "%%~xf"==".c" CALL :makeofile %%~nf
)
SET "command=gcc"
for %%f in (bin\*.o) do (
    if "%%~xf"==".o" CALL :makeCommand %%~nf
)
SET "command=%command% -g -Wall -lm -fPIC -o bin/klin.exe"
%command%
ECHO %command%
EXIT /B %ERRORLEVEL%

:makeCommand
SET command=%command% bin/%~1.o
EXIT /b 0

:makeofile
gcc -c -g -Wall -lm -fPIC "src/"%~1".c" -o "bin/"%~1".o"
ECHO gcc -c -g -Wall -lm -fPIC src/%~1.c -o bin/%~1.o
EXIT /b 0
