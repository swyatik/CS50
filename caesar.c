#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, string argv[])
{
    // data entry check
    if (argc > 2 || argc == 1)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    int error = 0;
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (isalpha(argv[1][i]))
        {
            error++;
        }
    }
    if (error > 0)
    {
        printf("Usage: ./caesar key\n");
        return 2;
    }
    int argv1 = atoi(argv[1]);
    if (argv1 < 0 || argv1 > pow(2, 35) - 26)
    {
        printf("Key must be a non-negative integer than 0 and less than 2^31-26\n");
        return 3;
    }

    // key
    int k = argv1 % 26;

    // get text for encryption
    string text = get_string("plaintext: ");
    if (text == NULL)
    {
        return 1;
    }

    // encryption the text
    printf("ciphertext: ");
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isupper(text[i]))
        {
            int upper = 'A' + ((text[i] - 65) + k) % 26;
            printf("%c", (char)upper);
        }
        else if (islower(text[i]))
        {
            int lower = 'a' + ((text[i] - 97) + k) % 26;
            printf("%c", (char)lower);
        }
        else
        {
            printf("%c", text[i]);
        }
    }

    printf("\n");

    return 0;
}
