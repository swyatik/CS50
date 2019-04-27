#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    int invalid;
    string key;
    string text;
        // checking the number of arguments
    if (argc > 2 || argc ==1)
    {
        printf("Usage: ./vigenere keyword \n");
        return 1;
    }
        // checking the line item's alphabet
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (isalpha(argv[1][i]))
        {
            invalid = 0;
        }
        else
        {
            invalid = 1;
        }
    }
    if (invalid == 1)
    {
        printf ("Usage: ./vigenere keyword\n");
        return 1;
    }
        // get text for encryption
    else
    {
        text = get_string("plaintext: ");
    }

        // lengh string key
    key = argv[1];
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        key[i] = toupper(argv[1][i]);
    }
    int l_key = strlen(key);

        // encryption the text
    printf ("ciphertext: ");
    int index_k = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]))
        {
            if (isupper(text[i]))
            {
                int upper = 'A' + (((text[i] - 65) + (key[index_k%l_key] - 65))%26);
                printf ("%c", (char)upper);
                index_k++;
            }
            if (islower(text[i]))
            {
                int lower = 'a' + (((text[i] - 97) + (key[index_k%l_key] - 65))%26);
                printf ("%c", (char)lower);
                index_k++;
            }
        }
        else
        {
            printf ("%c", text[i]);
        }
    }
    printf ("\n");

    return 0;
}
