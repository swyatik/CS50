#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

int luhn(int card[], int n); // Luhn Algorithm

int main(void)
{
    long number, num, x; // number credit card
    int n = 1; // counter number of digits
    int *card; // array for number of digits
          // get number credit card
    number = get_long("Number: ");
    while (number < 0)
    {
        number = get_long("Number: ");
    }
    num = number;
        // counter the number of digits
    while ((num/=10) > 0)
    {
        n++;
    }
        // переставляємо цифри карти задом наперед для зручності
    num = number;
    x = 0;
    while (num > 0)
    {
        x = x * 10 + (num%10);
        num /= 10;
    }
        // виділяємо пам'ять під масив для номера карти для зручності обрахунку
    card = malloc(n * sizeof(int));
    num = x;
    if (n == 13 || n == 15 || n == 16)
    {
            // заносимо номер карти в масив
        for (int i = 0; i < n; i++)
        {
            card[i] = num%10;
            num /= 10;
        }
            // check credit card
        if (luhn(card, n) == 0)
        {
            if (card[0] == 4)
            {
                printf("VISA\n");
            }
            else if (card[0] == 3)
            {
                if (card[1] == 4 || card[1] == 7)
                {
                    printf("AMEX\n");
                }
                else
                {
                    printf("INVALID\n");
                }
            }
            else if (card[0] == 5)
            {
                if (card[1] == 1 || card[1] == 2 || card[1] == 3 || card[1] == 4 || card[1] == 5)
                {
                    printf("MASTERCARD\n");
                }
                else
                {
                    printf("INVALID\n");
                }
            }
            else
            {
                 printf ("INVALID\n");
            }
        }
        else
        {
            printf ("INVALID\n");
        }

    }
    else
    {
        printf ("INVALID\n");
    }
    free (card);
}

int luhn(int card[], int n)
{
    int l;
    int sum1 = 0;
    int sum2 = 0;
    if ((n%10)/2 == 3)
    {
        for (int i = 0; i < n + 1; i +=2)
        {
            if (card[i]*2 > 9)
            {
                sum1 += ((card[i]*2)%10 + (card[i]*2)/10);
            }
            else
            {
                sum1 += card[i]*2;
            }
        }
        for (int j = 1; j < n + 1; j +=2)
        {
            sum2 += card[j];
        }
    }
    else
    {
        for (int i = 1; i < n + 1; i +=2)
        {
            if (card[i]*2 > 9)
            {
                sum1 += ((card[i]*2)%10 + (card[i]*2)/10);
            }
            else
            {
                sum1 += card[i]*2;
            }
        }
        for (int j = 0; j < n + 1; j +=2)
        {
            sum2 += card[j];
        }
    }

    l = (sum1 + sum2)%10;
    return l;
}
