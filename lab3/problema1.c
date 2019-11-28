#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<wait.h>

const char message[] = "Error!";

int main(){
	pid_t pid = fork();
	if(pid < 0){
		write(2, message, sizeof(message));
		return 1;
	}
	else if(pid == 0){
		char *argv[] = {"ls","-l", NULL};
		execve("/bin/ls", argv, NULL);
	}
	else{
		printf("My ID: %d Child ID: %d \n", getppid(), getpid());
		wait(NULL);
		printf("Child %d finished", getpid());
	}
	return 0;
}