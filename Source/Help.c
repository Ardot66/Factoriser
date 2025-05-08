#include <stdlib.h>
#include <stdio.h>
#include "Command.h"

const Command **HelpCommandList = NULL;
size_t HelpCommandListCount = 0;

int Help(int argCount, char **args)
{
    printf("\n");

    if(argCount > 0 && HelpCommandList != NULL)
    {
        const Command *command = FindCommand(HelpCommandList, HelpCommandListCount, args[0]);
        if(command != NULL)
            PrintCommandHelp(command, 3, 20);
    }
    else
        for(int x = 0; x < HelpCommandListCount; x++)
            PrintCommandSummary(HelpCommandList[x], 15);

    printf("\n");
    return EXIT_SUCCESS;
}

const Command HelpCommand = CommandInit(
    "help",
    Help,
    "[command] Displays this information, or information on a specific command",
    "\n"
);