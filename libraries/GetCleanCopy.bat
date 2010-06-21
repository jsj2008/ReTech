@echo off

echo Removing old files...
rd code /s /q

echo Creating directories structure...
md code
md code\POCO
md code\box2d
md code\sfml
md code\AngelScript

echo Checkout clean copies...

echo Checkout POCO...
svn co https://poco.svn.sourceforge.net/svnroot/poco/poco/trunk code\POCO
echo Checkout box2d...
svn co https://box2d.svn.sourceforge.net/svnroot/box2d/trunk code\box2d
echo Checkout SFML...
svn co https://sfml.svn.sourceforge.net/svnroot/sfml/branches/sfml2 code\sfml
echo Checkout AngelScript
svn co https://angelscript.svn.sourceforge.net/svnroot/angelscript/trunk code\Angelscript

echo Done
pause
