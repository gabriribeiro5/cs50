#include <cs50.h>
#include <stdio.h>

void printdigit(string digit, int manytimes);

int main(void)
{
    int height;
    do
    {
        height = get_int(
            "You have initiated the Pyramd program. Please state the height of the pyramd: "
        );
    }
    while (height < 1 || height > 8);

    for (int row = 1; row <= height; row++)
        {
            printdigit(" ", height - row);
            printdigit("#", row);
            printdigit(" ", 2);
            printdigit("#", row);
            printf("\n");
        }
}


void printdigit(string digit, int manytimes)
{
    for (int i = 0; i < manytimes; i++)
    {
        printf("%s", digit);
    }
}
