#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CollectionsPlus.h"
#include "Command.h"

int PrintPrecision = 2;

typedef List(float, float) ListFloat;

float Abs(float a)
{
    return a * ((a >= 0) - (a < 0));
}

float Power(float num, int power)
{
    if(power == 0)
        return 1;

    float result = 1;
    for(int x = 0; x < power; x++)
        result *= num;

    return result;
}

float ComputePolynomial(int degree, float *polynomial, float input)
{
    float result = 0;

    for(int x = 0; x <= degree; x++)
        result += polynomial[x] * Power(input, degree - x);

    return result;
}

void PrintPolynomial(int degree, float *polynomial)
{
    for(int x = 0; x <= degree; x++)
    {
        printf("%.*fx%d", PrintPrecision, Abs(polynomial[x]), degree - x);
        if(x < degree)
        {
            if(polynomial[x + 1] > 0)
                printf(" + ");
            else
                printf(" - ");
        }
    }

    printf("\n");
}

float TestForZero(int degree, float *polynomial, float startingIncrement, int iterations, float testFrom, float *zero)
{
    float increment = startingIncrement;
    float point = testFrom;
    float distance = 1.0f;
    int direction = 0;

    for(int x = 0; x < iterations; x++)
    {
        if(distance == 0.0f)
            break;

        float up = Abs(ComputePolynomial(degree, polynomial, point + increment));
        float down = Abs(ComputePolynomial(degree, polynomial, point - increment));
        int oldDirection = direction;

        if(up < down)
        {
            distance = up;
            point += increment;
            direction = 1;
        }
        else
        {
            distance = down;
            direction = -1;
            point -= increment;
        }

        if(oldDirection != 0 && oldDirection != direction)
            increment /= 2;
    }

    *zero = point;
    return distance;
}

int FindZeroes(int degree, float *polynomial, int zerosFound, float *zeroDest)
{
    if(degree < 1)
        return 0;

    int zeroFound = 0;
    float zero;

    for(int x = 0; x < 50; x++)
    {
        int toTest = (x >> 1) * ((x % 2 == 1) - (x % 2 == 0));
        float distance = TestForZero(degree, polynomial, 0.5f, 100, (float)toTest, &zero);

        if(distance < 0.01f)
        {
           zeroDest[zerosFound] = zero;
           zeroFound = 1;
           break;
        }

        AlreadyFound:
    }

    if(!zeroFound)
        return 0;

    PrintPolynomial(degree, polynomial);

    float newPolynomial[degree];
    float nextValue = polynomial[0];

    for(int x = 0; x < degree; x++)
    {
        newPolynomial[x] = nextValue;
        nextValue = polynomial[x + 1] - nextValue * (-zero);
    }

    return FindZeroes(degree - 1, newPolynomial, zerosFound + 1, zeroDest) + 1;
}

int SolvePolynomial(int argc, char **argv)
{
    if(argc < 1)
        return EXIT_FAILURE;

    char *arg;
    if(FindArg(argc, argv, "-p", &arg))
    {
        int precision;
        if(sscanf(arg, "%d", &precision) < 1)
            printf("Failed to read precision");
        else
            PrintPrecision = precision;
    }

    ListFloat polynomial;
    ListInit(&polynomial, 10);

    char *polynomialArg = argv[0];
    int index = 0;
    
    while(*polynomialArg != '\0')
    {
        if(index != 0 && *polynomialArg != '+' && *polynomialArg != '-' || *polynomialArg == ' ')
        {
            polynomialArg++;
            continue;
        }

        float sign = 1;
        if(*polynomialArg == '-')
            sign = -1;

        if(index != 0)
            polynomialArg++;

        float coefficient;
        int scanned = sscanf(polynomialArg, "%f", &coefficient);
        coefficient *= sign; 
        
        if(scanned < 1)
        {
            printf("Failed to read polynomial arg at index %d\n", index);
            exit(EXIT_FAILURE);
        }

        ListAdd(&polynomial, &coefficient);
        index++;
    }

    float zeros[polynomial.Count - 1];
    int found = FindZeroes(polynomial.Count - 1, polynomial.V, 0, zeros);

    printf("Zeroes are: ");

    for(int x = 0; x < found; x++)
        printf("%.*f, ", PrintPrecision, zeros[x]);

    printf("\n");
    return EXIT_SUCCESS;
}

const Command PolynomialCommand = CommandInit(
    "polynomial poly", 
    SolvePolynomial, 
    "[x^n[+ or -]x^n-1[+ or -]...] [-h] [-p [integer]]",
    "\n"
    "%i-h%pPrints this information\n"
    "%i-p%p[integer] Decimal precision of results\n"
    "\n"
    "Example use: Factoriser 1-2+1 -p 3\n"
    "This would find the zeroes of the polynomial x^2-2x+1\n"
);