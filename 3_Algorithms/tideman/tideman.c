#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void sort_pairs_recursivelly_2(void);
void merge_sort(pair array[], int lenght);
void merge_sort_recursion(pair array[], int left, int right);
void merge_sorted_arrays(pair array[], int left, int middle, int right);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs_recursivelly_2();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    /* TODO
    - If name is a valid candidate, update the ranks array
    - return true if the rank was successfully recorded,
    - return false otherwise
    */
    for (int c = 0; c < candidate_count; c++)
    {
        if (strcmp(name, candidates[c]) == 0)
        {
            ranks[rank] = c;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    /*
        Use ranks to update the global preferences array to add the current voter’s preferences
    */
    for (int prefered_candidate = 0; prefered_candidate < candidate_count-1; prefered_candidate++) {
        for (int other_candidate = prefered_candidate+1; other_candidate < candidate_count; other_candidate++) {
            preferences[ranks[prefered_candidate]][ranks[other_candidate]]++;
        }
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    /*
        Add all pairs of candidates where one candidate is preferred to the pairs array.
            A pair of candidates who are tied (one is not preferred over the other) should not be added to the array.
        Update the global variable pair_count to be the number of pairs of candidates. (The pairs should thus all be stored between pairs[0] and pairs[pair_count - 1], inclusive).
    */
    pair new_pair;
    for (int candidate_a = 0; candidate_a < candidate_count; candidate_a++)
    {
        for (int candidate_b = 0; candidate_b < candidate_count; candidate_b++)
        {
            int p = preferences[candidate_a][candidate_b] - preferences[candidate_b][candidate_a]; // compare opposite pairs
            if (p > 0) // candidate_a wins
            {
                // Add pair
                new_pair.winner = candidate_a;
                new_pair.loser = candidate_b;
                pairs[pair_count] = new_pair;
                pair_count++;
            }
            else if (p < 0) // candidate_b wins
            {
                // Add pair
                new_pair.winner = candidate_b;
                new_pair.loser = candidate_a;
                pairs[pair_count] = new_pair;
                pair_count++;
            }
        }
    }
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    /*
        Sort the pairs array in decreasing order of strength of victory,
            where strength of victory is defined to be the number of voters who prefer the preferred candidate.
        If multiple pairs have the same strength of victory, you may assume that the order does not matter.
        hint:
            pair pairs[36];
    */
    // int n = pairs[a].winner - pairs[b].winner;
    // int no_chage = 0;
    // do
    // {
    //     if (n > 0) // pair B wins
    //     {
    //         no_change++;
    //     }
    //     else if (n < 0) // pair B wins
    //     {
    //         pair winner = pairs[b];
    //         pairs[b] = pairs[a];
    //         pairs[a] = winner;
    //         no_change = 0;
    //     }
    // } while {no_change < (pair_count / 2)}

    // for (p = 0; p > pair_count; p++)
    // {
    //     int highest_number = 0;
    //     if (pairs[p].winner >= highest_number)
    //     {
    //         for (relocated_pair = pair_count-1; relocated_pair > 0; relocated_pair--)
    //         {
    //             pairs[relocated_pair+1] = pairs[relocated_pair];
    //         }
    //         pairs[0] = pairs[p];
    //         highest_number = pairs[p].winner;
    //     }

    // }
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs_recursivelly_2(void)
{
    /*
        Sort the pairs array in decreasing order of strength of victory,
            where strength of victory is defined to be the number of voters who prefer the preferred candidate.
        If multiple pairs have the same strength of victory, you may assume that the order does not matter.
        hint:
            pair pairs[36];
    */

    merge_sort(pairs, pair_count);

    for (int i = 0; i < pair_count; i++)
        {
            printf("%d", pairs[i].winner);
        }
    printf("\n");
}

void merge_sort(pair array[], int lenght)
{
    merge_sort_recursion(array, 0, lenght -1);
}

void merge_sort_recursion(pair array[], int left_index, int right_index)
{
    // Stop recursion
    // Sort left and right portions of the array
    if (left_index < right_index)
    {
        int middle_index = left_index + (right_index - left_index) / 2;

        merge_sort_recursion(array, left_index, middle_index);
        merge_sort_recursion(array, middle_index+1, right_index);

        merge_sorted_arrays(array, left_index, middle_index, right_index);
    }
}

void merge_sorted_arrays(pair array[], int left, int middle, int right)
{
    // Create resources
    int left_lenght = middle - left + 1;
    int right_lenght = right - middle;

    pair temp_left[left_lenght];
    pair temp_right[right_lenght];

    int left_index, array_index, right_index;

    // Go through LEFT array
    for (int i = 0; i < left_lenght; i++)
    {
        temp_left[i].winner = array[left + i].winner;
        temp_left[i].loser = array[left + i].loser;
    }

    // Go through RIGHT array
    for (int i = 0; i < right_lenght; i++)
    {
        temp_right[i].winner = array[middle + 1 + i].winner;
        temp_left[i].loser = array[middle + 1 + i].loser;
    }

    /* MERGE SORTED SUBARRAYS

                         index:    i
                     temp_left: 4, 9, 12

                         index: j
                    temp_right: 5, 8, 14

                         index:   k
                        array: 4, 5
    */
    for (left_index = 0, right_index = 0, array_index = left; array_index <= right; array_index++)
    {
        if ((left_index < left_lenght) &&
            (right_index >= right_lenght || temp_left[left_index].winner <= temp_right[right_index].winner))

        {
            array[array_index].winner = temp_left[left_index].winner;
            array[array_index].loser = temp_left[left_index].loser;
            left_index++;
        }
        else
        {
            array[array_index].winner = temp_right[right_index].winner;
            array[array_index].loser = temp_right[right_index].loser;
            right_index++;
        }
    }
}

// Sort pairs in decreasing order by strength of victory
// void sort_pairs_recursivelly(void)
// {
//     /*
//         Sort the pairs array in decreasing order of strength of victory,
//             where strength of victory is defined to be the number of voters who prefer the preferred candidate.
//         If multiple pairs have the same strength of victory, you may assume that the order does not matter.
//         hint:
//             pair pairs[36];
//     */
//     // Merge sort using recursive function:
//     // solve left
//     // solve right
//     // merge solutions
//     int left_chunk[pair_count];
//     int right_chunk[pair_count];
//     void merge_sort(int array_chunk[]; int array_count)
//     {
//         if (array_count % 2 == 0) // is even (é par), not odd ;)
//         {
//             int new_array_count = array_count / 2;
//             int right_index = 0;
//             for (i = 0; i < array_count; i++)
//             {
//                 if (i < new_array_count)
//                 {
//                     left_chunk[i] = pairs[i];
//                 }
//                 else if (i >= new_array_count)
//                 {
//                     right_chunk[new_array_count + right_index] = pairs[i];
//                     right_index++;
//                 }
//             }

//             // Double recursion
//             int left_chunk_sorted[] = merge_sort(left_chunk, new_array_count); // merge left
//             int right_chunk_sorted[] = merge_sort(right_chunk, new_array_count); // merge right

//             // Sort even arrays
//             int left_chunk_sorted_returnable[] = selection_sort(left_chunk; array_count);
//             int right_chunk_sorted_returnable[] = selection_sort(left_chunk; array_count);

//             // Merge left and right


//         }
//         else // is odd
//         {
//             return selection_sort(array_chunk; array_count);
//         }
//     }

//     merge_sort(pairs[]; pair_count);
// }

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    /*
        Create the locked graph, adding all edges in decreasing order of victory strength so long as the edge would not create a cycle.
        hint:
            // locked[i][j] means i is locked in over j
            bool locked[MAX][MAX];
    */
    int winner_list[pair_count];
    int winner_list_count = 0;
    bool end_locking = false;
    for(int p = 0; p < pair_count; p++)
    {
        for(int w = 0; w < pair_count; w++)
        {
            if (pairs[p].winner == winner_list[w])
            {
                end_locking = true;
            }
        }
        if (end_locking)
        {
            break;
        }

        locked[pairs[p].winner][pairs[p].loser] = true;
        winner_list[winner_list_count] = pairs[p].winner;
    }
}

// Print the winner of the election
void print_winner(void)
{
    // Print out the name of the candidate who is the source of the graph. You may assume there will not be more than one source.
    int winner = 0;
    int losers[pair_count];
    int loser_count = 0;
    for(int w = 0; w < pair_count; w++)
    {
        for(int l = 0; l < pair_count; l++)
        {
            if (locked[w][l])
            {
                losers[l] = pairs[l].loser;
                loser_count++;
                for (int lsr = 0; lsr < pair_count; lsr++)
                {
                    if (pairs[w].winner == losers[lsr])
                    {
                        break;
                    }
                    winner = pairs[w].winner;
                }
            }
        }
    }
    printf("%s", candidates[winner]);
}
