#include  <stdio.h>
#include  <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    int i=fork();//retuerns 0 in child process // retirns child pid in parent process
    if(i>0){
        printf("I am Parent\n");
    }
    else if(i==0){
        printf("I am Child\n");
        execl("/usr/bin/ls","ls","-l",NULL);
        printf("I am Child\n");
    }

}