#include<stdio.h>
#include <stdlib.h>
#include <crypt.h>
#include <string.h>
#include <sys/resource.h>
#include <sys/time.h>

#define LETTER 53

// Prototype
double calculate(const struct rusage *b, const struct rusage *a);

int main(int argc, char *argv[])
{
     // Structures for timing data
    struct rusage before, after;
    double time_key = 0;

    if (argc != 2)
    {
        printf("Usage: ./crack list.txt\n");
        return 1;
    }
    char *f = argv[1];
    FILE *file = fopen(f, "r");
    if (file == NULL)
    {
        printf("Error opening file\n");
        return 2;
    }
    // Buffer for a hash key
    char *hash = malloc(sizeof(char));
    if (!hash)
    {
        return 3;
    }
    int amount_key = 0;
    char salt[3];
    salt[2] = '\0';

    // hash without name
    char without_name[14];
    without_name[13] = '\0';

    // arrey for letter from 'A' to 'z'
    char letter[LETTER];
    char low = 'a';
    char up = 'A';
    letter[LETTER - 1] = '\0';
    for (int i = 0; i < LETTER - 1; i++)
    {
        if (i < 26)
        {
            letter[i] = up + i;
        }
        else
        {
            letter[i] = low + (i - 25);
        }
    }
    // key predicted
    char key[6] = "\0\0\0\0\0\0";
    // number key
    int amount = 1;

    while (fscanf(file, "%s", hash) != EOF)
    {
        char *name = malloc(sizeof(char));
        if (!name)
        {
            return 4;
        }
        getrusage(RUSAGE_SELF, &before);
        int str_cmp = 1;
        // кількість ітерацій
        unsigned long long x = 0;

        int n = strlen(hash);
        for (int i = 0; i < n; i++)
        {
            if (hash[i] == ':')
            {
                // write salt
                salt[0] = hash[i + 1];
                salt[1] = hash[i + 2];
                // write hash without name
                for (int j = i + 1; j < n; j++)
                {
                    without_name[j - (i + 1)] = hash[j];
                }
                // write name
                for (int k = 0; k < n - (n - i); k++)
                {
                    name[k] = hash[k];
                }
                amount_key++;
                break;
            }
        }
        for (int fifth = 0; fifth < LETTER; fifth++)
        {
            for (int fourth = 0; fourth < LETTER; fourth++)
            {
                for (int tird = 0; tird < LETTER; tird++)
                {
                    for (int second = 0; second < LETTER; second++)
                    {
                        for (int first = 0; first < LETTER; first++)
                        {
                            key[0] = letter[first];
                            key[1] = letter[second];
                            key[2] = letter[tird];
                            key[3] = letter[fourth];
                            key[4] = letter[fifth];
                            x++;
                            if (strcmp(without_name, crypt(key, salt)) == 0)
                            {
                                getrusage(RUSAGE_SELF, &after);
                                time_key = calculate(&before, &after);
                                str_cmp = 0;
                                printf("%i. name: %s; password: %s; time: %2.2f; iteration: %lli\n", amount, name, key, time_key, x);
                                amount++;
                                break;
                            }
                        }
                        x++;
                        if (str_cmp == 0)
                        {
                            break;
                        }
                    }
                    x++;
                    if (str_cmp == 0)
                    {
                        break;
                    }
                }
                x++;
                if (str_cmp == 0)
                {
                    break;
                }
            }
            x++;
            if (str_cmp == 0)
            {
                break;
            }
        }
        if (str_cmp == 1)
        {
            printf("Password %i couldn't be cracked!\n", amount);
        }
        free(name);
    }


    free(hash);
    fclose(file);
    return 0;
}



// Returns number of seconds between b and a
double calculate(const struct rusage *b, const struct rusage *a)
{
    if (b == NULL || a == NULL)
    {
        return 0.0;
    }
    else
    {
        return ((((a->ru_utime.tv_sec * 1000000 + a->ru_utime.tv_usec) -
                  (b->ru_utime.tv_sec * 1000000 + b->ru_utime.tv_usec)) +
                 ((a->ru_stime.tv_sec * 1000000 + a->ru_stime.tv_usec) -
                  (b->ru_stime.tv_sec * 1000000 + b->ru_stime.tv_usec)))
                / 1000000.0);
    }
}
