SHELL = cmd

DEPEND = $() CollectionsPlus Try Command
BIN = ../Bin
HEADER = Header
SOURCE = Source/*
NAME = Factoriser

EXE := $(BIN)/$(NAME).exe

HEADERS_WILDCARD = ../*/Header
HEADERS := $(subst $() , -I , $(wildcard $(HEADERS_WILDCARD)))

All: $(EXE)
	$(EXE) sim $(ARGS)

$(EXE): $(SOURCE) $(HEADERS_WILDCARD)/*
	gcc $(SOURCE) $(HEADERS) -L$(BIN) $(subst $() , -l,$(DEPEND)) -o $(EXE)

Clean:
	del /Q $(subst /,\,$(EXE))
