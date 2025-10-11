#include <stdio.h>
#include <string.h>

#define DAYS 30   // Number of days in a month

// Define structure for Member
struct Member {
    char name[50];
    int steps[DAYS];
};

// Function to analyze step counts
void analyzeSteps(struct Member members[], int n) {
    for (int i = 0; i < n; i++) {
        int countAbove10k = 0;
        int maxSteps = members[i].steps[0];

        // Analyze each day
        for (int j = 0; j < DAYS; j++) {
            if (members[i].steps[j] > 10000)
                countAbove10k++;
            if (members[i].steps[j] > maxSteps)
                maxSteps = members[i].steps[j];
        }

        // Print result for this member
        printf("\nMember Name: %s\n", members[i].name);
        printf("Days with more than 10,000 steps: %d\n", countAbove10k);
        printf("Maximum step count in the month: %d\n", maxSteps);
    }
}

int main() {
    int n;
    printf("Enter number of members: ");
    scanf("%d", &n);

    struct Member members[n];

    // Input data for each member
    for (int i = 0; i < n; i++) {
        printf("\nEnter member name: ");
        scanf("%s", members[i].name);
        printf("Enter 30 daily step counts for %s:\n", members[i].name);

        for (int j = 0; j < DAYS; j++) {
            scanf("%d", &members[i].steps[j]);
        }
    }

    // Analyze all members
    analyzeSteps(members, n);

    return 0;
}
