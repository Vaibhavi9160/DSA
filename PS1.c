#include <stdio.h>
#include <string.h>

#define MAX 50

void searchWord(char grid[MAX][MAX], int m, int n, char word[]) {
    int len = strlen(word);
    int found = 0;

    // Horizontal search (left to right)
    for (int i = 0; i < m; i++) {
        for (int j = 0; j <= n - len; j++) {
            int k;
            for (k = 0; k < len; k++) {
                if (grid[i][j + k] != word[k])
                    break;
            }
            if (k == len) {
                printf("Start: (%d, %d) End: (%d, %d)\n", i, j, i, j + len - 1);
                found = 1;
            }
        }
    }

    // Vertical search (top to bottom)
    for (int i = 0; i <= m - len; i++) {
        for (int j = 0; j < n; j++) {
            int k;
            for (k = 0; k < len; k++) {
                if (grid[i + k][j] != word[k])
                    break;
            }
            if (k == len) {
                printf("Start: (%d, %d) End: (%d, %d)\n", i, j, i + len - 1, j);
                found = 1;
            }
        }
    }

    if (!found)
        printf("Word not found\n");
}

int main() {
    // Hardcoded grid containing the word "VAIBH" both horizontally and vertically
    int m = 6, n = 6;
    char grid[MAX][MAX] = {
        {'V', 'A', 'I', 'B', 'H', 'X'},
        {'A', 'B', 'C', 'D', 'E', 'F'},
        {'I', 'V', 'A', 'I', 'B', 'H'},
        {'B', 'A', 'I', 'B', 'H', 'Y'},
        {'H', 'A', 'I', 'B', 'H', 'Z'},
        {'V', 'A', 'I', 'B', 'H', 'Z'}
    };

    char word[MAX] = "VAIBH";  // 🔍 target word (your name)

    printf("Grid:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%c ", grid[i][j]);
        }
        printf("\n");
    }

    printf("\nSearching for word: %s\n", word);
    searchWord(grid, m, n, word);

    return 0;
}
