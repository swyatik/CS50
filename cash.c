#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)

{
    float f;
    int change = 0, quarter = 0, dime = 0, nickel = 0, penny = 0;

        // get change owened
    f = get_float("Change owed: ");

         while (f <= 0)
    {
        f = get_float("Change owed: ");
    }

    change = roundf (f*100);

    if (change >= 25)
    {
        quarter = quarter + (change-change%25)/25;
        change = change%25;
    }

    if (change >= 10)
    {
        dime = dime + (change - change%10)/10;
        change = change%10;
    }

    if (change >= 5)
    {
        nickel = nickel + (change - change%5)/5;
        change = change%5;
    }

    penny = change;
    change = quarter + dime + nickel + penny;
    printf ("%i\n", change);
}
