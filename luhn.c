#include <stdio.h>

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
