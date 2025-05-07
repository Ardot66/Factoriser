#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CollectionsPlus.h"
#include "Command.h"

int SolvePolynomial(int argc, char **argv);

const Command Commands[] = 
{
    CommandInit(
        "polynomial poly", 
        SolvePolynomial, 
        "[x^n[+ or -]x^n-1[+ or -]...] [-h] [-p [integer]]",
        "\n"
        "%i-h%pPrints this information\n"
        "%i-p%p[integer] Decimal precision of results\n"
        "\n"
        "Example use: Factoriser 1-2+1 -p 3\n"
        "This would find the zeroes of the polynomial x^2-2x+1\n"
    )
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