#include  <stdio.h>
#include  <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_INPUT_SIZE 1024
#define MAX_TOKEN_SIZE 64
#define MAX_NUM_TOKENS 64

/* Splits the string by space and returns the array of tokens
*
*/
char **tokenize(char *line)
{
  char **tokens = (char **)malloc(MAX_NUM_TOKENS * sizeof(char *));
  char *token = (char *)malloc(MAX_TOKEN_SIZE * sizeof(char));
  int i, tokenIndex = 0, tokenNo = 0;

  for(i =0; i < strlen(line); i++){

    char readChar = line[i];

    if (readChar == ' ' || readChar == '\n' || readChar == '\t'){
      token[tokenIndex] = '\0';
      if (tokenIndex != 0){
	tokens[tokenNo] = (char*)malloc(MAX_TOKEN_SIZE*sizeof(char));
	strcpy(tokens[tokenNo++], token);
	tokenIndex = 0; 
      }
    } else {
      token[tokenIndex++] = readChar;
    }
  }
 
  free(token);
  tokens[tokenNo] = NULL ;
  return tokens;
}

void signalhand(int t){

}

int main(int argc, char* argv[]) {
	char  line[MAX_INPUT_SIZE];            
	char  **tokens;              
	int i;
	pid_t background[64]={0};

	signal(2,signalhand);
	while(1) {			
		/* BEGIN: TAKING INPUT */
		bzero(line, sizeof(line));
		printf("$ ");
		scanf("%[^\n]", line);
		getchar();
		printf("Command entered: %s (remove this debug output later)\n", line);
		/* END: TAKING INPUT */

		line[strlen(line)] = '\n'; //terminate with new line
		tokens = tokenize(line);
       //do whatever you want with the commands, here we just print them
	   	if(tokens[0]==NULL){
			continue;
	   	}
	   int present=0;
	   int f=0;
	   int h=0;
	   while(1){			    			
		if(tokens[h]==NULL||strcmp(tokens[h],"&&")==0){
						// printf("%d\n",h);
			if(tokens[h]==NULL){
				f=1;
			}
			else{
				tokens[h]=NULL;
			}
			// printf("%d\n",h);

		pid_t print[64]={0};
		//seeing if anything is exited,if exited reaping it
	   int e =-2;
	   int t=0;
		if(strcmp(tokens[present],"exit")==0){
		for(int i=0;i<64;i++){
			// int bufferSize = snprintf(NULL, 0, "%d", background[i]) + 1; // +1 for the null terminator
			// char *pidStr = (char *)malloc(bufferSize);
			// sprintf(pidStr, "%d", background[i]);
			int ret=fork();
			if(ret==0){
			if(background[i]!=0){
				kill(background[i],9);
			}
			exit(0);
			}
			else if(ret>0){
				waitpid(ret,NULL,0);
			}
		}
		break;
	   }
	   else{
	   for(int i=0;i<64;i++){
		if(background[i]!=0){
			// printf("%d\n",background[0]);
			e=waitpid(background[i],NULL,WNOHANG);
			//  printf("%d\n",e);
			if(e>0){
				print[t]=background[i];t++;
				background[i]=0;
				//make it zero and print it at last
			}
		}
	   }
	   //command

	   if(strcmp(tokens[present],"cd")==0){
		if(chdir(tokens[present+1])==0 && tokens[present+2]==NULL){

		}
		else{printf("Incorrect Command\n");
		}
	   }
	   else{
		// printf("HELLO\n");
		int h=0;
		int back=0;
		while(tokens[h]!=NULL){
			if(strcmp(tokens[h],"&")==0){
				if(tokens[h+1]==NULL)
					{back=1;
					break;}
			}
			h++;
		}
		if(back==0){
			int ret=fork();
			if(ret==0){//we are in the child process
				char p[1024]="/usr/bin/";
				strcat(p,tokens[present]);
				// printf("%s\n",tokens[1]);
				// printf("HELLO");
				execv(p,&tokens[present]);
				printf("The command doesnot exist\n");
				exit(0);
			}
			else if(ret>0){//parent process
				waitpid(ret,NULL,0);
				//printing the terminated exited processes
				for(int i=0;i<64;i++){
					if(print[i]==0){
						break;
					}
					else{
						printf("Background process with PID %d has been reaped\n",print[i]);
					}
				}
			}
			}
		else if(back==1){
			// printf("d\n");
			int ret=fork();
			if(ret==0){//we are in the child process
				setpgid(0,0); // keeping the background processes in a seperate process group
				char p[1024]="/usr/bin/";
				tokens[h]=NULL;
				strcat(p,tokens[0]);
				execv(p,tokens);
				printf("The command doesnot exist\n");
				exit(0);
			}
			else if(ret>0){
				for(int i=0;i<63;i++){
					if(background[i]==0){
						background[i]=ret;
						// printf("%d\n",background[0]);
						break;
				}
	   		}
			//printing the terminated exited processes
			for(int i=0;i<64;i++){
				if(print[i]==0){
					break;
				}
				else{
					printf("Background process with PID %d has been reaped\n",print[i]);
				}
			}
			}
				}
			}}		
			present=h+1;}
		if(f==1){
			break;
		}
		h=h+1;

	   }
	   if(tokens[present]!=NULL){
	   if(strcmp(tokens[present],"exit")==0){
	   break;}}

		for(i=0;tokens[i]!=NULL;i++){
			printf("found token %s (remove this debug output later)\n", tokens[i]);
		}
       
		for(i=0;tokens[i]!=NULL;i++){
			free(tokens[i]);

		}
		free(tokens);
		}

	return 0;
}