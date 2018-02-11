@echo off

set Debug= -Od -DDEBUG_BUILD
set Release= -Ox

set Common= -nologo -FC -Z7 -Oi -EHsc- %Debug% -DDEV_BUILD

set Includes=-I..\Includes

pushd Bin
cl %Common% %Includes% ..\Source\Engine\CoreEngine.cpp -link -incremental:no -opt:ref /out:Project_Mario.exe
popd