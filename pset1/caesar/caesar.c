#include <ctype.h>
#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

// Calling my functions and my key value
void dostuff();
void dostuffs();
string key;


int main(int argc, string argv[])
{
    key = argv[1]; // key needs to by typed in like so : "./caesar key"
    if (argc != 2) // prompting the user to correctly type in the key
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else
    {
        string plain = get_string("plaintext: ");
        printf("ciphertext: ");
        dostuffs(plain);
    }
    printf("\n");
    return 0;
}


void dostuffs(string plain)
{
    int at = atoi(key) % 26; // Calculates the modulo of key%26
    for (int i = 0, n = strlen(plain); i < n; i++)
    {
        int diffl = 'z' - plain[i] + 1; // difference for lower letters
        int diffU = 'Z' - plain[i] + 1; // difference for upper letters
        if (islower(plain[i]))
        {
            if (plain[i] + at > 'z') // If after adding the key the letter is bigger than 'z'it starts adding the modulo minus difference
            { 
                printf("%c", 'a' + (at - diffl));
            }
            else
            {
                printf("%c", plain[i] + at);
            }
        }
        else if (isupper(plain[i])) // Does all the same but for upper letters
        {
            if (plain[i] + at > 'Z')
            {
                printf("%c", 'A' + (at - diffU));
            }
            else
            {
                printf("%c", plain[i] + at);
            }
        }
        else
        {
            printf("%c", plain[i]);
        }
    }
}

















