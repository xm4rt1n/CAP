// Ejercicio que crea dos arrays por memoria dinamica y los suma, midiendo cuanto tarda esa suma.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h> //usar omp para paralelizar el for

void main() {
	int n;
	unsigned short* array1, * array2;
	time_t t0, t1;
	srand(0);

	omp_get_num_threads(4); //establecemos el numero de hilos a usar por omp en 4

	printf("Introduce el numero de elementos de los arrays: ");
	scanf("%d", &n);

	// reserva de memoria dinamica de las matrices
	array1 = (unsigned short*)malloc(n * sizeof(unsigned short));
	if (array1 == NULL) {
		printf("No se pudo reservar la memoria dinamica");
		exit;
	}
	array2 = (unsigned short*)malloc(n * sizeof(unsigned short));
	if (array2 == NULL) {
		printf("No se pudo reservar la memoria dinamica");
		exit;
	}

	//rellenar los arrays con numeros enteros pseudoaleatorios
	for (int i = 0; i < n - 1; i++) {
		*(array1 + i) = rand();
		*(array2 + i) = rand();
	}

	// realizamos la conversion de tipos para sumar bloques de long(8 bytes) en luegar de sumar bloques de short (2 bytes)
	unsigned long* LvA = (unsigned long*)array1;
	unsigned long* LvB = (unsigned long*)array2;

	//se suman los elementos de los arrays uno a uno midiendo cuanto tarda esta suma
	t0 = clock();

	n = n / 4; // tengo que reajustar el numero de elementos ya que ahora a estar mas agrupados los datos tengo menos datos. 

	//#pragma omp parallel for // paralelizacion del bucle for
	for (int i = 0; i < n; i++) {
		*(LvA + i) += *(LvB + i);
	}

	t1 = clock();

	printf("T0 = %d\n", t0);
	printf("T1 = %d\n", t1);
	printf("El tiempo es: %f", ((float)(t1 - t0) / CLOCKS_PER_SEC));

	free(array1);
	free(array2);
}