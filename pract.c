#include<stdio.h>
#include<stdbool.h>

#define p 5
#define r 3

int main(){

   int alloc[p][r],max[p][r],avail[r];
   printf("enter the avail resource");
for(int i=0;i<r;i++){
    scanf("%d",&avail[i]);
}
    for(int i=0;i<p;i++){
        printf("enter the max resource for p%d", i);
        for(int j=0;j<r;j++){
            scanf("%d",&max[i][j]);

        }
    }
    
    for(int i=0;i<p;i++){
        printf("enter the aloc resource for p%d", i);
        for(int j=0;j<r;j++){
            scanf("%d",&alloc[i][j]);

        }
    }
    
}