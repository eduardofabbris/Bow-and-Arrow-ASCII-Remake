@echo off
title windows build
if not exist "src" goto end
echo Building project...
if not exist "objects" mkdir "objects"
for %%i in (src\*.c) do gcc %%i -o "objects\%%~ni.o" -Wall -Wextra -c
gcc -o main.exe "objects\*.o"
pause
exit
:end
echo Source folder not found!
pause
