#include <stdio.h>

int main()
{
    int n, m, i, j;

    printf("Enter number of processes\t--\t");
    scanf("%d", &n);

    printf("Enter number of resources\t--\t");
    scanf("%d", &m);

    int alloc[n][m], max[n][m], need[n][m];
    int avail[m], work[m];
    int finish[n], safe[n];

    // Input Allocation and Max
    for(i=0; i<n; i++)
    {
        printf("\nEnter details for P%d\n", i);

        printf("Enter allocation\t--\t");
        for(j=0; j<m; j++)
            scanf("%d", &alloc[i][j]);

        printf("Enter Max\t\t--\t");
        for(j=0; j<m; j++)
            scanf("%d", &max[i][j]);
    }

    // Calculate Need Matrix
    for(i=0; i<n; i++)
    {
        for(j=0; j<m; j++)
        {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    // Input Available Resources
    printf("\nEnter Available Resources --\t");
    for(i=0; i<m; i++)
        scanf("%d", &avail[i]);

    // New Request
    int pid, req[m];

    printf("\nEnter New Request Details --\n");

    printf("Enter pid\t--\t");
    scanf("%d", &pid);

    printf("Enter Request for Resources\t--\t");
    for(i=0; i<m; i++)
        scanf("%d", &req[i]);

    // Check Request
    int possible = 1;

    for(i=0; i<m; i++)
    {
        if(req[i] > need[pid][i] || req[i] > avail[i])
        {
            possible = 0;
            break;
        }
    }

    // Temporary Allocation
    if(possible)
    {
        for(i=0; i<m; i++)
        {
            avail[i] -= req[i];
            alloc[pid][i] += req[i];
            need[pid][i] -= req[i];
        }
    }

    // Initialize
    for(i=0; i<n; i++)
        finish[i] = 0;

    for(i=0; i<m; i++)
        work[i] = avail[i];

    int count = 0;

    printf("\nOUTPUT\n");

    // Safety Algorithm
    while(count < n)
    {
        int found = 0;

        for(i=0; i<n; i++)
        {
            if(finish[i] == 0)
            {
                int flag = 1;

                for(j=0; j<m; j++)
                {
                    if(need[i][j] > work[j])
                    {
                        flag = 0;
                        break;
                    }
                }

                if(flag)
                {
                    for(j=0; j<m; j++)
                        work[j] += alloc[i][j];

                    printf("P%d is visited(", i);

                    for(j=0; j<m; j++)
                        printf("%d ", work[j]);

                    printf(")\n");

                    safe[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if(found == 0)
            break;
    }

    // Check Safe State
    int safeState = 1;

    for(i=0; i<n; i++)
    {
        if(finish[i] == 0)
        {
            safeState = 0;
            break;
        }
    }

    if(safeState)
    {
        printf("SYSTEM IS IN SAFE STATE\n");

        printf("The Safe Sequence is -- (");

        for(i=0; i<n; i++)
            printf("P%d ", safe[i]);

        printf(")\n");
    }
    else
    {
        printf("SYSTEM IS NOT IN SAFE STATE\n");
    }

    // Final Table
    printf("\nProcess\tAllocation\tMax\t\tNeed\n");

    for(i=0; i<n; i++)
    {
        printf("P%d\t", i);

        for(j=0; j<m; j++)
            printf("%d ", alloc[i][j]);

        printf("\t\t");

        for(j=0; j<m; j++)
            printf("%d ", max[i][j]);

        printf("\t\t");

        for(j=0; j<m; j++)
            printf("%d ", need[i][j]);

        printf("\n");
    }

    return 0;
}
