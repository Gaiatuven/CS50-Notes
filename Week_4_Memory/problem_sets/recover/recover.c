#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> // Needed for uint8_t

// Define the block size for memory cards
#define BLOCK_SIZE 512

int main(int argc, char *argv[])
{
    // 1. Check for exactly 2 arguments
    if (argc != 2)
    {
        printf("Usage: ./recover card.raw\n");
        return 1;
    }

    // 2. Open the memory card in binary read mode
    FILE *input = fopen(argv[1], "rb");
    if (input == NULL)
    {
        printf("Could not open file %s.\n", argv[1]);
        return 1;
    }

    // Buffer to store a 512-byte block of data
    uint8_t buffer[BLOCK_SIZE];

    // 3. Read 512-byte chunks at a time until the end of the file
    while (fread(buffer, 1, BLOCK_SIZE, input) == BLOCK_SIZE)
    {
        // TODO: Look for JPEG signatures and write blocks to output files
    }

    // 4. Close the input file
    fclose(input);
    return 0;
}
