@echo off
rem convert .asm (Microsoft assembler) to .lg 
if not exist %1.asm goto Complain

lgrind -i -lmasm %1.asm > %1.lg
echo Created %1.lg
goto Done

:Complain
echo '%1.asm' does not exist.

:Done


