/**
 * Simple program demonstrating shared memory in POSIX systems.
 *
 * This is the consumer process
 *
 * Figure 3.18
 *
 * @author Gagne, Galvin, Silberschatz
 * Operating System Concepts - Ninth Edition
 * Copyright John Wiley & Sons - 2013
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>

int main()
{
	const char *name = "OS";
	const char *message0= "freeeee";
	const int SIZE = 4096;

	int shm_fd;
	void *ptr;
	int i;

	key_t key = ftok("/path/to/keyfile", 'A');
    int msgid = msgget(key, 0666 | IPC_CREAT);

    if (msgid == -1) {
        perror("msgget");
        return 1;  // Error handling
    }

	/* open the shared memory segment */
	shm_fd = shm_open(name, O_RDONLY, 0666);
	if (shm_fd == -1) {
		printf("shared memory failed\n");
		exit(-1);
	}

	/* now map the shared memory segment in the address space of the process */
	ptr = mmap(0,SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
	if (ptr == MAP_FAILED) {
		printf("Map failed\n");
		exit(-1);
	}

	struct mymsg {
    long int    mtype;     /* message type */
    int        offset;  /* message text */
	};
	while(1){
	struct mymsg kk;
	if(msgrcv(msgid,&kk,SIZE,1,0)!=-1){
	// printf("%d\n", kk.offset);
	printf("%s\n", (char *)(ptr+kk.offset));
	// printf("%d\n", kk.offset);
	sleep(1);
	char*ptr5=(char *)(ptr+kk.offset);
	// printf("j\n");
	strcpy(ptr,message0);
	// printf("t\n");
	ptr5[7]='\0';
	}
	}
	msgctl(msgid, IPC_RMID, NULL);

	/* remove the shared memory segment */
	if (shm_unlink(name) == -1) {
		printf("Error removing %s\n",name);
		exit(-1);
	}

	return 0;
}
