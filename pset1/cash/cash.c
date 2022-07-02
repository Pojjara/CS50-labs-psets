#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float dollars;
    int nCoins = 0;



    do
    {
        dollars = get_float("Change owed: ");
    }
    while (dollars <= 0);
    
    int cents = round(dollars * 100);

    while (cents != 0)
    {

        while (cents >= 25)
        {
            cents = cents - 25;
            nCoins++;
        }
        while (cents >= 10)
        {
            cents = cents - 10;
            nCoins++;
        }
        while (cents >= 5)
        {
            cents = cents - 5;
            nCoins++;
        }
        while (cents >= 1)
        {
            cents = cents - 1;
            nCoins++;
        }
    }
    printf("%d\n", nCoins);


}