#include <cs50.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

// variables
long card_number;
int card_number_lenght;
int *selected_digits;
int *unselected_digits;
int *selected_digits_multiplied;
string cc_flags[] = {"INVALID\n", "AMEX\n","MASTERCARD\n", "VISA\n"};
string card_flag;
struct Tuple splited_digits;
int selected_digits_sum;
int unselected_digits_sum;
struct Tuple {
    int *selected_dgts;
    int *unselected_dgts;
};

// helper function prototypes
int get_int_lenght(int some_int);
int get_long_lenght(long some_long);
bool card_number_can_be_handled(long card_number);
struct Tuple split_digits(long card_number);
int *multiply_digits(int selected_digits[]);
int sum_each_digit(int digits_list[]);
bool last_digit_is_zero(int number);
string find_flag(long card_number);
int get_first_2_digits(long input);

// main code
int main(void)
{
    do
    {
        card_number = get_long(
        "You have initiated the Credit Card Validation program. Please state a credit card number: "
        );
    }
    while(card_number_can_be_handled(card_number) == false);

    // Hans Peter Luhn’s Algorithm
    splited_digits = split_digits(card_number);
    selected_digits = splited_digits.selected_dgts;
    unselected_digits = splited_digits.unselected_dgts;
    selected_digits_multiplied = multiply_digits(selected_digits);
    selected_digits_sum = sum_each_digit(selected_digits_multiplied);
    unselected_digits_sum = sum_each_digit(unselected_digits);

    if(last_digit_is_zero(selected_digits_sum + unselected_digits_sum)) // card is valid
    {
        card_flag = find_flag(card_number);
        printf("%s\n", card_flag);
    }
    else
    {
        printf("%s\n", cc_flags[0]); // should be "INVALID\n"
    }
}

/////////////////////////////////
// helper functions assignment //
/////////////////////////////////

// main helper functions
int get_int_lenght(int some_int)
{
    int some_int_lenght;
    if(some_int != 0)
    {
        some_int_lenght = floor(log10(abs(some_int))) + 1;
    }
    else
    {
        some_int_lenght = 1;
    }

    return some_int_lenght;
}

int get_long_lenght(long some_long)
{
    int some_long_lenght;
    if(some_long != 0)
    {
        some_long_lenght = floor(log10(labs(some_long))) + 1;
    }
    else
    {
        some_long_lenght = 1;
    }

    return some_long_lenght;
}

bool card_number_can_be_handled(long c_number)
{
    bool is_valid = true;
    // Apply base validations such as data type, lenght and special characters
    card_number_lenght = get_long_lenght(c_number);

    if(card_number_lenght < 13 || card_number_lenght > 16)
    {
        is_valid = false;
    }

    return is_valid;
}

struct Tuple split_digits(long c_number)
{
    // Get every other digit, starting with the number’s second-to-last digit.
        // Exemple:
        //     Given number     - 4 0 0 3 6 0 0 0 0 0 0 0 0 0 1 4
        //     Selecting nums   - ^  ^   ^   ^   ^   ^   ^   ^
        //     Selected nums    - 4  0   6   0   0   0   0   1
        //     Unselected nums  -   0   3   0   0   0   0   0  4

    card_number_lenght = get_long_lenght(c_number);

    last_digit = number % 10;
    bool select_next = false;
    for(int i = 0; i < card_number_lenght; i++)
    {
        if(select_next)
        {
            selected_digits[i] = c_number % 10; // get c_number last digit
            c_number = c_number / 10; // remove collected digit for next loop
            select_next = false;
        }
        else
        {
            unselected_digits[i] = card_number[i];
            c_number = c_number / 10; // remove collected digit for next loop
            select_next = true;
        }
    }

    struct Tuple splited_digits = {selected_digits, unselected_digits}

    return splited_digits;
}

int multiply_digits(selected_digits)
{
    // following Luhn’s Algorithm
    // multiply each of the selected digits by 2


    selected_digits_lenght = get_number_lenght(selected_digits);

    int multiplied_digits[];

    for(i = 0; i < selected_digits_lenght; i++)
    {
        multiplied_digits[i] = selected_digits[i] * 2
    }

    return multiplied_digits;
}

int sum_each_digit(digits_list)
{
    // sum the digits of each item in the given list

    digits_list_lenght = get_number_lenght(digits_list);

    int digits_sum = 0;

    for(item_index = 0; item_index < digits_list_lenght; i++)
    {
        int item = digits_list[item_index]

        int item_lenght = get_number_lenght(item)

        for(digit = 0; digit < item_lenght; i++)
        {
            digits_sum = digits_sum + item[digit]
        }

        return digits_sum
    }
}

bool last_digit_is_zero(int number)
{
    last_digit = number % 10;

    if (last_digit != 0)
    {
        return false
    }

    return true
}

string find_flag(card_number)
{
    // 1 - Amex: 15 digits       | starts with: 34 or 37
    // 2 - Master: 16 digits     | starts with: 51, 32, 53, 54 or 55
    // 3 - Visa: 13 or 16 digits | starts with: 4

    card_number_lenght = get_number_lenght(card_number);
    first_two = get_first_2_digits(card_number);
    first_digit = get_first_digit(card_number);

    switch(card_number_lenght)
    {
        case 16:
            if(first_digit == 4)
            {
                printf("%s", cc_flags[3]); // VISA
            }
            else if(first_two > 50 && first_two < 56)
            {
                printf("%s", cc_flags[2]); // MASTER
            }
            else
            {
                printf("number has 16 digits but isnt VISA or MASTER");
            }
            break;
        case 15:
            if(first_two == 34 || first_two == 37)
            {
                printf("%s", cc_flags[1]); // AMEX
            }
            else
            {
                printf("number has 15 digits but isnt AMEX");
            }
            break;
        case 13:
            if(first_digit == 4)
            {
                printf("%s", cc_flags[3]); // VISA
            }
            else
            {
                printf("number has 13 digits but isnt VISA");
            }
            break;
        default:
            printf("unexpected number of digits: %li\n", card_number_lenght);
            break;
    }
}


// "don't repeat yourself" functions
int get_first_2_digits(long input)
{
    long local = input;

    while (local >= 100)
    {
        local /= 10;
    }

    return local;
}

int get_first_digit(long input)
{
    long local = input;

    while (local >= 10)
    {
        local /= 10;
    }

    return local;
}
