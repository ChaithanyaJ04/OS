#include <stdio.h>

#define MAX 10

int main() {
    int n, i, t = 0, hyper = 20; // simulate till time = 20

    int Ci[MAX], Di[MAX], Ti[MAX];
    int remaining[MAX], deadline[MAX];
    int next_arrival[MAX];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Input
    for (i = 0; i < n; i++) {
        printf("\nProcess P%d\n", i + 1);

        printf("Execution Time (Ci): ");
        scanf("%d", &Ci[i]);

        printf("Deadline (Di): ");
        scanf("%d", &Di[i]);

        printf("Period (Ti): ");
        scanf("%d", &Ti[i]);

        remaining[i] = 0;        // no job initially
        next_arrival[i] = 0;     // first arrival at time 0
        deadline[i] = 0;
    }

    printf("\nExecution Order:\n");

    // Run simulation
    while (t < hyper) {

        // Check for new arrivals
        for (i = 0; i < n; i++) {
            if (t == next_arrival[i]) {
                remaining[i] = Ci[i];                 // new job
                deadline[i] = t + Di[i];              // absolute deadline
                next_arrival[i] += Ti[i];             // next release
            }
        }

        int selected = -1;
        int min_deadline = 9999;

        // Select process with earliest deadline
        for (i = 0; i < n; i++) {
            if (remaining[i] > 0) {
                if (deadline[i] < min_deadline) {
                    min_deadline = deadline[i];
                    selected = i;
                }
            }
        }

        if (selected == -1) {
            printf("Time %d: Idle\n", t);
        } else {
            printf("Time %d: P%d\n", t, selected + 1);
            remaining[selected]--;
        }

        t++;
    }

    return 0;
}
