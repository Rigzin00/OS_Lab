#include<stdio.h>
#include<String.h>

void ff(int bs[],int m, int ps[],int n){
 int all[n];
 memset(all,-1,sizeof(all));
 for(int i=0;i<n;i++){
    for(int j=0;j<m;j++){
        if(bs[j]<=ps[i]){
            all[i]=j;
            bs[j]-=ps[i];
            break;
        }
    }
 }
 printf("\nProcess No.\tProcess Size\tBlock no.\n");
 for (int i = 0; i < n; i++) {
     printf(" %d\t\t%d\t\t", i + 1, processSize[i]);
     if (allocation[i] != -1)
         printf("%d", allocation[i] + 1);
     else
         printf("Not Allocated");
     printf("\n");
 }

 printf("Free Blocks\n");
 for (int i = 0; i < m; i++) printf("%d->",blockSize[i]);
}
int main(){
    int bs[]={122,232,43,};
    int ps[]={211,75,856};
    int m=sizeof(bs)/sizeof(bs[0]);
    int  n= sizeof(ps)/sizeof(ps[0]);
    ff(bs,m,ps,n);
    return 0;
}