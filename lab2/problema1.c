#include<unistd.h>

int main(){
	char mesaj[] = "Hello, world!";

	ssize_t bytesWritten = write(2, mesaj, sizeof(mesaj));

	if(bytesWritten < 0){
		return 1;
	}

	return 0;
}