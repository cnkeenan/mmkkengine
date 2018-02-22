@echo off

set Debug= -Od -DDEBUG_BUILD
set Release= -Ox

set Common= -W4 -wd4996 -wd4100 -wd4201 -wd4805 -wd4189 -wd4251 -nologo -FC -Z7 -Oi -EHsc- %Debug% -DDEV_BUILD

set Includes=-I..\Includes

pushd ..\..\..\Bin
cl %Common% %Includes% ..\Source\Systems\Physics\Physics.cpp -link ObjectFramework.lib -incremental:no -opt:ref -PDB:Physics.pdb /dll /out:Physics.dll
popd