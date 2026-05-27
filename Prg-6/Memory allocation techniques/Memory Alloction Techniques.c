#include <stdio.h>

int main()
{
    int m, n, i, j;

    // Input memory blocks
    printf("Enter number of memory blocks: ");
    scanf("%d", &m);

    int block[m], b1[m], b2[m], b3[m];

    printf("Enter sizes of %d memory blocks:\n", m);

    for(i = 0; i < m; i++)
    {
        scanf("%d", &block[i]);

        b1[i] = block[i];
        b2[i] = block[i];
        b3[i] = block[i];
    }

    // Input processes
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int p[n];

    printf("Enter sizes of %d processes:\n", n);

    for(i = 0; i < n; i++)
        scanf("%d", &p[i]);

    int a[n];

    // ---------------- FIRST FIT ----------------
    printf("\n--- First Fit ---\n\n");
    printf("%-15s %-15s %-15s\n",
           "Process No.", "Process Size", "Block No.");

    for(i = 0; i < n; i++)
    {
        a[i] = -1;

        for(j = 0; j < m; j++)
        {
            if(b1[j] >= p[i])
            {
                a[i] = j;
                b1[j] -= p[i];
                break;
            }
        }

        if(a[i] != -1)
            printf("%-15d %-15d %-15d\n",
                   i + 1, p[i], a[i] + 1);
        else
            printf("%-15d %-15d %-15s\n",
                   i + 1, p[i], "Not Allocated");
    }

    // ---------------- BEST FIT ----------------
    printf("\n--- Best Fit ---\n\n");
    printf("%-15s %-15s %-15s\n",
           "Process No.", "Process Size", "Block No.");

    for(i = 0; i < n; i++)
    {
        int best = -1;

        for(j = 0; j < m; j++)
        {
            if(b2[j] >= p[i])
            {
                if(best == -1 || b2[j] < b2[best])
                    best = j;
            }
        }

        if(best != -1)
        {
            b2[best] -= p[i];

            printf("%-15d %-15d %-15d\n",
                   i + 1, p[i], best + 1);
        }
        else
        {
            printf("%-15d %-15d %-15s\n",
                   i + 1, p[i], "Not Allocated");
        }
    }

    // ---------------- WORST FIT ----------------
    printf("\n--- Worst Fit ---\n\n");
    printf("%-15s %-15s %-15s\n",
           "Process No.", "Process Size", "Block No.");

    for(i = 0; i < n; i++)
    {
        int worst = -1;

        for(j = 0; j < m; j++)
        {
            if(b3[j] >= p[i])
            {
                if(worst == -1 || b3[j] > b3[worst])
                    worst = j;
            }
        }

        if(worst != -1)
        {
            b3[worst] -= p[i];

            printf("%-15d %-15d %-15d\n",
                   i + 1, p[i], worst + 1);
        }
        else
        {
            printf("%-15d %-15d %-15s\n",
                   i + 1, p[i], "Not Allocated");
        }
    }

    return 0;
}
