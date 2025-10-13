#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
} candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    /* TODO
    - Look for a candidate called `name`
    - If found, update preferences and return `true`
    - Else, return false
    */

    // If name is in candidates[], update votes (++) and return true, else return false
    for (int c = 0; c < candidate_count; c++)
    {
        if (strcmp(name, candidates[c].name) == 0)
        {
            preferences[voter][rank] = c;
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    /* TODO
    - Update vote counts for all non-eliminated candidates
    */
    for (int voter = 0; voter < voter_count; voter++)
    {
        for (int rank = 0; rank < MAX_CANDIDATES; rank++)
        {
            if (!candidates[preferences[voter][rank]].eliminated)
            {
                candidates[preferences[voter][rank]].votes++;
                break;
            }
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    /* TODO
    - If any candidate has more than half of the vote,
     their name should be printed and the function should return true.
    - If nobody has won the election yet, the function should return false
    */
    for (int c = 0; c < candidate_count; c++)
    {
        if (candidates[c].votes > voter_count / 2)
        {
            printf("%s\n", candidates[c].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    /* TODO
    - Return the minimum vote total for any candidate who is still in the election.
    */
    int min = MAX_VOTERS;
    bool non_eligible_candidates = true;
    for (int c = 0; c < candidate_count; c++)
    {
        if (!candidates[c].eliminated)
        {
            non_eligible_candidates = false;
            if (candidates[c].votes < min)
            {
                min = candidates[c].votes;
            }
        }
    }

    if (non_eligible_candidates)
    {
        return 0;
    }

    return min;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    /* TODO
    - Return true if every candidate remaining in the election has the same number of votes
    - Return false otherwise.
    */
    int previous_vote = candidates[0].votes;
    for (int c = 1; c < candidate_count; c++)
    {
        if (!candidates[c].eliminated)
        {
            if (candidates[c].votes == previous_vote)
            {
                previous_vote = candidates[c].votes;
            }
            else
            {
                return false;
            }
        }
    }
    return true;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    /* TODO
    - eliminate the candidate (or candidates) who have min number of votes
    */
    for (int c = 0; c < candidate_count; c++)
    {
        if (candidates[c].votes == min)
        {
            candidates[c].eliminated = true;
        }
    }
}
