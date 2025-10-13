#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
} candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);
void print_winner_bubble_sort(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    // print_winner();
    print_winner_bubble_sort();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // If name is in candidates[], update votes (++) and return true, else return false
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // print the name(s) of the candidate(s) with the most votes
    int greatest_number = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > greatest_number)
        {
            greatest_number = candidates[i].votes;
        }
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == greatest_number)
        {
            printf("%s\n", candidates[i].name);
        }
    }
}

// print the winner (or winners) of the election
void print_winner_bubble_sort(void)
{
    // Uses Bubble Sort algorithm to print the name(s) of the candidate(s) with the most votes
    int greatest_number = 0;
    string winners[MAX];
    int winners_count = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > greatest_number)
        {
            greatest_number = candidates[i].votes;
            winners[0] = "\0";
            winners[0] = candidates[i].name;
            winners_count = 1;
        }
        else if (candidates[i].votes == greatest_number)
        {
            winners_count++;
            winners[winners_count - 1] = candidates[i].name;
        }
    }

    for (int i = 0; i < winners_count; i++)
    {
        printf("%s\n", winners[i]);
    }
}
