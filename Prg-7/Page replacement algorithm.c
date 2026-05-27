#include <stdio.h>

int main()
{
    int f,n,i,j,k,pf=0,pos=0;

    printf("Enter the number of Frames: ");
    scanf("%d",&f);

    printf("Enter the length of reference string: ");
    scanf("%d",&n);

    int ref[n],frame[f];

    printf("Enter the reference string: ");
    for(i=0;i<n;i++)
        scanf("%d",&ref[i]);

// ---------------- FIFO ----------------

    for(i=0;i<f;i++) frame[i]=-1;

    printf("\nFIFO Page Replacement Process:\n");

    for(i=0;i<n;i++)
    {
        int found=0;

        for(j=0;j<f;j++)
            if(frame[j]==ref[i]) found=1;

        if(!found)
        {
            frame[pos]=ref[i];
            pos=(pos+1)%f;
            pf++;

            printf("PF No. %d: ",pf);

            for(j=0;j<f;j++)
                frame[j]==-1 ? printf("- ") : printf("%d ",frame[j]);

            printf("\n");
        }
    }

    printf("FIFO Page Faults: %d\n",pf);

// ---------------- LRU ----------------

    for(i=0;i<f;i++) frame[i]=-1;
    pf=0;

    printf("\nLRU Page Replacement Process:\n");

    for(i=0;i<n;i++)
    {
        int found=0;

        for(j=0;j<f;j++)
            if(frame[j]==ref[i]) found=1;

        if(!found)
        {
            int lru=0,min=999;

            for(j=0;j<f;j++)
            {
                int last=-1;

                for(k=i-1;k>=0;k--)
                    if(frame[j]==ref[k])
                    {
                        last=k;
                        break;
                    }

                if(last<min)
                {
                    min=last;
                    lru=j;
                }
            }

            frame[lru]=ref[i];
            pf++;

            printf("PF No. %d: ",pf);

            for(j=0;j<f;j++)
                frame[j]==-1 ? printf("- ") : printf("%d ",frame[j]);

            printf("\n");
        }
    }

    printf("LRU Page Faults: %d\n",pf);

// ---------------- OPTIMAL ----------------

    for(i=0;i<f;i++) frame[i]=-1;
    pf=0;

    printf("\nOptimal Page Replacement Process:\n");

    for(i=0;i<n;i++)
    {
        int found=0;

        for(j=0;j<f;j++)
            if(frame[j]==ref[i]) found=1;

        if(!found)
        {
            int far=-1,replace=0;

            for(j=0;j<f;j++)
            {
                int next=999;

                for(k=i+1;k<n;k++)
                    if(frame[j]==ref[k])
                    {
                        next=k;
                        break;
                    }

                if(next>far)
                {
                    far=next;
                    replace=j;
                }
            }

            frame[replace]=ref[i];
            pf++;

            printf("PF No. %d: ",pf);

            for(j=0;j<f;j++)
                frame[j]==-1 ? printf("- ") : printf("%d ",frame[j]);

            printf("\n");
        }
    }

    printf("Optimal Page Faults: %d\n",pf);

    return 0;
}
