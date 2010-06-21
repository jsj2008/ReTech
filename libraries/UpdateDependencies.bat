@echo off
call "%VS90COMNTOOLS%vsvars32.bat"

echo Update libraries...
echo Update POCO...
svn update code\POCO
echo Update boost...
svn update code\boost
echo Update box2d...
svn update code\box2d
echo Update SFML...
svn update code\sfml

echo Build libraries...
echo Build SFML debug...
devenv code\sfml\build\vc2008\SFML.sln /build "Debug static" /project sfml-main
devenv code\sfml\build\vc2008\SFML.sln /build "Debug static" /project sfml-system
devenv code\sfml\build\vc2008\SFML.sln /build "Debug static" /project sfml-window
devenv code\sfml\build\vc2008\SFML.sln /build "Debug static" /project sfml-network
devenv code\sfml\build\vc2008\SFML.sln /build "Debug static" /project sfml-graphics
devenv code\sfml\build\vc2008\SFML.sln /build "Debug static" /project sfml-audio
echo Build SFML release...
devenv code\sfml\build\vc2008\SFML.sln /build "Release static" /project sfml-main
devenv code\sfml\build\vc2008\SFML.sln /build "Release static" /project sfml-system
devenv code\sfml\build\vc2008\SFML.sln /build "Release static" /project sfml-window
devenv code\sfml\build\vc2008\SFML.sln /build "Release static" /project sfml-network
devenv code\sfml\build\vc2008\SFML.sln /build "Release static" /project sfml-graphics
devenv code\sfml\build\vc2008\SFML.sln /build "Release static" /project sfml-audio

echo Build POCO debug...
devenv code\POCO\Foundation\Foundation_vs90.sln /build "debug_static" /project Foundation
devenv code\POCO\XML\XML_vs90.sln /build "debug_static" /project XML
devenv code\POCO\Util\Util_vs90.sln /build "debug_static" /project Util
rem devenv code\POCO\Zip\Zip_vs90.sln /build "debug_shared" /project Zip
devenv code\POCO\Net\Net_vs90.sln /build "debug_static" /project Net
echo Build POCO release...
devenv code\POCO\Foundation\Foundation_vs90.sln /build "release_static" /project Foundation
devenv code\POCO\XML\XML_vs90.sln /build "release_static" /project XML
devenv code\POCO\Util\Util_vs90.sln /build "release_static" /project Util
rem devenv code\POCO\Zip\Zip_vs90.sln /build "release_shared" /project Zip
devenv code\POCO\Net\Net_vs90.sln /build "release_static" /project Net

echo Build AngelScript debug...
devenv code\AngelScript\sdk\angelscript\projects\msvc9\angelscript.sln /build "Debug"

echo Build AngelScript release...
devenv code\AngelScript\sdk\angelscript\projects\msvc9\angelscript.sln /build "Release"

rem echo Build boost
rem cd ./code/boost
rem "../../bjam" --toolset=msvc-9.0 --build-type=minimal --with-serialization
rem cd ..
rem cd ..

echo Remove old files...
rd /q /s ..\dependencies
md ..\dependencies
md ..\dependencies\lib
md ..\dependencies\include
rem del ..\bin\*.dll /q

echo Copy includes...
md ..\dependencies\include\POCO
xcopy code\POCO\Foundation\include\POCO\* ..\dependencies\include\POCO\ /s /q
xcopy code\POCO\XML\include\POCO\* ..\dependencies\include\POCO\ /s /q
xcopy code\POCO\Util\include\POCO\* ..\dependencies\include\POCO\ /s /q
rem xcopy code\POCO\Zip\include\POCO\* ..\dependencies\include\POCO\ /s /q
xcopy code\POCO\Net\include\POCO\* ..\dependencies\include\POCO\ /s /q
md ..\dependencies\include\boost
xcopy code\boost\boost\* ..\dependencies\include\boost\ /s /q
md ..\dependencies\include\sfml
xcopy code\sfml\include\sfml\* ..\dependencies\include\sfml\ /s /q
md ..\dependencies\include\angelscript
xcopy code\AngelScript\sdk\angelscript\include\* ..\dependencies\include\angelscript\ /s /q

echo Copy libraries...
xcopy code\sfml\lib\vc2008\*.lib ..\dependencies\lib /q
xcopy code\POCO\lib\*.lib ..\dependencies\lib /q
xcopy code\AngelScript\sdk\angelscript\lib\*.lib ..\dependencies\lib /q
rem xcopy code\boost\stage\lib\*.lib ..\dependencies\lib /q

echo Copy binaries...
rem xcopy code\POCO\bin\*.dll ..\bin /q

echo Done

pause

