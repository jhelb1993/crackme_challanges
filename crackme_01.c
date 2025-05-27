#include <stdio.h>
#include <string.h>

int main(int argc, char **argv){
	if(argc != 2){
		fprintf(stderr, "Usage: %s KEY\n",argv[0]);
		return 1;
	}

	if(!strcmp(argv[1], "kauw-oPOq-ADd9-sGGf")){
		printf("Your crackme is licensed!\n");
		return 0;
	}
	printf("Invalid license!\n");

	return 1;
}
