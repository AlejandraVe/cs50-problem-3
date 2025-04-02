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
void print_winner();

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
    print_winner();
    return (0);
}

// Update vote totals given a new vote
bool vote(string name)
{
    int i = 0;

    if (!name)
        return false;
    while (i < candidate_count)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
        i++;
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner() // voter_count is the amount of votes
{
    int highest_votes;

    for (int i = 0; i < candidate_count; i++)
    {
        int j = 1;
        if (candidates[i].votes < candidates[i + j].votes && candidates[i + j].votes)
            highest_votes = candidates[i + j].votes;
        else if (candidates[i].votes > candidates[i + j].votes && candidates[i + j].votes)
        {
            while (candidates[i].votes > candidates[i + j].votes && candidates[i + j].votes)
            {
                highest_votes = candidates[i].votes;
                j++;
            }
        }
        else
        {
            highest_votes = candidates[i].votes;
            break;
        }
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > highest_votes)
            highest_votes = candidates[i].votes;
    }
    for (int n = 0; n < candidate_count; n++)
    {
        if (highest_votes == candidates[n].votes)
            printf("%s\n", candidates[n].name);
    }
}
