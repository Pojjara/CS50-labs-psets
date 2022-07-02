#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Check usage
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // Open file
    FILE *file = fopen(argv[1], "r");
    if (!file)
    {
        printf("forensic image cannot be opened\n");
        return 1;
    }
    
    char filename[8];
    
    //Open jpg
    FILE *outjpg = NULL;
    
    //counter for jpgs already found
    int jpgsfound = 0;
    // Creating a buffer
    BYTE buffer[512];

    while (fread(buffer, sizeof(BYTE), 512, file))
    {
        // Check first three bytes
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {   
            // Check if it's the first jpg, if isn't, close the jpg.
            if (jpgsfound != 0)
            {
                fclose(outjpg);
            }
            sprintf(filename, "%03i.jpg", jpgsfound);
            outjpg = fopen(filename, "w");
            jpgsfound++;

        }
        if (jpgsfound != 0)
        {
            fwrite(buffer, sizeof(BYTE), 512, outjpg);
        }
    }
    // Close file
    fclose(file);
    fclose(outjpg);
    return 0;
}

