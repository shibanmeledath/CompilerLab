#include <stdio.h>
#include <stdlib.h>

#define MAX_STATES 10
#define MAX_SYMBOLS 10

int nfa[MAX_STATES][MAX_SYMBOLS][MAX_STATES];

void epsilonClosure(int state, int epsilonClosureSet[MAX_STATES], int n) {
    int i;
    epsilonClosureSet[state] = 1;

    for (i = 0; i < n; i++) {
        if (nfa[state][MAX_SYMBOLS - 1][i] == 1 && epsilonClosureSet[i] == 0) {
            epsilonClosure(i, epsilonClosureSet, n);
        }
    }
}

void addTransition(int nfa[MAX_STATES][MAX_SYMBOLS][MAX_STATES], int state, int symbol, int nextState) {
    nfa[state][symbol][nextState] = 1;
}

int main() {
    int n; // n: number of transitions
    printf("Enter the number of transitions: ");
    scanf("%d", &n);

    // Initialize NFA
    int i, j, k;
    for (i = 0; i < MAX_STATES; i++) {
        for (j = 0; j < MAX_SYMBOLS; j++) {
            for (k = 0; k < MAX_STATES; k++) {
                nfa[i][j][k] = 0;
            }
        }
    }

    // Input transitions and epsilon transitions
    printf("Enter transitions as state symbol state:\n");
    int state, symbol, nextState;
    for (i = 0; i < n; i++) {
        scanf("%d%d%d", &state, &symbol, &nextState);

        if (symbol == -1) {
            // Epsilon transition
            nfa[state][MAX_SYMBOLS - 1][nextState] = 1;
        } else {
            // Regular transition
            addTransition(nfa, state, symbol, nextState);
        }
    }

    // Display NFA transitions
    printf("\nNFA transitions:\n");
    for (i = 0; i < MAX_STATES; i++) {
        for (j = 0; j < MAX_SYMBOLS - 1; j++) {
            for (k = 0; k < MAX_STATES; k++) {
                if (nfa[i][j][k] == 1) {
                    printf("(%d, %d, %d)\n", i, j, k);
                }
            }
        }
    }

    // Display final states
    printf("\nFinal states:\n");
    int finalStates[MAX_STATES] = {0};
    for (i = 0; i < MAX_STATES; i++) {
        int epsilonClosureSet[MAX_STATES] = {0};
        epsilonClosure(i, epsilonClosureSet, MAX_STATES);

        for (j = 0; j < MAX_STATES; j++) {
            if (epsilonClosureSet[j] == 1) {
                finalStates[j] = 1;
            }
        }
    }

    for (i = 0; i < MAX_STATES; i++) {
        if (finalStates[i] == 1) {
            printf("%d ", i);
        }
    }

    return 0;
}
