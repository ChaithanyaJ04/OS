#include <stdio.h>

int main() {
    int n, i, t = 0, completed = 0;
    int at[10], bt[10], d[10], rt[10];
    float U = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Input
    for (i = 0; i < n; i++) {
        printf("Process %d Arrival Time: ", i + 1);
        scanf("%d", &at[i]);

        printf("Process %d Burst Time: ", i + 1);
        scanf("%d", &bt[i]);

        printf("Process %d Deadline: ", i + 1);
        scanf("%d", &d[i]);

        rt[i] = bt[i];
    }

    // Step 1: CPU Utilization
    for (i = 0; i < n; i++) {
        U += (float)bt[i] / d[i];
    }

    printf("\nCPU Utilization = %.2f\n", U);

    // Step 2: Feasibility Check
    if (U > 1)
        printf("Scheduling not feasible\n");
    else
        printf("Scheduling feasible\n");

    printf("\nEDF Scheduling:\n");

    // Step 3–4: Scheduling Loop
    while (completed < n) {
        int idx = -1;
        int min_deadline = 9999;

        // Find ready process with earliest deadline
        for (i = 0; i < n; i++) {
            if (at[i] <= t && rt[i] > 0) {
                if (d[i] < min_deadline) {
                    min_deadline = d[i];
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            printf("Idle ");
            t++;
            continue;
        }

        // Execute 1 unit
        printf("P%d ", idx + 1);
        rt[idx]--;

        // Completion
        if (rt[idx] == 0) {
            completed++;
        }

        t++;
    }

    printf("\n");
    return 0;
}
