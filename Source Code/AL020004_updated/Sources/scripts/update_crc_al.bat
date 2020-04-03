@echo OFF

:begin

rem CRC script parameters
set CRC_ADDRESS=0x0000FFFF
set CRC_FILE=..\\Config_MPLAB\\%1%.hex
set CRC_SCRIPT=updatecrcal.exe

:update_crc
rem CRC script launch
cd ..\\scripts\\
%CRC_SCRIPT% -a%CRC_ADDRESS% %CRC_FILE%
rem add a --gen-bad-crc option as shown here under to test the checksum check on startup.
rem %CRC_SCRIPT% -a%CRC_ADDRESS% %CRC_FILE% --gen-bad-crc
cd ..\\Config_MPLAB

:end