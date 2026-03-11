#include <stdio.h>

int main() {
    int n,i,time=0,completed=0;
    int at[20],bt[20],pr[20],rt[20];
    int ct[20],wt[20],tat[20],res[20];
    int min,index;
    float twt=0,ttat=0,trt=0;

    printf("Enter number of processes: ");
    scanf("%d",&n);

    for(i=0;i<n;i++){
        printf("Enter AT, BT, Priority for P%d: ",i+1);
        scanf("%d%d%d",&at[i],&bt[i],&pr[i]);
        rt[i]=bt[i];
        res[i]=-1;
    }

    while(completed<n){
        min=9999;
        index=-1;

        for(i=0;i<n;i++){
            if(at[i]<=time && rt[i]>0 && pr[i]<min){
                min=pr[i];
                index=i;
            }
        }

        if(index!=-1){
            if(res[index]==-1)
                res[index]=time-at[index];

            rt[index]--;
            time++;

            if(rt[index]==0){
                completed++;
                ct[index]=time;
                tat[index]=ct[index]-at[index];
                wt[index]=tat[index]-bt[index];
            }
        }
        else
            time++;
    }

    printf("\nP\tAT\tBT\tPR\tCT\tWT\tTAT\tRT\n");

    for(i=0;i<n;i++){
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
        i+1,at[i],bt[i],pr[i],ct[i],wt[i],tat[i],res[i]);

        twt+=wt[i];
        ttat+=tat[i];
        trt+=res[i];
    }

    printf("\nAverage WT = %.2f",twt/n);
    printf("\nAverage TAT = %.2f",ttat/n);
    printf("\nAverage RT = %.2f",trt/n);

    return 0;
}
