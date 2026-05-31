#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BLOCK_SIZE 512

int main(int argc, char *argv[])
{
    int in_jpeg = 0;
    int counter = 0;

    if (argc != 2)
    {
        printf("Usage: ./recover card.raw\n");
        return 1;
    }

    FILE *raw_file = fopen(argv[1], "rb");
    if (raw_file == NULL)
    {
        printf("Could not open file %s.\n", argv[1]);
        return 1;
    }

    uint8_t buffer[BLOCK_SIZE];
    char filename[8];
    FILE *img = NULL;

    while (fread(buffer, 1, BLOCK_SIZE, raw_file) == BLOCK_SIZE)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // Close previous JPEG if one is open
            if (in_jpeg)
            {
                fclose(img);
            }
            sprintf(filename, "%03i.jpg", counter);
            counter++;
            img = fopen(filename, "wb");
            in_jpeg = 1;
        }

        // Write block if we're inside a JPEG
        if (in_jpeg)
        {
            fwrite(buffer, 1, BLOCK_SIZE, img);
        }
    }

    // Close the last JPEG if one is open
    if (in_jpeg)
    {
        fclose(img);
    }

    fclose(raw_file);
    return 0;
}