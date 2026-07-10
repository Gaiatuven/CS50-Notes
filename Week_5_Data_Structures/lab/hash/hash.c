#include <stdio.h>
#include <string.h>
#include <ctype.h>


int hash(char* word);

int main(void)
{
    char sentence[100]; 

    printf("Enter a sentence: ");
    fgets(sentence, sizeof(sentence), stdin);

    sentence[strcspn(sentence, "\n")] = '\0';

    printf("Hash value: %i\n", hash(sentence));


    return 0;
}


int hash(char* word)
{
    if (word == NULL || strlen(word) == 0)
    {
        return -1;
    }

    char c = word[0];
    if (isalpha(c))
    {
        c = toupper(c);
        return c - 'A';
    }
    return 0;
}