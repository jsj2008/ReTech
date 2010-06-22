@echo off
call "%VS90COMNTOOLS%vsvars32.bat"

echo Update libraries...
echo Update POCO...
svn update code\POCO
echo Update box2d...
svn update code\box2d
echo Update SFML...
svn update code\sfml
echo Update YAML Cpp...
svn update code\yaml-cpp

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
devenv code\POCO\Net\Net_vs90.sln /build "debug_static" /project Net
echo Build POCO release...
devenv code\POCO\Foundation\Foundation_vs90.sln /build "release_static" /project Foundation
devenv code\POCO\XML\XML_vs90.sln /build "release_static" /project XML
devenv code\POCO\Util\Util_vs90.sln /build "release_static" /project Util
devenv code\POCO\Net\Net_vs90.sln /build "release_static" /project Net

echo Build AngelScript debug...
devenv code\AngelScript\sdk\angelscript\projects\msvc9\angelscript.sln /build "Debug"

echo Build AngelScript release...
devenv code\AngelScript\sdk\angelscript\projects\msvc9\angelscript.sln /build "Release"

echo Build YAML Cpp debug...
devenv code\yaml-cpp\yamlcpp.sln /build "Debug" /project yamlcpp

echo Build YAML Cpp release...
devenv code\yaml-cpp\yamlcpp.sln /build "Release" /project yamlcpp

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
md ..\dependencies\include\fastdelegates
xcopy external\fastdelegates\* ..\dependencies\include\fastdelegates\ /s /q
md ..\dependencies\include\sfml
xcopy code\sfml\include\sfml\* ..\dependencies\include\sfml\ /s /q
md ..\dependencies\include\angelscript
xcopy code\AngelScript\sdk\angelscript\include\* ..\dependencies\include\angelscript\ /s /q
md ..\dependencies\include\yaml-cpp
xcopy code\yaml-cpp\include\* ..\dependencies\include\yaml-cpp\ /s /q

echo Copy libraries...
xcopy code\sfml\lib\vc2008\*.lib ..\dependencies\lib /q
xcopy code\POCO\lib\*.lib ..\dependencies\lib /q
xcopy code\AngelScript\sdk\angelscript\lib\*.lib ..\dependencies\lib /q
xcopy code\yaml-cpp\lib\*.lib ..\dependencies\lib /q

echo Copy binaries...
rem xcopy code\POCO\bin\*.dll ..\bin /q

echo Done

pause

