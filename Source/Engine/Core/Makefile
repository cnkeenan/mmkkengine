OS=$(shell uname)
CCFLAGS=-Wall -pedantic -pthread
CXX=g++
INCLUDES=-I../../../Source/Engine/Interfaces/\
		 -I../../../Source/Engine/Utility

TARGET=CoreEngine.cpp
EXE=ProjectMario

ifeq ($(OS),Linux)
	CCFLAGS +=-lGL -lGLU -lX11
endif
ifeq ($(OS),Darwin)
	CCFLAGS +=-framework Cocoa 
endif	

all:
	@echo -e '\033[0;34m[Platform Detected] $(OS)\033[0m'
	rm -rf out
	mkdir out
	$(CXX) $(CCFLAGS) $(INCLUDES) $(TARGET) -o out/$(EXE)
	
