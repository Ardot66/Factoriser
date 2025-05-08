#include <stdlib.h>
#include <stdio.h>
#include "Command.h"
#include "Internal.h"
#include "Try.h"

extern const TokenType *Tokens[];

int Simplify(int argCount, char **args)
{
    if(argCount < 1)
        return EXIT_FAILURE;

    Token token;
    int result = TokenFromString(args[0], &token);
    PrintStackTrace();

    ListChar string;
    ListInit(&string, 256);
    token.Type->ToString(&token, &string);
    char end = '\0';
    ListAdd(&string, &end);

    printf("%s\n", string.V);

    return EXIT_SUCCESS;
}

const Command SimplifyCommand = CommandInit(
    "sim",
    Simplify,
    "",
    "\n"
);