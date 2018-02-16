@echo off

set Debug= -Od -DDEBUG_BUILD
set Release= -Ox

set Common= -nologo -FC -Z7 -Oi -EHsc- %Debug% -DDEV_BUILD

set Includes=-I..\Includes
set GameInclude=-I..\Pong

pushd Bin
cl %Common% %Includes% -DFRAMEWORK_EXPORT ..\Source\ObjectFramework\ObjectFramework.cpp -link -incremental:no -opt:ref -PDB:ObjectFramework.pdb /dll /out:ObjectFramework.dll 
cl %Common% %Includes% ..\Source\Systems\AI\AI.cpp -link ObjectFramework.lib -incremental:no -opt:ref -PDB:AI.pdb /dll /out:AI.dll
cl %Common% %Includes% ..\Source\Systems\Collision\Collision.cpp -link ObjectFramework.lib -incremental:no -opt:ref -PDB:Collision.pdb /dll /out:Collision.dll
cl %Common% %Includes% ..\Source\Systems\Graphics\Graphics.cpp -link ObjectFramework.lib -incremental:no -opt:ref -PDB:Graphics.pdb /dll /out:Graphics.dll
cl %Common% %Includes% ..\Source\Systems\Input\Input.cpp -link ObjectFramework.lib -incremental:no -opt:ref -PDB:Input.pdb /dll /out:Input.dll
cl %Common% %Includes% ..\Source\Systems\Physics\Physics.cpp -link ObjectFramework.lib -incremental:no -opt:ref -PDB:Physics.pdb /dll /out:Physics.dll
cl %Common% %Includes% ..\Source\Systems\Sound\Sound.cpp -link ObjectFramework.lib -incremental:no -opt:ref -PDB:Sound.pdb /dll /out:Sound.dll
cl %Common% %Includes% ..\Source\Systems\Transform\Transform.cpp -link ObjectFramework.lib -incremental:no -opt:ref -PDB:Transform.pdb /dll /out:Transform.dll
cl %Common% %Includes% ..\Source\Systems\Widget\Widget.cpp -link ObjectFramework.lib -incremental:no -opt:ref -PDB:Widget.pdb /dll /out:Widget.dll
cl %Common% %Includes% -DGAME_EXPORT ..\Pong\Pong.cpp -link ObjectFramework.lib -incremental:no -opt:ref -PDB:Pong.pdb /dll /out:Pong.dll
cl %Common% %Includes% %GameInclude% ..\Source\Engine\CoreEngine.cpp -link ObjectFramework.lib Pong.lib -incremental:no -opt:ref /out:Project_Mario.exe
popd