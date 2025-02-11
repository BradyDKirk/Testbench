@echo off

set ProjectDir=%~dp0

:: Options
set BaseName=workbench
set Source=main.c

set Definess=
set IncDirs=
set LibDirs=
set Libs=

:: Setup Flags
set CommonFlags=/nologo /std:c11 /Oi /FC /EHa- /WX /W4 /wd4100 /wd4189

:: Release Flags
set CompilerFlags=/O2 /MT
:: Debug Flags
::set CompilerFlags=/Od /MTd /Z7

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
cl %CompilerSettings% %ProjectDir%\src\%Source% /link %LinkerSettings%

popd
