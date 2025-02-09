@echo off

:: Options
set BaseName=testbench
set Source=main.c

set Definess=
set IncDirs=
set LibDirs=
set Libs=

:: Setup Flags
set CommonFlags=/nologo /std:c11 /Oi /FC /EHsc /WX /W4 /wd4100 /wd4189
:: /wd4505 /wd4201 /wd4127 /wd4456

:: Release Flags
::set CompilerFlags=/O2 /MT
:: Debug Flags
set CompilerFlags=/Od /MTd /Z7

:: Enable ASan
::set CompilerFlags=%CompilerFlags% /fsanitize=address

set LinkerFlags=/INCREMENTAL:NO /OPT:REF 

set OutFiles=/Fe%BaseName%.exe /Fo%BaseName%.obj

:: Create Settings
set CompilerSettings=%CommonFlags% %CompilerFlags% %IncDirs% %Defines% %OutFiles%
set LinkerSettings=%LinkerFlags% %LibDirs% %Libs%

:: Setup Directories
if not exist build mkdir build

:: Build
pushd build

del *.pdb > NUL 2> NUL
cl %CompilerSettings% ..\src\%Source% /link %LinkerSettings%

popd