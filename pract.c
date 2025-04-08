#include<stdio.h>
#include<stdbool.h>

#define p 5
#define r 3

bool isSafe(int alloc[][r],int max[][r],int avail[r]){
    int need[p][r];
    bool finish[p]={0};
     int work[r];
     int safeseq[p];

     for(int i=0;i<p;i++){
        for(int j=0;j<r;j++){
            need[i][j]=max[i][j]-alloc[i][j];
           
        }
     }
     
        for(int j=0;j<r;j++)
        work[j]=avail[j];
     

     int count=0;
     while(count<p){
        bool found=false;
        for(int i=0;i<p;i++){
            if(!finish[i]){
                int j;
                for(j=0;j<r;j++){
                    if(need[i][j]>work[j])
                    break;
                }
                if(j==r){
                    for(int k=0;k<r;k++)
                        work[k]+=alloc[i][k];
                    
                        finish[i]=true;
                        found=true;
                        safeseq[count++]=i;

                        printf("p%d\n",i);
                       for(int k=0;k<r;k++) printf("%d",alloc[i][k]);
                        printf("\t");
                    for(int k=0;k<r;k++)
                    printf("%d",max[i][k]);
                printf("\t");
                for(int k=0;k<r;k++)
                printf("%d",need[i][k]);
            printf("\t");
            for(int k=0;k<r;k++)
            printf("%d",work[k]);
        printf("\n");

                       

                }
            }
        }
        if(!found){
            printf("system is not safe \n");
            return false;

        }
       
        }printf("safe seq is \n");
        for(int i=0;i<p;i++){
            printf("%d",safeseq[i]);
        
             
     } return true;
}


int main(){
int alloc[p][r],max[p][r],avail[r];
printf("enter the availabe resource\n ");

    for(int j=0;j<r;j++){
        scanf("%d",&avail[j]);
     }

for(int i=0;i<p;i++){
    printf("enter the max resource %d\n",i);
        for(int j=0;j<r;j++){
            scanf("%d",&max[i][j]);
        }
    }

for(int i=0;i<p;i++){
    printf("enter the alloc resource %d\n",i);
        for(int j=0;j<r;j++){
            scanf("%d",&alloc[i][j]);
        }
    }if(!isSafe(alloc,max,avail)){
    printf("state is unsafe\n");
    return 1;
}

return 0;
}

   
