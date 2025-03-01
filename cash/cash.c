#include <cs50.h>
#include <stdio.h>


int main()
{
    // a program in C that prints the minimum coins needed to make the given amount of change, in cents
    int change_in_cents = 0;
    int available_coins[] = {25, 10, 5, 1};
    int runtime_sum = 0;
    int coins_count = 0;
    do
    {
        change_in_cents = get_int(
        "You have initiated the Minimum Coins program. Please state an amount of change in cents: "
        );
    }
    while(change_in_cents < 0);

    if(change_in_cents > 0)
    {
        // find out how many elements the array `available_coins` has
        int available_coins_length = sizeof(available_coins) / sizeof(available_coins[0]);

        // count the minimum coins needed to match `change_in_cents`
        while(runtime_sum != change_in_cents)
        {
            for(int i = 0; i < available_coins_length; i++)
            {
                if(available_coins[i] <= change_in_cents)
                {
                    do
                    {
                        runtime_sum = runtime_sum + available_coins[i];
                        coins_count++;
                    }
                    while(runtime_sum < change_in_cents);

                    if(runtime_sum > change_in_cents)
                    {
                        // undo last sum
                        runtime_sum = runtime_sum - available_coins[i];
                        coins_count--;
                    }
                }
            }
        }

        // print result
        printf("%i\n", coins_count);
    }
}
