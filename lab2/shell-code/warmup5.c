#include  <stdio.h>
#include  <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    int N=3;
    for(int i=0;i<N;i++){
        int ret=fork();
        if(ret==0){
            // printf("I am Child");
            pid_t pi=getpid();
            printf("%d\n",pi);
        }
        else if(ret>0){
            pid_t rea=waitpid(ret);
            printf("reaped:%d\n",rea);
        }
    }
}