#include <stdio.h>

int main() {
    int n, bt[20], at[20], wt[20], tat[20], ct[20], rt[20];
    int response[20], started[20] = {0};
    int i, time = 0, completed = 0;
    float twt = 0, ttat = 0, trt = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++) {
        printf("Enter Arrival Time for Process %d: ", i+1);
        scanf("%d", &at[i]);
        printf("Enter Burst Time for Process %d: ", i+1);
        scanf("%d", &bt[i]);
        rt[i] = bt[i];   // remaining time
    }

    while(completed < n) {
        int min = 9999, index = -1;

        for(i = 0; i < n; i++) {
            if(at[i] <= time && rt[i] > 0) {
                if(rt[i] < min) {
                    min = rt[i];
                    index = i;
                }
            }
        }

        if(index != -1) {


            if(started[index] == 0) {
                response[index] = time - at[index];
                started[index] = 1;
            }

            rt[index]--;
            time++;

            if(rt[index] == 0) {
                ct[index] = time;
                tat[index] = ct[index] - at[index];
                wt[index] = tat[index] - bt[index];
                completed++;
            }

        } else {
            time++;  // CPU idle
        }
    }

    for(i = 0; i < n; i++) {
        twt += wt[i];
        ttat += tat[i];
        trt += response[i];
    }

    printf("\nPROCESS\tAT\tBT\tCT\tWT\tTAT\tRT");
    for(i = 0; i < n; i++) {
        printf("\nP%d\t%d\t%d\t%d\t%d\t%d\t%d",
        i+1, at[i], bt[i], ct[i], wt[i], tat[i], response[i]);
    }

    printf("\n\nAverage Waiting Time = %.2f", twt/n);
    printf("\nAverage Turnaround Time = %.2f", ttat/n);
    printf("\nAverage Response Time = %.2f\n", trt/n);

    return 0;
}
