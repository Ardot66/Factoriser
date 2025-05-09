SHELL = bash

DEPEND = $() CollectionsPlus Try Command
DLL_BIN = ../Bin
BIN = Bin
SOURCE = Source/*.c
TESTS = Tests/*.c
NAME = Factoriser

EXE := $(BIN)/$(NAME).exe

HEADERS_WILDCARD = ../*/Header
HEADERS := $(subst $() , -I , $(wildcard $(HEADERS_WILDCARD)))

Debug: COMPILE_FLAGS = -g
Debug: Compile

Release: COMPILE_FLAGS = -s
Release: Compile

Debugger: RUN = gdb $(EXE)
Debugger: Debug

Compile: $(EXE)
	$(RUN)

$(EXE): $(SOURCE) $(HEADERS_WILDCARD)/*.h
	gcc $(COMPILE_FLAGS) $(SOURCE) $(HEADERS) -L$(DLL_BIN) $(subst $() , -l,$(DEPEND)) -o $(EXE)

Clean:
	rm $(TESTS_EXE) $(EXE)
