/**
 * Simple program demonstrating shared memory in POSIX systems.
 *
 * This is the producer process that writes to the shared memory region.
 *
 * Figure 3.17
 *
 * @author Silberschatz, Galvin, and Gagne
 * Operating System Concepts  - Ninth Edition
 * Copyright John Wiley & Sons - 2013
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <errno.h>

int main()
{
	const int SIZE = 4096;
	const char *name = "OS";
	const char *message0= "freeeee";
	const char *message1= "OSisFUN";

	key_t key = ftok("/path/to/keyfile", 'A');
    int msgid = msgget(key, 0666 | IPC_CREAT);

    if (msgid == -1) {
        perror("msgget");
        return 1;  // Error handling
    }

	int shm_fd;
	void *ptr;
	void *ptr1;
	void *ptr2;
	/* create the shared memory segment */
	shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);

	/* configure the size of the shared memory segment */
	ftruncate(shm_fd,SIZE);

	/* now map the shared memory segment in the address space of the process */
	ptr = mmap(0,SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
	if (ptr == MAP_FAILED) {
		printf("Map failed\n");
		return -1;
	}

	/**
	 * Now write to the shared memory region.
 	 *
	 * Note we must increment the value of ptr after each write.
	 */
	ptr1=ptr;
	ptr2=ptr;
	int k=0;
	for(int i=0;i<512;i++){
		sprintf(ptr,"%s",message0);
		ptr += strlen(message0)+1;
		}
	struct mymsg {
    long int    mtype;     /* message type */
    int        offset;  /* message text */
	};
	while(k<10){
	ptr1=ptr2;
	for(int i=0;i<512;i++){
	char*ptr4=(char*)ptr1;
	if(strcmp(ptr4,"freeeee")==0 && k<10){
		strcpy(ptr4,message1);
		ptr4[7]='\0';
		k++;
		struct mymsg ohh;
		ohh.mtype=1;
		ohh.offset = ptr1-ptr2;
		// printf("%d\n",ohh.offset);
    	msgsnd(msgid, &ohh, sizeof(ohh), 0);
		}
		ptr1 += strlen(message1)+1;
	}
	}
	return 0;
}
