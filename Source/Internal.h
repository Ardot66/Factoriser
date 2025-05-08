#ifndef ___INTERNAL___
#define ___INTERNAL___

#include "Command.h"
#include "CollectionsPlus.h"

typedef List(char, char) ListChar;
typedef struct Token Token;

typedef struct TokenType
{
    int (*Simplify)(Token *token);
    int (*FromString)(char *string, size_t index, Token *tokenDest);
    int (*ToString)(Token *token, ListChar *string);
    int (*Priority)(char *string, size_t *indexDest);
} TokenType;

struct Token
{
    const TokenType *Type;
    void *Data;
};

int TokenFromString(char *string, Token *tokenDest);

extern const Command PolynomialCommand;
extern const Command HelpCommand;
extern const Command SimplifyCommand;

extern const Command **HelpCommandList;
extern size_t HelpCommandListCount;

#endif