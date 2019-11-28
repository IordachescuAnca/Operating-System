#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<wait.h>
#include<stdlib.h>

const char message[] = "Error!";

int main(int argc, char** argv){
	if(argc == 1){
		write(2, message, sizeof(message));
		return 1;
	}

	printf("Starting parent %d\n", getpid());


	pid_t* pidArray = malloc((argc-1)*sizeof(pid_t));

	for(int i = 1; i <= argc-1; i++){
		pid_t pid = fork();
		if(pid < 0){
			write(2, message, sizeof(message));
			return 1;
		}
		else if(pid == 0){
			int n = atoi(argv[i]);
			printf("%d: ", n);
			while(n != 1){
				printf("%d ", n);
				if(n&1){
					n = 3 * n + 1;
				}
				else{
					n /= 2;
				}
				printf("1\n");
				return 0;
			}
		}
		pidArray[i-1] = pid;
	}

	for(int i = 0; i < argc-1; i++){
		int status = 0;
		waitpid(pidArray[i], &status, 0);
		printf("Done Parent %d Me %d\n", getpid(), pidArray[i]);
	}

	return 0;
}