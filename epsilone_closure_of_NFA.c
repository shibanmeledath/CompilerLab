#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_STATES 100

// Structure to represent a state in the NFA
struct State {
    int id;
    bool isFinal;
    int epsilonTransitions[MAX_STATES];
    int numEpsilonTransitions;
};

// Function to compute the epsilon closure of a state
void computeEpsilonClosure(struct State nfa[], int currentState, bool visited[]) {
    if (visited[currentState]) {
        return;
    }

    visited[currentState] = true;
    printf("%d ", currentState);

    for (int i = 0; i < nfa[currentState].numEpsilonTransitions; i++) {
        computeEpsilonClosure(nfa, nfa[currentState].epsilonTransitions[i], visited);
    }
}

int main() {
    int numStates, numTransitions;
    printf("Enter the number of states: ");
    scanf("%d", &numStates);

    struct State nfa[numStates];

    // Initialize states
    for (int i = 0; i < numStates; i++) {
        nfa[i].id = i;
        nfa[i].isFinal = false;
        nfa[i].numEpsilonTransitions = 0;
    }

    printf("Enter the number of epsilon transitions: ");
    scanf("%d", &numTransitions);

    // Input epsilon transitions
    printf("Enter epsilon transitions (state1 state2):\n");
    for (int i = 0; i < numTransitions; i++) {
        int state1, state2;
        scanf("%d %d", &state1, &state2);
        nfa[state1].epsilonTransitions[nfa[state1].numEpsilonTransitions++] = state2;
    }

    // Compute epsilon closure for each state
    printf("Epsilon Closures:\n");
    for (int i = 0; i < numStates; i++) {
        bool visited[MAX_STATES] = {false};
        printf("Epsilon Closure of State %d: ", i);
        computeEpsilonClosure(nfa, i, visited);
        printf("\n");
    }

    return 0;
}
