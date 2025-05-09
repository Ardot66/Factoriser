#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CollectionsPlus.h"
#include "Internal.h"

const Command *Commands[] =
{
    &PolynomialCommand,
    &HelpCommand,
    &SimplifyCommand
};

const size_t CommandCount = sizeof(Commands) / sizeof(*Commands);

int main(int argc, char **argv)
{
    HelpCommandList = Commands;
    HelpCommandListCount = CommandCount;

    const Command *command = NULL;
    if(argc > 1)
        command = FindCommand(Commands, CommandCount, argv[1]);

    if(command != NULL)
        return command->Command(argc - 2, argv + 2);

    return EXIT_SUCCESS;
}