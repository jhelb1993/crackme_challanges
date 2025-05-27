#include <stdio.h>
#include <stdlib.h>

void exit_fail(){
	printf("...Fail!\n");
	exit(1);
}

int main(int argc, char **argv){
	if(argc != 2){
		printf("Usage: %s key\n",argv[0]);
		exit(0);
	}
	
	if(argv[1][0] == 't'){
		printf("H");
	} else {
		exit_fail();
	}

	if(argv[1][1] == 'i'){
		printf("E");
	} else {
		exit_fail();
	}

	if(argv[1][2] == 'X'){
		printf("LL");
	} else {
		exit_fail();
	}

	if(argv[1][3] == '0'){
		printf("O!\n");
	} else {
		exit_fail();
	}
	return 0;
}
