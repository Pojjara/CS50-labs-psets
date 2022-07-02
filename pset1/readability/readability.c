#include <ctype.h>
#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <string.h>

int count_letters();
int count_words();
int count_sentences();
float average_letters();
float average_sentences();
int numberOL;
int numberOW;
int numberOS;




int main(void)
{
    // Some declarations and an input for text
    string text = get_string("Text: ");
    numberOL = count_letters(text);
    numberOW = count_words(text);
    numberOS = count_sentences(text);
    float L = average_letters(text);
    float S = average_sentences(text);

    // Calculation
    float result = round(0.0588 * L - 0.296 * S - 15.8);
    int index = result;

    // Prints the results
    if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (index <= 0)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }



}

int count_letters(string text) // Counts letters in a text
{
    int numberOfLetters = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] >= 'a' && text[i] <= 'z')
        {
            numberOfLetters++;
        }
        else if (text[i] >= 'A' && text[i] <= 'Z')
        {
            numberOfLetters++;
        }
    }
    return numberOfLetters;
}

int count_words(string text) // Counts words in a text
{
    int numberOfWords = 1;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == ' ')
        {
            numberOfWords++;
        }
    }
    return numberOfWords;
}

int count_sentences(string text) // Counts sentences in a text
{
    int numberOfSentences = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            numberOfSentences++;
        }

    }
    return numberOfSentences;
}

float average_letters(string text) // Average letter
{
    float sum = ((float)numberOL / numberOW) * 100;
    return sum;
}


float average_sentences(string text) // Average sentences
{
    float sum1 = ((float)numberOS / numberOW) * 100;
    return sum1;
}










