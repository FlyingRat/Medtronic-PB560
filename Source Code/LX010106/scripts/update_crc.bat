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

rem CRC script parameters
set CRC_ADDRESS=0x000DFFFF
set CRC_FILE=..\\ConfigKeil\\%SUBDIR%\\Lst\\%1%.H86
set CRC_SCRIPT=updatecrc.exe
set CRC_SCRIPT_PATH=..\\..\\Scripts

echo ----------------------------------
echo Generating and integrating Checksum...

:update_crc
rem CRC script launch
cd %CRC_SCRIPT_PATH%
@echo ON
%CRC_SCRIPT% -a%CRC_ADDRESS% %CRC_FILE%
@echo OFF
cd ..

:end

echo Generating and integrating Checksum: OK