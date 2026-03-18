#include <stdio.h>

int main()
{
    int n, bt[20], wt[20], tat[20], at[20], ct[20], rt[20];
    int resp[20], visited[20];
    int queue[100], front = 0, rear = 0;
    int inQueue[20] = {0};

    int i, tq, time = 0, remain;
    float twt = 0.0, ttat = 0.0, trt = 0.0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++)
    {
        printf("Enter AT and BT for P%d: ", i+1);
        scanf("%d %d", &at[i], &bt[i]);

        rt[i] = bt[i];
        visited[i] = 0;
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    remain = n;

    // Push processes that arrive at time 0
    for(i = 0; i < n; i++)
    {
        if(at[i] == 0)
        {
            queue[rear++] = i;
            inQueue[i] = 1;
        }
    }

    while(remain > 0)
    {
        // If queue empty → CPU idle
        if(front == rear)
        {
            time++;
            for(i = 0; i < n; i++)
            {
                if(at[i] <= time && rt[i] > 0 && !inQueue[i])
                {
                    queue[rear++] = i;
                    inQueue[i] = 1;
                }
            }
            continue;
        }

        i = queue[front++];

        // Response time
        if(visited[i] == 0)
        {
            resp[i] = time - at[i];
            visited[i] = 1;
        }

        // Execute process
        if(rt[i] <= tq)
        {
            time += rt[i];
            rt[i] = 0;
            ct[i] = time;
            remain--;
        }
        else
        {
            time += tq;
            rt[i] -= tq;
        }

        // Add newly arrived processes
        for(int j = 0; j < n; j++)
        {
            if(at[j] <= time && rt[j] > 0 && !inQueue[j])
            {
                queue[rear++] = j;
                inQueue[j] = 1;
            }
        }

        // Re-add current process if not finished
        if(rt[i] > 0)
        {
            queue[rear++] = i;
        }
    }

    // Calculate TAT, WT
    for(i = 0; i < n; i++)
    {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        twt += wt[i];
        ttat += tat[i];
        trt += resp[i];
    }

    printf("\nPROCESS\tAT\tBT\tCT\tTAT\tWT\tRT\n");

    for(i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
        i+1, at[i], bt[i], ct[i], tat[i], wt[i], resp[i]);
    }

    printf("\nAverage TAT = %.2f", ttat/n);
    printf("\nAverage WT = %.2f", twt/n);
    printf("\nAverage RT = %.2f\n", trt/n);

    return 0;
}
