@echo OFF

:begin
echo ----------------------------------
echo Updating revision...
SubWCRev.exe ../.. "../../SRC/DATABASE/DB_Revision.in" "../../SRC/DATABASE/DB_Revision.h"
echo Updated revision: OK