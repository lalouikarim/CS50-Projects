#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
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
}
candidate;

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
    // TODO
    for(int i=0;i<candidate_count;i++)
    {
        if(strcmp(candidates[i].name,name)==0)
        {
            preferences[voter][rank]=i;
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // TODO
    int k;
    int j;
    for(int i=0;i<voter_count;i++)
    {
        j=0;
        while(j<candidate_count)
        {
            k=preferences[i][j];
            if(!candidates[k].eliminated)
            {
                candidates[k].votes=candidates[k].votes+1;
                j=j+1;
                break;
            }
            else
            {
                j=j+1;
            }
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // TODO
    float needed_voters;
    int needed_voters_i;
    needed_voters=voter_count/2;
    needed_voters_i=round(needed_voters);
    for(int i=0;i<candidate_count;i++)
    {
        if(candidates[i].votes>needed_voters_i)
        {
            printf("%s\n",candidates[i].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // TODO
    int i=0;
    int min_c=candidates[i].votes;
    if(candidates[i].eliminated)
    {
        i=i+1;
    }
    int j=0;
    while(j<candidate_count)
    {
        if(j==i)
        {
             j=j+1;
        }
        else
        {
             if(!candidates[j].eliminated)
             {
                  if(candidates[j].votes<min_c)
                  {
                        min_c=candidates[j].votes;
                  }
             }
             j=j+1;
        }
    }

    return min_c;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // TODO
    bool f=true;
    int i=0;
    if(candidates[i].votes==min)
    {
        i=i+1;
    }
    int j=0;
    while(j<candidate_count)
    {
        if(j==i)
        {
             j=j+1;
        }
        else
        {
             if(candidates[j].votes<min)
             {
                  j=j+1;
             }
             else
             {
                  if(candidates[i].votes==candidates[j].votes)
                  {
                       f=true;
                       j=j+1;
                       return f;
                  }
                  else
                  {
                        f=false;
                        return f;
                        break;
                  }
            }
       }
    }
    return false;
}

// Eliminate the candidate (or candidiates) in last place
void eliminate(int min)
{
    // TODO
    for(int i=0;i<candidate_count;i++)
    {
        if(candidates[i].votes==min)
        {
            candidates[i].eliminated=true;
        }
    }
    return;
}
