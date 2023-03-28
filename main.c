
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "ts_hashmap.h"

int main(int argc, char *argv[]) {
	if (argc < 3) {
		printf("Usage: %s <num threads> <hashmap capacity>\n", argv[0]);
		return 1;
	}

  srand(time(NULL));
	int capacity = (unsigned int) atoi(argv[2]);
	int length = (int) (rand() * 30.0/RAND_MAX) + 1;
	ts_hashmap_t *testMap = initmap(capacity);

	for(int i = 0; i < length; i++){
		int newSize = (int) (rand() * 30.0/RAND_MAX) + 1;
		put(testMap, newSize, newSize);
	}
printmap(testMap);
return 0;
}