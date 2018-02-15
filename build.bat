@echo off

set Debug= -Od -DDEBUG_BUILD
set Release= -Ox

set Common= -nologo -FC -Z7 -Oi -EHsc- %Debug% -DDEV_BUILD

set Includes=-I..\Includes
set GameInclude=-I..\Pong

pushd Bin
cl %Common% %Includes% -DFRAMEWORK_EXPORT ..\Source\ObjectFramework\ObjectFramework.cpp -link -incremental:no -opt:ref -PDB:ObjectFramework.pdb /dll /out:ObjectFramework.dll 
cl %Common% %Includes% -DGAME_EXPORT ..\Pong\Pong.cpp -link ObjectFramework.lib -incremental:no -opt:ref -PDB:Pong.pdb /dll /out:Pong.dll
cl %Common% %Includes% %GameInclude% ..\Source\Engine\CoreEngine.cpp -link ObjectFramework.lib Pong.lib -incremental:no -opt:ref /out:Project_Mario.exe
popd