@echo off
call "%VS90COMNTOOLS%vsvars32.bat"

rem ********** UPDATES ****************
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
rem ********** BOOST ****************
cd code\boost
call "bootstrap.bat"
bjam --build-type=complete stage --with=filesystem --toolset=msvc-9.0
cd ..\..

rem ********** BOX2D ****************
echo Build Box2D debug...
devenv code\box2d\Build\VC8\Box2D.sln /build "Debug" /project Box2D
echo Build Box2D release...
devenv code\box2d\Build\VC8\Box2D.sln /build "Release" /project Box2D

rem ********** CAMP ****************
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

rem ********** SFML ****************
echo Build SFML debug...
devenv code\sfml\build\vc2008\SFML.sln /build "Debug DLL" /project sfml-main
devenv code\sfml\build\vc2008\SFML.sln /build "Debug DLL" /project sfml-system
devenv code\sfml\build\vc2008\SFML.sln /build "Debug DLL" /project sfml-window
devenv code\sfml\build\vc2008\SFML.sln /build "Debug DLL" /project sfml-network
devenv code\sfml\build\vc2008\SFML.sln /build "Debug DLL" /project sfml-graphics
devenv code\sfml\build\vc2008\SFML.sln /build "Debug DLL" /project sfml-audio
echo Build SFML release...
devenv code\sfml\build\vc2008\SFML.sln /build "Release DLL" /project sfml-main
devenv code\sfml\build\vc2008\SFML.sln /build "Release DLL" /project sfml-system
devenv code\sfml\build\vc2008\SFML.sln /build "Release DLL" /project sfml-window
devenv code\sfml\build\vc2008\SFML.sln /build "Release DLL" /project sfml-network
devenv code\sfml\build\vc2008\SFML.sln /build "Release DLL" /project sfml-graphics
devenv code\sfml\build\vc2008\SFML.sln /build "Release DLL" /project sfml-audio

rem ********** SFGUI ****************
echo Copy SfGui to SFML folder...
xcopy code\sfgui\* code\sfml\ /s /q /y
xcopy code\sfml\lib\vc2008\*.lib code\sfml\build\vc2008\sfgui /q /y
echo Build SfGui debug...
devenv code\sfml\build\vc2008\sfgui\sfgui.sln /build "Debug" /project sfgui
echo Build SfGui release...
devenv code\sfml\build\vc2008\sfgui\sfgui.sln /build "Release" /project sfgui

rem ********** SPARK ****************
echo Copy SFML to SPARK folder...
xcopy code\sfml\include\sfml\* code\spark\trunk\include\sfml\ /s /q /y
xcopy code\sfml\lib\vc2008\*.lib "code\spark\trunk\projects\vc2008\SPARK engine" /q /y
echo Build SPARK debug...
devenv code\spark\trunk\projects\vc2008\SPARK_engine.sln /build "Debug" /project "SPARK Engine CORE DLL"
devenv code\spark\trunk\projects\vc2008\SPARK_engine.sln /build "Debug" /project "SPARK Engine GL DLL"
devenv code\spark\trunk\projects\vc2008\SPARK_engine.sln /build "Debug" /project "SPARK Engine SFML DLL"
echo Build SPARK release...
devenv code\spark\trunk\projects\vc2008\SPARK_engine.sln /build "Release" /project "SPARK Engine CORE DLL"
devenv code\spark\trunk\projects\vc2008\SPARK_engine.sln /build "Release" /project "SPARK Engine GL DLL"
devenv code\spark\trunk\projects\vc2008\SPARK_engine.sln /build "Release" /project "SPARK Engine SFML DLL"

rem ********** YAML CPP ****************
echo Build YAML Cpp debug...
devenv code\yaml-cpp\yamlcpp.sln /build "Debug" /project yamlcpp
echo Build YAML Cpp release...
devenv code\yaml-cpp\yamlcpp.sln /build "Release" /project yamlcpp

rem ********** REMOVE OLD FILES ****************
echo Remove old files...
rd /q /s ..\dependencies
md ..\dependencies
md ..\dependencies\lib
md ..\dependencies\include
del ..\bin\*.dll /q

rem ********** INCLUDES ****************
echo Copy includes...
md ..\dependencies\include\boost
xcopy code\boost\boost\* ..\dependencies\include\boost\ /s /q /y
md ..\dependencies\include\fastdelegates
xcopy external\fastdelegates\* ..\dependencies\include\fastdelegates\ /s /q /y
md ..\dependencies\include\sfml
xcopy code\sfml\include\sfml\* ..\dependencies\include\sfml\ /s /q /y
md ..\dependencies\include\sfgui
xcopy code\sfgui\include\sfgui\* ..\dependencies\include\sfgui\ /s /q /y
md ..\dependencies\include\yaml-cpp
xcopy code\yaml-cpp\include\* ..\dependencies\include\yaml-cpp\ /s /q /y
md ..\dependencies\include\spark
xcopy code\spark\trunk\include\* ..\dependencies\include\spark\ /s /q /y
md ..\dependencies\include\box2d
xcopy code\box2d\Source\* ..\dependencies\include\box2d\ /s /q /y
md ..\dependencies\include\camp
xcopy code\camp\include\camp\* ..\dependencies\include\camp\ /s /q /y

rem ********** LIBRARIES ****************
echo Copy libraries...
xcopy code\sfml\lib\vc2008\*.lib ..\dependencies\lib /q /y
xcopy code\yaml-cpp\lib\*.lib ..\dependencies\lib /q /y
xcopy code\spark\trunk\lib\vc2008\dynamic\*.lib ..\dependencies\lib /q /y
xcopy code\camp\Debug\campd.lib ..\dependencies\lib /q /y
xcopy code\camp\Release\camp.lib ..\dependencies\lib /q /y
xcopy code\boost\stage\lib\libboost_filesystem-vc90-mt-gd-1_45.lib ..\dependencies\lib /q /y
xcopy code\boost\stage\lib\libboost_filesystem-vc90-mt-1_45.lib ..\dependencies\lib /q /y
xcopy code\boost\stage\lib\libboost_system-vc90-mt-gd-1_45.lib ..\dependencies\lib /q /y
xcopy code\boost\stage\lib\libboost_system-vc90-mt-1_45.lib ..\dependencies\lib /q /y

rem ********** BINARIES ****************
echo Copy binaries...
xcopy code\camp\Debug\campd.dll ..\bin /q /y
xcopy code\camp\Release\camp.dll ..\bin /q /y
xcopy code\sfml\lib\vc2008\*.dll ..\bin /q /y
xcopy code\spark\trunk\lib\vc2008\dynamic\*.dll ..\bin /q /y

echo Done

pause

