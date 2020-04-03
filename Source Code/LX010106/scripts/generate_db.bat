@echo OFF

:begin
if "%1" equ ""RA0104"" set SUBDIR=US-PB540
if "%1" equ "RA0104" set SUBDIR=US-PB540
if "%1" equ ""RB0505"" set SUBDIR=XL2-PB560
if "%1" equ "RB0505" set SUBDIR=XL2-PB560
if "%1" equ ""RC0306"" set SUBDIR=M2-PB640
if "%1" equ "RC0306" set SUBDIR=M2-PB640
if "%1" equ ""RC1205"" set SUBDIR=S2-PB520
if "%1" equ "RC1205" set SUBDIR=S2-PB520

set DB_INPUT_PATH=..\\
set DB_OUTPUT_PATH=..\\ConfigKeil\\%SUBDIR%\\Lst
set DB_SCRIPT_PATH=..\\..\\Scripts
set DB_SCRIPT=dbtoini.exe

echo ----------------------------------
echo Generating Database (.ini file)...

cd %DB_SCRIPT_PATH%
%DB_SCRIPT% %DB_INPUT_PATH% %DB_OUTPUT_PATH%

del %DB_OUTPUT_PATH%\\%1%.ini
ren %DB_OUTPUT_PATH%\\database_XL2.txt %1%.ini 

:end

echo Generated Database: OK