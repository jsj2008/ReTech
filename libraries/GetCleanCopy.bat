@echo off

echo Removing old files...
rd code /s /q

echo Creating directories structure...
md code
md code\boost
md code\POCO
md code\box2d
md code\sfml
md code\yaml-cpp
md code\spark

echo Checkout clean copies...

echo Checkout boost...
svn co http://svn.boost.org/svn/boost/trunk code\boost
echo Checkout POCO...
svn co https://poco.svn.sourceforge.net/svnroot/poco/poco/trunk code\POCO
echo Checkout box2d...
svn co https://box2d.svn.sourceforge.net/svnroot/box2d/trunk code\box2d
echo Checkout SFML...
svn co https://sfml.svn.sourceforge.net/svnroot/sfml/branches/sfml2 code\sfml
echo Checkout YAML Cpp
svn co http://yaml-cpp.googlecode.com/svn/trunk/ code\yaml-cpp
echo Checkout SPARK
svn co https://sparkengine.svn.sourceforge.net/svnroot/sparkengine/ code\spark
pause
