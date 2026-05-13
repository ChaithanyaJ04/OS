#include <stdio.h>

int main()
{
    int n, m, i, j;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resources: ");
    scanf("%d", &m);

    int alloc[n][m], request[n][m], avail[m];
    int work[m], finish[n];

    // Input Allocation Matrix
    printf("\nEnter Allocation Matrix:\n");
    for(i=0; i<n; i++)
    {
        printf("P%d: ", i);
        for(j=0; j<m; j++)
        {
            scanf("%d", &alloc[i][j]);
        }
    }

    // Input Request Matrix
    printf("\nEnter Request Matrix:\n");
    for(i=0; i<n; i++)
    {
        printf("P%d: ", i);
        for(j=0; j<m; j++)
        {
            scanf("%d", &request[i][j]);
        }
    }

    // Input Available Resources
    printf("\nEnter Available Resources: ");
    for(i=0; i<m; i++)
    {
        scanf("%d", &avail[i]);
        work[i] = avail[i];
    }

    // Step 1: Initialize Finish
    for(i=0; i<n; i++)
    {
        int zero = 1;

        for(j=0; j<m; j++)
        {
            if(alloc[i][j] != 0)
            {
                zero = 0;
                break;
            }
        }

        if(zero)
            finish[i] = 1;
        else
            finish[i] = 0;
    }

    // Step 2 & 3
    int found;

    do
    {
        found = 0;

        for(i=0; i<n; i++)
        {
            if(finish[i] == 0)
            {
                int possible = 1;

                for(j=0; j<m; j++)
                {
                    if(request[i][j] > work[j])
                    {
                        possible = 0;
                        break;
                    }
                }

                if(possible)
                {
                    printf("\nP%d can finish", i);

                    for(j=0; j<m; j++)
                    {
                        work[j] += alloc[i][j];
                    }

                    finish[i] = 1;
                    found = 1;
                }
            }
        }

    } while(found);

    // Step 4: Check Deadlock
    int deadlock = 0;

    printf("\n\nDeadlocked Processes: ");

    for(i=0; i<n; i++)
    {
        if(finish[i] == 0)
        {
            printf("P%d ", i);
            deadlock = 1;
        }
    }

    if(deadlock == 0)
    {
        printf("None");
        printf("\nSystem is NOT in Deadlock");
    }
    else
    {
        printf("\nSystem is in Deadlock");
    }

    return 0;
}
