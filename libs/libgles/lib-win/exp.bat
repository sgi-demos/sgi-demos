@echo off
setlocal EnableDelayedExpansion

REM Copy these DLLs from your Chrome browser installation directory, if you want to update them
set DLLS=libEGL.dll libGLESv2.dll

REM Process each DLL
for %%D in (%DLLS%) do (
    echo Processing %%D...
    
    REM Get base name without extension for .def and .lib files
    set "BASENAME=%%~nD"
    
    REM Get the exports
    dumpbin /exports %%D > exports.txt
    
    REM Create the initial .def file
    echo LIBRARY !BASENAME! > !BASENAME!.def
    echo EXPORTS >> !BASENAME!.def
    
    REM Append the exports, skipping the header lines
    for /f "skip=19 tokens=4" %%A in (exports.txt) do echo %%A >> !BASENAME!.def
    
    REM Create the import library
    lib /def:!BASENAME!.def /out:!BASENAME!.lib /machine:x64
    
    REM Clean up temporary files
    del exports.txt
    echo Finished processing %%D
    echo.
)

echo All DLLs processed!
endlocal