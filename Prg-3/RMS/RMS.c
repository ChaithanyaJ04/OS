#include <stdio.h>
#include <math.h>

int main() {
    int n, i, j;
    int C[10], T[10], remaining[10];
    int time, hyper = 1;
    float U = 0.0, bound;
    int current_task = -1, prev_task = -1;

    printf("Enter number of tasks: ");
    scanf("%d", &n);

    // Input
    for (i = 0; i < n; i++) {
        printf("Enter Execution Time (C) for Task %d: ", i + 1);
        scanf("%d", &C[i]);

        printf("Enter Period (T) for Task %d: ", i + 1);
        scanf("%d", &T[i]);

        remaining[i] = 0;
    }

    // Step 1: CPU Utilization
    for (i = 0; i < n; i++) {
        U += (float)C[i] / T[i];
    }

    // Step 2: RMS Bound
    bound = n * (pow(2, 1.0 / n) - 1);

    printf("\nCPU Utilization = %.4f", U);
    printf("\nRMS Bound = %.4f\n", bound);

    if (U <= bound)
        printf("Schedulable using RMS\n");
    else
        printf("Not guaranteed schedulable\n");

    // Step 4: Sort by Period (Priority)
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (T[j] > T[j + 1]) {
                int temp;

                temp = T[j];
                T[j] = T[j + 1];
                T[j + 1] = temp;

                temp = C[j];
                C[j] = C[j + 1];
                C[j + 1] = temp;
            }
        }
    }

    printf("\nPriority Order (Shortest Period = Highest Priority):\n");
    for (i = 0; i < n; i++) {
        printf("Task %d -> C=%d, T=%d\n", i + 1, C[i], T[i]);
    }

    // Hyperperiod (LCM)
    hyper = T[0];
    for (i = 1; i < n; i++) {
        int a = hyper, b = T[i], temp;
        while (b != 0) {
            temp = b;
            b = a % b;
            a = temp;
        }
        hyper = (hyper * T[i]) / a;
    }

    printf("\nScheduling with Preemption:\n");

    // Step 5: Scheduling Loop
    for (time = 0; time < hyper; time++) {

        // Task arrivals
        for (i = 0; i < n; i++) {
            if (time % T[i] == 0) {
                remaining[i] = C[i];
            }
        }

        // Select highest priority READY task
        current_task = -1;
        for (i = 0; i < n; i++) {
            if (remaining[i] > 0) {
                current_task = i;
                break;
            }
        }

        // Check preemption
        if (current_task != prev_task && prev_task != -1 && current_task != -1) {
            printf("\nTime %d: Task %d preempted by Task %d\n",
                   time, prev_task + 1, current_task + 1);
        }

        // Execute task
        if (current_task != -1) {
            printf("T%d ", current_task + 1);
            remaining[current_task]--;
        } else {
            printf("Idle ");
        }

        prev_task = current_task;
    }

    printf("\n");

    return 0;
}
