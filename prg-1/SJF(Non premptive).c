#include <stdio.h>

int main() {
    int n, bt[20], at[20], wt[20], tat[20], ct[20];
    int completed[20] = {0};
    int i, time = 0, done = 0;
    float twt = 0, ttat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++) {
        printf("Enter Arrival Time for Process %d: ", i+1);
        scanf("%d", &at[i]);
        printf("Enter Burst Time for Process %d: ", i+1);
        scanf("%d", &bt[i]);
    }

    while(done < n) {
        int min = 9999, index = -1;

        for(i = 0; i < n; i++) {
            if(at[i] <= time && completed[i] == 0) {
                if(bt[i] < min) {
                    min = bt[i];
                    index = i;
                }
            }
        }

        if(index != -1) {
            ct[index] = time + bt[index];
            tat[index] = ct[index] - at[index];
            wt[index] = tat[index] - bt[index];

            time = ct[index];
            completed[index] = 1;
            done++;
        } else {
            time++; // CPU idle
        }
    }

    for(i = 0; i < n; i++) {
        twt += wt[i];
        ttat += tat[i];
    }

    printf("\nPROCESS\tAT\tBT\tCT\tWT\tTAT");
    for(i = 0; i < n; i++) {
        printf("\nP%d\t%d\t%d\t%d\t%d\t%d",
        i+1, at[i], bt[i], ct[i], wt[i], tat[i]);
    }

    printf("\n\nAverage Waiting Time = %.2f", twt/n);
    printf("\nAverage Turnaround Time = %.2f\n", ttat/n);

    return 0;
}
