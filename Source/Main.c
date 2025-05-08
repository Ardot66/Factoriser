#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CollectionsPlus.h"
#include "Command.h"

extern const Command PolynomialCommand;

const Command *Commands[] =
{
    &PolynomialCommand
};

const size_t CommandCount = sizeof(Commands) / sizeof(*Commands);

int main(int argc, char **argv)
{
    const Command *command = NULL;
    if(argc > 1)
        command = FindCommand(Commands, CommandCount, argv[1]);

    if(command != NULL)
        return command->Command(argc - 2, argv + 2);
}