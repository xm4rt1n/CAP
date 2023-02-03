#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

void quicksort(int* array, int nElem, int pivote);

void main() {
	int n;
	int* array1;

	srand(time(NULL));


	printf("Introduce el numero de elementos de los arrays: ");
	scanf("%d", &n);

	// reserva de memoria dinamica del array
	array1 = (int*)malloc(n * sizeof(int));
	if (array1 == NULL) {
		printf("No se pudo reservar la memoria dinamica");
		exit;
	}

	//rellenar el array con numeros enteros pseudoaleatorios
	for (int i = 0; i < n; i++) {
		*(array1 + i) = rand();
	}

	for (int i = 0; i < n; i++) {
		printf("%d,", *(array1 + i));
	}
	printf("\n");
	double t0 = omp_get_wtime();

	quicksort(array1, n, 5000);

	double t1 = omp_get_wtime();

	printf("\n");

	for (int i = 0; i < n; i++) {
		printf("%d, ", *(array1 + i));
	}
	printf("\n");

	printf("El tiempo es: %f", t1 - t0);

	free(array1);

}

void quicksort(int* array, int nElem, int pivote) {

	int menoresPivote = 0;
	int mayoresPivote = 0;
	int igualesPivote = 0;
	int* copiaArray;

	if (nElem <= 1) {
		return;
	}
	if (nElem == 2) {
		if (array[0] > array[1]) {
			int aux;
			aux = array[0];
			array[0] = array[1];
			array[1] = aux;
		}
		return;
	}

	copiaArray = (int*)malloc(nElem * sizeof(int));
	if (copiaArray == NULL) {
		printf("No se pudo reservar la memoria dinamica");
		exit;
	}

	for (int i = 0; i < nElem; i++) {
		if (array[i] < pivote) {
			copiaArray[menoresPivote] = array[i];
			menoresPivote++;
		}
		if (array[i] > pivote) {
			copiaArray[nElem-mayoresPivote-1] = array[i];
			mayoresPivote++;
		}
		if (array[i] == pivote) {
			igualesPivote++;
		}
	}

	for (int i = 0; i < igualesPivote; i++) {
		copiaArray[menoresPivote + i] = pivote;
	}

	memcpy(array, copiaArray, nElem * sizeof(int));
	free(copiaArray);

	quicksort(array, menoresPivote, pivote / 2);
	int posMayores = nElem - mayoresPivote;
	quicksort(array + posMayores, mayoresPivote, pivote * 3 / 2);

}