OS=$(shell uname)
CCFLAGS=-Wall -pedantic -pthread
CXX=g++
OBJC=Managers/Private/MacOS/MacOS_Window.mm
INCLUDES=-IIncludes/

TARGET=Source/Engine/CoreEngine.cpp
EXE=ProjectMario

ifeq ($(OS),Linux)
	CCFLAGS +=-lGL -lGLU -lX11
endif
ifeq ($(OS),Darwin)
	CCFLAGS +=-framework Cocoa 
	CXX=clang++
endif	

all:
	@echo -e '\033[0;34m[Platform Detected] $(OS)\033[0m'
	rm -rf Bin 
	mkdir Bin
	$(CXX) $(CCFLAGS) $(INCLUDES) $(TARGET) -o Bin/$(EXE)
	
