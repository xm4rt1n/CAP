#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void main() {
	int n;
	int* array1,* array2;
	time_t t0, t1;
	srand(0);

	printf("Introduce el numero de elementos de los arrays: ");
	scanf("%d", &n);

	array1 = (int*)malloc(n * sizeof(int));
	array2 = (int*)malloc(n * sizeof(int));

	for (int i = 0; i < n - 1; i++) {
		*(array1 + i) = rand();
		*(array2 + i) = rand();
	}

	t0 = clock();
	
	for (int i = 0; i < n; i++) {
		*(array1 + i) += *(array2+i);
	}

	t1 = clock();

	printf("T0 = %d\n", t0);
	printf("T1 = %d\n", t1);
	printf("El tiempo es: %f", ((float)(t1 - t0) / CLOCKS_PER_SEC));

	free(array1);
	free(array2);
}
