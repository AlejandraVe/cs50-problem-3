#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i. Here its preferences[the voter][the candidate
// they prefer]
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
        return 3; // the 3 is just ecause this is the number set for this type of error
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);
            // the vote function is called to keep track of all of the preferences
            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }
    // preferences[i][j] has stored the preferences of each voter
    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();
        // Now the votes of each candidates are stored in their struct

        // Check if election has been won; prints out the winner if so
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
// preferences[i][j] is jth preference for voter i. Here its preferences[the voter][the candidate
// they prefer]
bool vote(int voter, int rank,
          string name) // i = the voter, j = their first choice, name: name of the candidate
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates; Calculate votes given remaining candidates
void tabulate(void)
{
    int n = 0;
    int found = 0;

    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            n = 0;
            if (preferences[i][n] == j && (candidates[j].eliminated == false))
                candidates[j].votes++;
            if (preferences[i][n] == j && (candidates[j].eliminated == true))
            {
                found = 0;
                for (int o = 1; o < candidate_count; o++)
                {
                    n = 0;
                    while (n < candidate_count)
                    {
                        if (preferences[i][o] == n && (candidates[n].eliminated == false))
                        {
                            candidates[n].votes++;
                            found = 1;
                            break;
                        }
                        n++;
                    }
                    if (found == 1)
                        break;
                }
            }
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    int highest_vote = 0;
    string temp;

    // printf("%d %d\n", candidates[0].votes, candidates[0 + 1].votes);

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > highest_vote && (candidates[i].eliminated == false))
        {
            highest_vote = candidates[i].votes;
            temp = candidates[i].name;
        }
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (highest_vote == candidates[i].votes && (strcmp(candidates[i].name, temp) != 0) &&
            (candidates[i].eliminated == false))
            return false;
    }
    if (highest_vote > (voter_count / 2))
    {
        printf("Winner: %s\n", temp);
        return true;
    }
    else
    {
        return false;
    }
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int min_vote = voter_count;

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes <= min_vote && (candidates[i].eliminated == false))
        {
            min_vote = candidates[i].votes;
            if (candidates[i].votes < min_vote)
            {
                min_vote = candidates[i].votes;
            }
        }
    }
    return (min_vote);
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    int eliminated = 0;
    int j = 0;

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == true)
            eliminated++;
        if (candidates[i].votes == min && (candidates[i].eliminated == false))
            j++;
    }
    if (j == (candidate_count - eliminated))
        return true;
    else
        return false;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (min == candidates[i].votes && (candidates[i].eliminated == false))
        {
            candidates[i].eliminated = true;
        }
    }
    return;
}
