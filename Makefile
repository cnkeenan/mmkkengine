OS=$(shell uname)
CCFLAGS=-Wall -std=c++11 -pedantic -pthread
CXX=g++
OBJC=
ADD_OBJ=
INCLUDES=-IIncludes/

TARGET=Source/Engine/CoreEngine.cpp
EXE=ProjectMario
ifeq ($(OS),Linux)
	CCFLAGS +=-lX11 -ldl
endif

ifeq ($(OS),Darwin)
	CCFLAGS +=-framework Cocoa -framework OpenGL -framework Foundation
	OBJC+=clang++ -std=c++11 -IIncludes Includes/Platform/MacOS/MacOS_Window.mm -c
	ADD_OBJ=MacOS_Window.o
	CXX=clang++
endif	

all:
	@echo -e '\033[0;34m[Platform Detected] $(OS)\033[0m'
	rm -rf Bin 
	mkdir Bin
	$(OBJC)
	$(CXX) $(CCFLAGS) $(INCLUDES) $(TARGET) -o Bin/$(EXE) $(ADD_OBJ)
	
