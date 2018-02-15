OS=$(shell uname)
CCFLAGS=-Wall -std=c++11 -pedantic -pthread
CXX=g++
OBJC=
ADD_OBJ=
INCLUDES=-IIncludes/
DEBUG= -g

TARGET=Source/Engine/CoreEngine.cpp
EXE=ProjectMario
ifeq ($(OS),Linux)
	CCFLAGS +=-lGL -lX11
endif

ifeq ($(OS),Darwin)
	CCFLAGS +=-framework Cocoa -framework OpenGL -framework Foundation
	OBJC+=clang++ -std=c++11 $(DEBUG) -IIncludes Includes/Platform/MacOS/MacOS_Window.mm -c
	ADD_OBJ=MacOS_Window.o
	CXX=clang++
endif	

all:
	@echo -e '\033[0;34m[Platform Detected] $(OS)\033[0m'
	rm -rf Bin 
	mkdir Bin
	$(OBJC)
	$(CXX) $(CCFLAGS) $(DEBUG) $(INCLUDES) $(TARGET) -o Bin/$(EXE) $(ADD_OBJ)
	
