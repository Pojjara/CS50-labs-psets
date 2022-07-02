#include <stdio.h>
#include <cs50.h>
#include <math.h>

//Declaring my variables/functions in global scope
void count();
float dollars;
int cents;
int nCoins = 0;


int main(void)
{




    // Getting input from the user
    do
    {
        dollars = get_float("Change owed: ");
    }
    while (dollars <= 0);
    cents = round(dollars * 100);
   


    // Calculating the fewest amount of coins to be given back to the customer
    while (cents != 0)
    {

        count(25);
        count(10);
        count(5);
        count(1);
    }
    
    // Printing the result
    printf("%d\n", nCoins);

}

// Definition of count function
void count(int n)
{
    while (cents >= n)
    {
        cents = cents - n;
        nCoins++;
    }

}


