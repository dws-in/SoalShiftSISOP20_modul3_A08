#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h> 

int main() 
{ 
	int fd1[2];
	int fd2[2];
	pid_t p; 
	
	if(pipe(fd1)==-1)
	{
		fprintf(stderr, "pipe error");
		return 1;
	}

	if((fork()) == 0)
	{
        dup2(fd1[1], 1); //output to fd1
        close(fd1[0]);
        close(fd1[1]);
        char *argv[4] = {"ls", NULL};
        execv("/bin/ls",argv);
	} 

    	if(pipe(fd2)==-1)
	return 1;

   	 else{
        dup2(fd1[0], 0);// input from fd1
        close(fd1[0]);
        close(fd1[1]);

        char *argv[4] = {"wc", "-l", NULL};
        execv("/usr/bin/wc",argv);
    }
}
