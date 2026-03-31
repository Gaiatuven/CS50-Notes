#include <stdio.h>


int main(void)
{
    struct election
    {
        char name[100];
        int number_of_election_votes;
    };

    struct election voter_one = {"Greg", 1000};
    printf("%s has %d votes.", voter_one.name, voter_one.number_of_election_votes);
    return 0;
    
}