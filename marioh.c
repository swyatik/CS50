#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n;
        // Get Height
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);

    for (int i = 0; i < n; i++)
        {
                // print spaces
                int space = n - i - 1;
            for (int j = 0; j < space; j++)
            {
                printf (" ");
            }
                   // print hashes
                int hash = n - space;
            for (int h = 0; h < hash; h++)
            {
                printf ("#");
            }

            printf ("  "); // print two spaces

                // print hashes
            for (int h = 0; h < hash; h++)
            {
                printf ("#");
            }
                // print new line
            printf ("\n");

        }
}
