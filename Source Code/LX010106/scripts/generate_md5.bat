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

set MD5_PROJECT_NAME=%1%
rem MD5 script parameters
set MD5_INPUT_FILE=%MD5_PROJECT_NAME%.H86
set MD5_OUTPUT_FILE=..\\ConfigKeil\\%SUBDIR%\\Lst\\%MD5_PROJECT_NAME%.md5
set MD5_SCRIPT=md5sum.exe
set MD5_CRC_FILE=..\\ConfigKeil\\%SUBDIR%\\Lst\\%MD5_PROJECT_NAME%.H86
set MD5_SCRIPT_PATH=..\\..\\Scripts
set MD5_TEMP_FILE=temp.txt

echo ----------------------------------
echo Generating MD5 signature...

:calc_md5
rem MD5 script launch
cd %MD5_SCRIPT_PATH%
copy /Y %MD5_CRC_FILE% %MD5_INPUT_FILE% > %MD5_TEMP_FILE%
%MD5_SCRIPT% -b %MD5_INPUT_FILE% > %MD5_OUTPUT_FILE%
echo Génération de la signature MD5... OK
del /F %MD5_TEMP_FILE%
del /F %MD5_INPUT_FILE%
cd ..

:end

echo Generated MD5 signature: OK
