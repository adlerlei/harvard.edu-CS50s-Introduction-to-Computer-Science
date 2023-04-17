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
    // 遍歷候選列表名單
    for (int i = 0; i < candidate_count; i++)
    {
        // 找到給定名稱候選人
        if (strcmp(candidates[i].name, name) == 0)
        {
            // 更新數組
            preferences[voter][rank] = i;
            return true;
        }
    }
    // 如果沒有找到給定名稱候選人則投票無效
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // 清除候選人投票數
    for (int k = 0; k < candidate_count; k++)
    {
        candidates[k].votes = 0;
    }
    // 遍歷每個選民，對每個選民考慮順位
    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            // 獲得排名編號索引
            int candidate_index = preferences[i][j];

            // 是否有排名編號候選人為淘汰
            if (!candidates[candidate_index].eliminated)
            {
                candidates[candidate_index].votes++;
                break;
            }
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // 遍歷所有候選人
    for (int i = 0; i < candidate_count; i++)
    {
        // If a candidate has more than half of the votes, they win
        if (candidates[i].votes > voter_count / 2)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    // 如果沒有人獲勝返回false
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // 將 min_votes 初始化
    int min_votes = voter_count;
    // 遍歷所有候選人
    for (int i = 0; i < candidate_count; i++)
    {
        // 如果候選人沒有被淘汰並且得票數少於當前最小值則更新最小值
        if (!candidates[i].eliminated && candidates[i].votes < min_votes)
        {
            min_votes = candidates[i].votes;
        }
    }
    return min_votes;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // 遍歷所有候選人
    for (int i = 0; i < candidate_count; i++)
    {
        // 如果候選人沒有被淘汰並且得票數與最小值不同，則返回false
        if (!candidates[i].eliminated && candidates[i].votes != min)
        {
            return false;
        }
    }
    // 如果所有未被淘汰的候選人的票數相同，則返回 true
    return true;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // 遍歷所有候選人
    for (int i = 0; i < candidate_count; i++)
    {
        // 如果候選人的票數最少，則將其淘汰
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
    return;
}