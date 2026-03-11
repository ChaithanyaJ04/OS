#include <stdio.h>

int main() {
    int n,i,time=0,completed=0;
    int at[20],bt[20],pr[20];
    int ct[20],wt[20],tat[20],rt[20];
    int visited[20]={0};
    float twt=0,ttat=0,trt=0;

    printf("Enter number of processes: ");
    scanf("%d",&n);

    for(i=0;i<n;i++){
        printf("Enter AT, BT, Priority for P%d: ",i+1);
        scanf("%d%d%d",&at[i],&bt[i],&pr[i]);
    }

    while(completed<n){
        int index=-1;
        int min=9999;

        for(i=0;i<n;i++){
            if(at[i]<=time && visited[i]==0){
                if(pr[i]<min){
                    min=pr[i];
                    index=i;
                }
            }
        }

        if(index!=-1){
            time+=bt[index];
            ct[index]=time;

            tat[index]=ct[index]-at[index];
            wt[index]=tat[index]-bt[index];
            rt[index]=wt[index];

            visited[index]=1;
            completed++;

            twt+=wt[index];
            ttat+=tat[index];
            trt+=rt[index];
        }
        else{
            time++;
        }
    }

    printf("\nP\tAT\tBT\tPR\tCT\tWT\tTAT\tRT\n");

    for(i=0;i<n;i++){
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
        i+1,at[i],bt[i],pr[i],ct[i],wt[i],tat[i],rt[i]);
    }

    printf("\nAverage WT = %.2f",twt/n);
    printf("\nAverage TAT = %.2f",ttat/n);
    printf("\nAverage RT = %.2f",trt/n);

    return 0;
}
