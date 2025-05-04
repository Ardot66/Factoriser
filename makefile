SHELL = cmd

DEPEND = CollectionsPlus
BIN = Bin
HEADER = Header
SOURCE = Source/*
NAME = Factoriser

EXE := $(BIN)/$(NAME).exe

HEADERS_WILDCARD = ../*/Header
HEADERS := $(subst $() , -I , $(wildcard $(HEADERS_WILDCARD)))

All: $(EXE)

$(EXE): $(SOURCE) $(HEADERS_WILDCARD)/*
	gcc $(SOURCE) $(HEADERS) -L $(BIN) -lCollectionsPlus -o $(EXE)

Links:
	$(subst &END,,$(foreach DEPENDENCY, $(DEPEND),cmd /C mklink $(BIN)\lib$(DEPENDENCY).dll ..\$(DEPENDENCY)\$(BIN)\lib$(DEPENDENCY).dll /H &)END)

Clean:
	del /Q $(subst /,\,$(EXE))
