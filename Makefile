#
# Makefile
#
# This file is part of the Core C++ source code.
# Copyright 2014 Patrick L. Melo <patrick@patrickmelo.com.br>
#

# Common Variables

CXX			= g++
CXX_FLAGS	= -O3 -std=c++0x -fno-pic -Wno-sign-compare -Wno-write-strings -Wno-narrowing -D_FILE_OFFSET_BITS=64
DEBUG_FLAGS	= -g3 -DCORE_ENABLE_DEBUGGER=1
EXE_PATH	= ./Core
INCLUDES	= -I./
LIBS		=
STRIP		= @true
STRIP_EXE	= strip
OBJECTS		= Main.o

# Linux Variables

LINUX_CXX		= g++
LINUX_CXX_FLAGS	= -DCORE_COLOR_MESSAGES=1
LINUX_INCLUDES	=
LINUX_LIBS		= -lm
LINUX_OBJECTS	=

# OSX Variables

OSX_CXX			= g++
OSX_CXX_FLAGS	= -DCORE_COLOR_MESSAGES=1
OSX_INCLUDES	=
OSX_LIBS		=
OSX_OBJECTS		=

# Windows Variables

WINDOWS_CXX_32		= i686-w64-mingw32-g++
WINDOWS_CXX_64		= x86_64-w64-mingw32-g++
WINDOWS_CXX_FLAGS	= -static-libgcc -static-libstdc++
WINDOWS_INCLUDES	=
WINDOWS_LIBS		=
WINDOWS_STRIP_32	= i686-w64-mingw32-strip
WINDOWS_STRIP_64	= x86_64-w64-mingw32-strip
WINDOWS_OBJECTS		=

# "Final" Variables

ifndef TARGET
	TARGET = linux
endif

ifndef TYPE
	TYPE = debug
endif

ifndef BITS
	BITS = 64
endif

ifeq ($(BITS), 32)
	ARCH = i686
else
	ARCH = x86_64
endif

ifeq ($(TARGET), linux)
	CXX			= $(LINUX_CXX)
	CXX_FLAGS	+= $(LINUX_CXX_FLAGS)
	INCLUDES	+= $(LINUX_INCLUDES)
	LIBS		+= $(LINUX_LIBS)
	OBJECTS		+= $(LINUX_OBJECTS)
endif

ifeq ($(TARGET), osx)
	ARCH		:= $(ARCH).osx
	CXX			 = $(OSX_CXX)
	CXX_FLAGS	+= $(OSX_CXX_FLAGS)
	INCLUDES	+= $(OSX_INCLUDES)
	LIBS		+= $(OSX_LIBS)
	OBJECTS		+= $(OSX_OBJECTS)
endif

ifeq ($(TARGET), windows)
	ARCH		:= $(ARCH).exe
	CXX_FLAGS	+= $(WINDOWS_CXX_FLAGS)
	INCLUDES	+= $(WINDOWS_INCLUDES)
	LIBS		+= $(WINDOWS_LIBS)
	OBJECTS		+= $(WINDOWS_OBJECTS)

	ifeq ($(BITS), 32)
		CXX			= $(WINDOWS_CXX_32)
		STRIP_EXE	= $(WINDOWS_STRIP_32)
	else
		CXX			= $(WINDOWS_CXX_64)
		STRIP_EXE	= $(WINDOWS_STRIP_64)
	endif
endif

ifeq ($(TYPE), debug)
	CXX_FLAGS	+= $(DEBUG_FLAGS)
	ARCH		:= debug.$(ARCH)
endif

ifeq ($(TYPE), release)
	STRIP = $(STRIP_EXE) -x $(EXE_PATH).$(ARCH)
endif

ifeq ($(BITS), 32)
	CXX_FLAGS += -m32
else
	CXX_FLAGS += -m64
endif

# Targets

%.o: %.cxx
	$(CXX) $(CXX_FLAGS) $(INCLUDES) -c $< -o $@

all: $(OBJECTS)
	$(CXX) $(CXX_FLAGS) $(INCLUDES) $(OBJECTS) $(LIBS) -o $(EXE_PATH).$(ARCH)
	$(STRIP) $(EXE_PATH).$(ARCH)

clean:
	rm -rf $(OBJECTS)
	
help:
	@echo ""
	@echo "Usage: make TARGET=<target name> TYPE=<debug|release> BITS=<32|64>"
	@echo ""
	@echo "Available targets:"
	@echo " - linux"
	@echo " - osx"
	@echo " - windows"
	@echo ""
	@echo "Defaults to: linux, debug, 64"	
