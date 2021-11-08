#include "apue.h"
#include "stdlib.h"

struct st{
	int a;
	float b;
};

int main(int argc, const char *argv[]) {
	void *ptr = calloc(sizeof(long), 100);
	long *lptr = ptr;
	for(int i = 0; i < 100; ++i) {
		printf("%ld ", lptr[i]);
	}
	printf("\n");

	int* *fptr = (int **)calloc(sizeof(int*), 100);
	for(int i = 0; i < 100; ++i){
		printf("%p\t", fptr[i]);
	}
	printf("\n");

    	return 0;
}
