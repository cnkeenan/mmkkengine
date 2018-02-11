Debug="-Od -DDEBUG_BUILD"
Release=-Ox

Common="-nologo -FC -Z7 -Oi -EHsc- $Debug -DDEV_BUILD"

Interfaces=-I../Source/Engine/Interfaces
Utility=-I../Source/Engine/Utility



pushd ../../../Bin
clang++ -std=c++11 $Interfaces $Utility ../Source/Engine/Core/Managers/Private/MacOS/MacOS_Window.mm -c 
clang++ -std=c++11 $Interfaces $Utility ../Source/Engine/Core/CoreEngine.cpp -o Project_Mario MacOS_Window.o -framework Cocoa
popd