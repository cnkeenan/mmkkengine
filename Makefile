OS=$(shell uname)
CCFLAGS=-Wall -pedantic -std=c++11 -pthread
CXX=g++
OBJC=
ADD_OBJ=
INCLUDES=-IIncludes/ -IPong/
DEBUG= -g
LIBS=./Bin/ObjectFramework.o ./Bin/Pong.o

TARGET=Source/Engine/CoreEngine.cpp
EXE=ProjectMario
ifeq ($(OS),Linux)
	CCFLAGS +=-lX11 -ldl
endif

ifeq ($(OS),Darwin)
	CCFLAGS +=-framework Cocoa -framework OpenGL -framework Foundation
	OBJC+=clang++ -std=c++11 $(DEBUG) -IIncludes Includes/Platform/MacOS/MacOS_Window.mm -c
	ADD_OBJ=MacOS_Window.o
	CXX=clang++
endif	

all:
	@echo -e '\033[0;34m[Platform Detected] $(OS)\033[0m'
	export LD_LIBRARY_PATH=./Libs
	$(OBJC)
	$(CXX) $(CCFLAGS) $(DEBUG) $(INCLUDES) $(TARGET) $(LIBS) -o Bin/$(EXE) $(ADD_OBJ)

libs:
	@echo -e 'Making Libraries'
	rm -rf Bin
	mkdir Bin
	rm -rf Libs
	mkdir Libs
	$(CXX) $(INCLUDES) -fPIC -c Source/ObjectFramework/ObjectFramework.cpp -o ./Bin/ObjectFramework.o
	$(CXX) $(INCLUDES) -fPIC -c Source/Systems/AI/AI.cpp -o ./Bin/AI.o
	$(CXX) $(INCLUDES) -fPIC -c Source/Systems/Collision/Collision.cpp -o ./Bin/Collision.o
	$(CXX) $(INCLUDES) -fPIC -c Source/Systems/Graphics/Graphics.cpp -o ./Bin/Graphics.o
	$(CXX) $(INCLUDES) -fPIC -c Source/Systems/Input/Input.cpp -o ./Bin/Input.o
	$(CXX) $(INCLUDES) -fPIC -c Source/Systems/Physics/Physics.cpp -o ./Bin/Physics.o
	$(CXX) $(INCLUDES) -fPIC -c Source/Systems/Sound/Sound.cpp -o ./Bin/Sound.o
	$(CXX) $(INCLUDES) -fPIC -c Source/Systems/Transform/Transform.cpp -o ./Bin/Transform.o
	$(CXX) $(INCLUDES) -fPIC -c Source/Systems/Widget/Widget.cpp -o ./Bin/Widget.o
	$(CXX) $(INCLUDES) -fPIC -c Pong/Pong.cpp -o ./Bin/Pong.o

	$(CXX) -shared -o ./Libs/ObjectFramework.so ./Bin/ObjectFramework.o
	$(CXX) -shared -o ./Libs/AI.so ./Libs/ObjectFramework.so ./Bin/AI.o
	$(CXX) -shared -o ./Libs/Collision.so ./Libs/ObjectFramework.so ./Bin/Collision.o
	$(CXX) -shared -o ./Libs/Graphics.so ./Libs/ObjectFramework.so ./Bin/Graphics.o
	$(CXX) -shared -o ./Libs/Input.so ./Libs/ObjectFramework.so ./Bin/Input.o
	$(CXX) -shared -o ./Libs/Physics.so ./Libs/ObjectFramework.so ./Bin/Physics.o
	$(CXX) -shared -o ./Libs/Sound.so ./Libs/ObjectFramework.so ./Bin/Sound.o
	$(CXX) -shared -o ./Libs/Transform.so ./Libs/ObjectFramework.so ./Bin/Transform.o
	$(CXX) -shared -o ./Libs/Widget.so ./Libs/ObjectFramework.so ./Bin/Widget.o
	$(CXX) -shared -o ./Libs/Pong.so ./Libs/ObjectFramework.so ./Bin/Pong.o

	
