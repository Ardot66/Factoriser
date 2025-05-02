#include <stdio.h>
#include <stdlib.h>

int Power(int num, int power)
{
    if(power == 0)
        return 1;

    int result = 1;
    for(int x = 0; x < power; x++)
        result *= num;

    return result;
}

int ComputePolynomial(int degree, int *polynomial, int input)
{
    int result = 0;

    for(int x = 0; x <= degree; x++)
        result += polynomial[x] * Power(input, degree - x);

    return result;
}

void PrintPolynomial(int degree, int *polynomial)
{
    for(int x = 0; x <= degree; x++)
    {
        printf("%dx%d", polynomial[x], degree - x);
        if(x < degree)
            printf(" + ");
    }

    printf("\n");
}

int FindZeroes(int degree, int *polynomial, int *zeroDest)
{
    int zeroFound = 0;
    int zero;

    for(int x = 0; x < 100; x++)
    {
        int toTest = (x >> 1) * ((x % 2 == 1) - (x % 2 == 0));
        int result = ComputePolynomial(degree, polynomial, toTest);

        if(result == 0)
        {
           *zeroDest = toTest;
           zeroFound = 1;
           zero = toTest;
           break;
        }
    }

    if(!zeroFound)
        return 0;

    int newPolynomial[degree];
    int nextValue = polynomial[0];

    for(int x = 0; x < degree; x++)
    {
        int new = nextValue;
        newPolynomial[x] = new;
        nextValue = polynomial[x + 1] - new * (-zero);
    }

    PrintPolynomial(degree - 1, newPolynomial);

    return FindZeroes(degree - 1, newPolynomial, zeroDest + 1) + 1;
}

int main(int argc, char **argv)
{
    if(argc < 3)
        return EXIT_FAILURE;

    int degree;
    if(sscanf(argv[1], "%d", &degree) < 1)
    {
        printf("Invalid degree, aborting\n");
        exit(EXIT_FAILURE);
    }

    int polynomial[degree + 1];
    int zeros[degree];

    char *polynomialArg = argv[2];
    int index = 0;
    
    while(*polynomialArg != '\0' && index <= degree)
    {
        if(index != 0 && *polynomialArg != ',')
        {
            polynomialArg++;
            continue;
        }
        
        if(index != 0)
            polynomialArg++;

        int scanned = sscanf(polynomialArg, "%d", polynomial + index);
        if(scanned < 1)
        {
            printf("Failed to read polynomial arg at index %d\n", index);
            exit(EXIT_FAILURE);
        }

        index++;
    }

    int found = FindZeroes(degree, polynomial, zeros);

    for(int x = 0; x < found; x++)
        printf("%d, ", zeros[x]);

    printf("\n");
}