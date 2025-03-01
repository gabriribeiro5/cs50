#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string somename = get_string("You have initiated the Hello program. Please state your name: ");
    printf("hello, %s\n", somename);
}
