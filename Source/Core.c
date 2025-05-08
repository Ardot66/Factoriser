#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "Internal.h"
#include "Try.h"
#include "CollectionsPlus.h"

int ListCharAddString(ListChar *list, char *string)
{
    while(*string != '\0')
    {
        Try(ListAdd(list, string), -1);
        string++;
    }
}

int Bracket(char character)
{
    return (character == '(') - (character == ')');
}

int NumberPriority(char *string, size_t *indexDest)
{
    int lowestBrackets = -1;
    int brackets = 0;
    size_t index = 0;
    while(*string != '\0')
    {
        brackets += Bracket(*string);
        float temp;
        if(sscanf(string, "%f", &temp) > 0)
        {
            *indexDest = index;
            return brackets;
        }

        index++;
        string++;
    }

    return -1;
}

int NumberFromString(char *string, size_t index, Token *tokenDest)
{
    float *value;
    Try((value = malloc(sizeof(float))) == NULL, -1);

    sscanf(string + index, "%f", value);
    tokenDest->Data = value;
    return 0;
}

int NumberToString(Token *token, ListChar *string)
{
    char numberString[33];
    snprintf(numberString, 32, "%f", *(float *)token->Data);
    Try(ListCharAddString(string, numberString), -1);
    return 0;
}

int AddPriority(char *string, size_t *indexDest)
{
    int lowestBrackets = -1;
    int brackets = 0;
    size_t index = 0;

    while(*string != '\0')
    {
        brackets += Bracket(*string);
        if(*string == '+' && (lowestBrackets == -1 || lowestBrackets > brackets))
        {
            *indexDest = index;
            lowestBrackets = brackets;
        }

        index++;
        string++;
    }

    return lowestBrackets;
}

int AddFromString(char *string, size_t index, Token *tokenDest)
{
    Try((tokenDest->Data = malloc(sizeof(Token) * 2)) == NULL, -1);
    Token *addTokens = tokenDest->Data;

    char beforeString[index + 1];
    memcpy(beforeString, string, index);
    beforeString[index] = '\0';

    Try(TokenFromString(beforeString, addTokens + 0), -1);
    Try(TokenFromString(string + index + 1, addTokens + 1), -1);

    return 0;
}

int AddToString(Token *token, ListChar *string)
{
    Token *addTokens = token->Data;

    addTokens[0].Type->ToString(addTokens + 0, string);
    ListCharAddString(string, " + ");
    addTokens[1].Type->ToString(addTokens + 1, string);
}

const TokenType *Tokens[] =
{
    &(TokenType){NULL, AddFromString, AddToString, AddPriority},
    &(TokenType){NULL, NumberFromString, NumberToString, NumberPriority}
};

const size_t TokenCount = sizeof(Tokens) / sizeof(*Tokens);

int TokenFromString(char *string, Token *tokenDest)
{
    int lowestPriority = -1;
    const TokenType *lowestPriorityToken;
    size_t lowestPriorityIndex;

    for(int x = 0; x < TokenCount; x++)
    {
        const TokenType *token = Tokens[x];
        size_t index;
        int priority = token->Priority(string, &index);

        if(priority != -1 && (lowestPriority == -1 || priority < lowestPriority))
        {
            lowestPriorityToken = token;
            lowestPriority = priority;
            lowestPriorityIndex = index;
        }
    }

    if(lowestPriority == -1)
        return -1;

    tokenDest->Type = lowestPriorityToken;
    return lowestPriorityToken->FromString(string, lowestPriorityIndex, tokenDest);
}