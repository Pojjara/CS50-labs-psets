#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int startSize;
    do
    {
        startSize = get_int("Start size : ");
    }
    while (startSize < 9);

    // TODO: Prompt for end size
    int endSize;
    do
    {
        endSize = get_int("End size : ");
    }
    while (endSize < startSize);

    // TODO: Calculate number of years until we reach threshold
    // n/3 - are born
    // n/4 - pass away

    int numberOfYears = 0;
    int population = startSize;

    
    
    while (population < endSize)
    {
        population = population + (population / 3) - (population / 4);
        numberOfYears++; 
    }

    

    // TODO: Print number of years
    printf("Years: %i", numberOfYears);
}

