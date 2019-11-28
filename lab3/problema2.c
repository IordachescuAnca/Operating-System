#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<wait.h>
#include<stdlib.h>

const char message[] = "Error!";

int main(int argc, char** argv){
	if(argc != 2){
		write(2, message, sizeof(message));
		return 1;
	}

	pid_t pid = fork();
	if(pid < 0){
		write(2, message, sizeof(message));
		return 1;
	}
	else if(pid == 0){
		int n = atoi(argv[1]);
		printf("%d: ", n);
		while(n != 1){
			printf("%d ", n);
			if(n&1){
				n = 3 * n + 1;
			}
			else{
				n /= 2;
			}
		}
		printf("1\n");
	}
	else{
		wait(NULL);
		printf("Child %d finished", getpid());
	}

	return 0;
}