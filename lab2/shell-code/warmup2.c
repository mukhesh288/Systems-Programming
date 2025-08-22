#include  <stdio.h>
#include  <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    int i=fork();
    if(i==0){//I am child
             pid_t child=getpid();
             printf("%d\n",child);
    }
    else if(i>0){

        printf("%d\n",i);

        pid_t k=wait();
        printf("%d\n",k);

        pid_t j=waitpid(i);
        printf("%d\n",j);
    }
}