#include  <stdio.h>
#include  <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    int ret=fork();
    if(ret==0){
        while(1){

        }
    }
    else if(ret>0){
        //converting pid into a string
        int bufferSize=snprintf(NULL,0,"%d",ret);
        char*pidstr=(char*)malloc(bufferSize);
        sprintf(pidstr,"%d",ret);
        execl("/usr/bin/kill","kill","-9",pidstr,NULL);
        printf("failed");
    }
}