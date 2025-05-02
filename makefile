NAME = Factorisor
BIN = Bin
SOURCE = Source
EXE = $(BIN)/$(NAME).exe

All: $(EXE)

$(EXE): $(SOURCE)/*
	gcc Source/Main.c -o $(EXE)