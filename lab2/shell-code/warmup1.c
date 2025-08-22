#include  <stdio.h>
#include  <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    int i=fork();
    if(i>0){
        wait();
        printf("I am Parent");
    }
    else if(i==0){
            printf("I am child");
            exit(0);
    }
}