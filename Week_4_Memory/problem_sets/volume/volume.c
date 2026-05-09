#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    FILE *input = fopen(argv[1], "rb");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "wb");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        fclose(input);
        return 1;
    }

    float factor = atof(argv[3]);

    // Copy header from input file to output file
    uint8_t header[HEADER_SIZE];
    fread(header, HEADER_SIZE, 1, input);
    fwrite(header, HEADER_SIZE, 1, output);

    // Read samples, scale, clamp, and write
    int16_t buffer;
    while (fread(&buffer, sizeof(int16_t), 1, input))
    {
        int32_t scaled = (int32_t)(buffer * factor);
        if      (scaled >  32767) scaled =  32767;
        else if (scaled < -32768) scaled = -32768;
        buffer = (int16_t)scaled;
        fwrite(&buffer, sizeof(int16_t), 1, output);
    }

    fclose(input);
    fclose(output);
}
