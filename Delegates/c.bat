@ECHO off
del Delegates.exp >nul
del Delegates.obj >nul
del Delegates.dll >nul
del Delegates.lib >nul
..\..\masm32\bin\ml /c /coff Delegates.asm
..\..\masm32\bin\Link /SUBSYSTEM:WINDOWS /DLL /DEF:Delegates.def Delegates.obj /NOENTRY
del Delegates.obj > nul
rem copy Delegates.dll ..\raw\ > nul
rem copy Delegates.dll ..\release\ > nul
echo -                                                                             -
echo -------------------------------------------------------------------------------
echo ------------------------------------- OK --------------------------------------
echo -------------------------------------------------------------------------------
pause