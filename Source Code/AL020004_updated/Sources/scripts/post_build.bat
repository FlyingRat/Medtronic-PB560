@echo OFF

rem udpate crc
call ..\\scripts\\update_crc_al.bat %1%

rem generate md5 signature
call ..\\scripts\\generate_md5_al.bat %1%