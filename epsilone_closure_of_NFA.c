#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_STATES 100

// Function to compute the epsilon closure of a state
void computeEpsilonClosure(int nfa[][MAX_STATES], int currentState, bool visited[]) {
    if (visited[currentState]) {
        return;
    }

    visited[currentState] = true;
    printf("Q%d ", currentState);

    for (int i = 1; i <= nfa[currentState][0]; i++) {
        computeEpsilonClosure(nfa, nfa[currentState][i], visited);
    }
}

int main() {
    int numStates, numTransitions;
    printf("Enter the number of states: ");
    scanf("%d", &numStates);

    int nfa[numStates][MAX_STATES];

    // Initialize states
    for (int i = 0; i < numStates; i++) {
        nfa[i][0] = 0; // Number of epsilon transitions
    }

    // Print the states
    printf("----STATES----\n");
    for (int i = 0; i < numStates; i++) {
        printf("Q%d,", i);
    }
    printf("\n--------------\n");

    // Input epsilon transitions
    printf("Enter the number of epsilon transitions: ");
    scanf("%d", &numTransitions);
    printf("Enter epsilon transitions (state1 state2):\n");
    for (int i = 0; i < numTransitions; i++) {
        int state1, state2;
        printf("Transition %d: ", i + 1);
        scanf("%d %d", &state1, &state2);

        // Store epsilon transitions in the array
        nfa[state1][++nfa[state1][0]] = state2;
    }

    // Compute epsilon closure for each state
    printf("Epsilon Closures:\n");
    for (int i = 0; i < numStates; i++) {
        bool visited[MAX_STATES] = {false};
        printf("Epsilon Closure of State Q%d: ", i);
        computeEpsilonClosure(nfa, i, visited);
        printf("\n");
    }

    return 0;
}
