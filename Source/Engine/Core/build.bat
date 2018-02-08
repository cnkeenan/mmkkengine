@echo off

set Debug= -Od -DDEBUG_BUILD
set Release= -Ox

set Common= -nologo -FC -Z7 -Oi -EHsc- %Debug% -DDEV_BUILD

set Interfaces=-I..\Source\Engine\Interfaces
set Utility=-I..\Source\Engine\Utility

pushd ..\..\..\Bin
cl %Common% %Interfaces% %Utility% ..\Source\Engine\Core\CoreEngine.cpp -link -incremental:no -opt:ref /out:Project_Mario.exe
popd