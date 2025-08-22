#include  <stdio.h>
#include  <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void signalhand(int t){
    printf("I will run forever\n");
}

int main(int argc, char* argv[]) {
    signal(2,signalhand);
    while(1){

    }
}