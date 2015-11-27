@echo off
IF (%1)==() echo.Usage !!!ERROR!!! %0 {Base Directory} Use capital letter for drive letter.

echo Setting up build environment with default configuration ...

rem *** PROJECT_DIR is used as the project top-level directory. ***
rem ***  The path to specify the location of project.mk ***

set PROJECT_DIR=%cd%
echo Set PROJECT_DIR to %PROJECT_DIR%

rem *** Set CFG_DIR ***

set CFG_DIR=%cd%
echo Set CFG_DIR to %CFG_DIR%

rem *** Setup the default environment ***

if not exist ($?DEFAULT_SETUP_PATH) set DEFAULT_SETUP_PATH=../default
call %DEFAULT_SETUP_PATH%/setup.bat %1

rem *** Append output path of DLLs in PATH ***
set PATH=%BUILD_ROOT%\installed_lib\win32;%PATH%
