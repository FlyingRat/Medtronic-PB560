@echo OFF

:begin

set MD5_PROJECT_NAME=%1%
rem MD5 script parameters
set MD5_INPUT_FILE=%MD5_PROJECT_NAME%.hex
set MD5_OUTPUT_FILE=..\\Config_MPLAB\\%MD5_PROJECT_NAME%.md5
set MD5_SCRIPT=md5sum.exe
set MD5_CRC_FILE=..\\Config_MPLAB\\%MD5_PROJECT_NAME%.hex
set MD5_TEMP_FILE=temp.txt

:calc_md5
rem MD5 script launch
cd ..\\scripts\\
copy /Y %MD5_CRC_FILE% %MD5_INPUT_FILE% > %MD5_TEMP_FILE%
%MD5_SCRIPT% -b %MD5_INPUT_FILE% > %MD5_OUTPUT_FILE%
echo Génération de la signature MD5... OK
del /F %MD5_TEMP_FILE%
del /F %MD5_INPUT_FILE%
cd ..\\Config_MPLAB

:end