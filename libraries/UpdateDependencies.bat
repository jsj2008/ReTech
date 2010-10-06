@echo off
call "%VS90COMNTOOLS%vsvars32.bat"

echo Update libraries...
echo Update boost...
svn update code\boost
echo Update box2d...
svn update code\box2d
echo Update SFML...
svn update code\sfml
echo Update YAML Cpp...
svn update code\yaml-cpp
echo Update SPARK...
svn update code\spark
cd code\camp
echo Update Camp...
call git pull
cd ..\..
cd code\sfgui
echo Update SfGui...
call git pull
cd ..\..

echo Build libraries...
cd code\boost
set BOOST_ROOT=%CD%
cd ..\..
cd code\camp
cmake -G "Visual Studio 9 2008"
cd ..\..
echo Build Camp debug...
devenv code\camp\camp.sln /build "Debug" /project camp
echo Build Camp release...
devenv code\camp\camp.sln /build "Release" /project camp 

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

echo Copy SfGui to SFML folder...
xcopy code\sfgui\* code\sfml\ /s /q
copy code\sfml\lib\vc2008\sfml2-audio-s-d.lib code\sfml\lib\vc2008\sfml2-audio-d.lib /s /q
copy code\sfml\lib\vc2008\sfml2-audio-s.lib code\sfml\lib\vc2008\sfml2-audio.lib /s /q
copy code\sfml\lib\vc2008\sfml2-graphics-s-d.lib code\sfml\lib\vc2008\sfml2-graphics-d.lib /s /q
copy code\sfml\lib\vc2008\sfml2-graphics-s.lib code\sfml\lib\vc2008\sfml2-graphics.lib /s /q
copy code\sfml\lib\vc2008\sfml2-system-s-d.lib code\sfml\lib\vc2008\sfml2-system-d.lib /s /q
copy code\sfml\lib\vc2008\sfml2-system-s.lib code\sfml\lib\vc2008\sfml2-system.lib /s /q
copy code\sfml\lib\vc2008\sfml2-window-s-d.lib code\sfml\lib\vc2008\sfml2-window-d.lib /s /q
copy code\sfml\lib\vc2008\sfml2-window-s.lib code\sfml\lib\vc2008\sfml2-window.lib /s /q

echo Build SfGui debug...
devenv code\sfml\build\vc2008\sfgui\sfgui.sln /build "Debug" /project sfgui
echo Build SfGui release...
devenv code\sfml\build\vc2008\sfgui\sfgui.sln /build "Release" /project sfgui

rm code\sfml\lib\vc2008\sfml2-window.lib
rm code\sfml\lib\vc2008\sfml2-window-d.lib
rm code\sfml\lib\vc2008\sfml2-system.lib
rm code\sfml\lib\vc2008\sfml2-system-d.lib
rm code\sfml\lib\vc2008\sfml2-graphics.lib
rm code\sfml\lib\vc2008\sfml2-graphics-d.lib
rm code\sfml\lib\vc2008\sfml2-audio.lib
rm code\sfml\lib\vc2008\sfml2-audio-d.lib

echo Copy SFML to SPARK folder...
xcopy code\sfml\include\sfml\* code\spark\trunk\include\sfml\ /s /q
echo Build SPARK debug...
devenv code\spark\trunk\projects\vc2008\SPARK_engine.sln /build "Debug" /project "SPARK Engine CORE LIB"
devenv code\spark\trunk\projects\vc2008\SPARK_engine.sln /build "Debug" /project "SPARK Engine GL LIB"
devenv code\spark\trunk\projects\vc2008\SPARK_engine.sln /build "Debug" /project "SPARK Engine SFML LIB"
echo Build SPARK release...
devenv code\spark\trunk\projects\vc2008\SPARK_engine.sln /build "Release" /project "SPARK Engine CORE LIB"
devenv code\spark\trunk\projects\vc2008\SPARK_engine.sln /build "Release" /project "SPARK Engine GL LIB"
devenv code\spark\trunk\projects\vc2008\SPARK_engine.sln /build "Release" /project "SPARK Engine SFML LIB"

echo Build YAML Cpp debug...
devenv code\yaml-cpp\yamlcpp.sln /build "Debug" /project yamlcpp
echo Build YAML Cpp release...
devenv code\yaml-cpp\yamlcpp.sln /build "Release" /project yamlcpp

echo Build Box2D debug...
devenv code\box2d\Build\VC8\Box2D.sln /build "Debug" /project Box2D
echo Build Box2D release...
devenv code\box2d\Build\VC8\Box2D.sln /build "Release" /project Box2D

echo Remove old files...
rd /q /s ..\dependencies
md ..\dependencies
md ..\dependencies\lib
md ..\dependencies\include
rem del ..\bin\*.dll /q

echo Copy includes...
md ..\dependencies\include\boost
xcopy code\boost\boost\* ..\dependencies\include\boost\ /s /q
md ..\dependencies\include\fastdelegates
xcopy external\fastdelegates\* ..\dependencies\include\fastdelegates\ /s /q
md ..\dependencies\include\sfml
xcopy code\sfml\include\sfml\* ..\dependencies\include\sfml\ /s /q
md ..\dependencies\include\sfgui
xcopy code\sfgui\include\sfgui\* ..\dependencies\include\sfgui\ /s /q
md ..\dependencies\include\yaml-cpp
xcopy code\yaml-cpp\include\* ..\dependencies\include\yaml-cpp\ /s /q
md ..\dependencies\include\spark
xcopy code\spark\trunk\include\* ..\dependencies\include\spark\ /s /q
md ..\dependencies\include\box2d
xcopy code\box2d\Source\* ..\dependencies\include\box2d\ /s /q
md ..\dependencies\include\camp
xcopy code\camp\include\camp\* ..\dependencies\include\camp\ /s /q

echo Copy libraries...
xcopy code\sfml\lib\vc2008\*.lib ..\dependencies\lib /q
xcopy code\yaml-cpp\lib\*.lib ..\dependencies\lib /q
xcopy code\spark\trunk\lib\vc2008\static\*.lib ..\dependencies\lib /q

echo Copy binaries...

echo Done

pause

