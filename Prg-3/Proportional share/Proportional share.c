#include <stdio.h>

#define TIME_QUANTUM 10

int main() {
    int n, i, completed = 0;
    int bt[10], rt[10], weight[10];
    int total_weight = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Input
    for (i = 0; i < n; i++) {
        printf("Process %d Burst Time: ", i + 1);
        scanf("%d", &bt[i]);

        printf("Process %d Weight: ", i + 1);
        scanf("%d", &weight[i]);

        rt[i] = bt[i];
        total_weight += weight[i];
    }

    printf("\nProportional Share Scheduling:\n");

    // Scheduling Loop
    while (completed < n) {

        for (i = 0; i < n; i++) {

            if (rt[i] > 0) {
                // Step 8: Time slice calculation
                int time_slice = (weight[i] * TIME_QUANTUM) / total_weight;

                if (time_slice == 0)
                    time_slice = 1;

                printf("P%d ", i + 1);

                // Execute
                if (rt[i] <= time_slice) {
                    rt[i] = 0;
                    completed++;
                    total_weight -= weight[i];
                } else {
                    rt[i] -= time_slice;
                }
            }
        }
    }

    printf("\n");
    return 0;
}
