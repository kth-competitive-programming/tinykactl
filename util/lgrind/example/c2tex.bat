@echo off
rem convert .c to .lg 
if not exist %1.c goto Complain

lgrind -i -v subst %1.c > %1.lg
echo Created %1.lg
goto Done

:Complain
echo '%1.c' does not exist.

:Done


