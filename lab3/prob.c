#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include<stdio.h>

#define MAXIMUMVALUE 207


const char message[] = "Error!\n";

int main(int argc, char** argv){
	if(argc != 3){
		write(2, message, sizeof(message));
		return 1;
	}

	int dpInput = open(argv[1], O_RDONLY);
	if(dpInput < 0){
		write(2, message, sizeof(message));
		return 1;
	}

	int dpOutput = open(argv[2], O_CREAT | O_WRONLY, 0644);
	if(dpOutput < 0){
		write(2, message, sizeof(message));
		return 1;
	}

	struct stat infoInput;
	if(stat(argv[1], &infoInput)){
		write(2, message, sizeof(message));
		return 1;
	}

	off_t sizeInfoInput = infoInput.st_size;


	unsigned int countBytes = 0;
	char *buffer = malloc(MAXIMUMVALUE * sizeof(char));

	while(countBytes != sizeInfoInput){
		ssize_t bytesRead = read(dpInput, buffer, sizeof(buffer));
		if(bytesRead < 0){
			write(2, message, sizeof(message));
			return 1;
		} 
		if(bytesRead == 0){
			break;
		}

		ssize_t bytesWritten = write(dpOutput, buffer, bytesRead);
		if(bytesWritten < 0){
			write(2, message, sizeof(message));
			return 1;
		}

		if(bytesWritten < bytesRead){
			ssize_t contor = bytesWritten;
			while(contor != bytesRead){
				ssize_t bytesWrittenActual = write(dpOutput, buffer + contor, sizeof(buffer + contor));
				if(bytesWritten < 0){
					write(2, message, sizeof(message));
					return 1;
				}
				contor += bytesWrittenActual;
			}
		}

		countBytes += bytesRead;
	}

	if(close(dpInput)){
		write(2, message, sizeof(message));
		return 1;
	}

	if(close(dpOutput)){
		write(2, message, sizeof(message));
		return 1;
	}

	return 0;
}