// Ejercicio que dado un array de n elementos generado con numeros aleatorios los ordena recursivamente 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

void quicksort(int* array, int nElem, int pivote);

void main() {
	int n;
	int* array1;

	srand(time(NULL)); //esstablecemos una semilla para generar los numeros aleatorios


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

	// si el numero de elementos es pequeño imprimimos el vector. Usado para ver que funciona correctametne el algoritmo
	if (n < 10) {
		for (int i = 0; i < n; i++) {
			printf("%d,", *(array1 + i));
		}
	}

	printf("\n");

	// obtenemos el tiempo en el que se inicia la ejecucion del algoritmo y lo guardamos en una variable
	double t0 = omp_get_wtime();

	// llamamos al algoritmo quicksort 
	quicksort(array1, n, 5000);

	//obtenemos el tiempo en el que acaba la ejecucion del algoritmo.
	double t1 = omp_get_wtime();

	printf("\n");

	// imprimimos el array una vez se ha ordenado. 
	for (int i = 0; i < n; i++) {
		printf("%d, ", *(array1 + i));
	}
	printf("\n");

	// imprimimos el tiempo que ha tardado el algoritmo restando el final menos inicio.
	printf("El tiempo es: %f", t1 - t0);

	//liberamos la memoria dinamica.
	free(array1);

}

void quicksort(int* array, int nElem, int pivote) {

	int menoresPivote = 0;
	int mayoresPivote = 0;
	int igualesPivote = 0;
	int* copiaArray;

	if (nElem <= 1) { //si el numero de elementos es 0 o 1 devolvemos el array tal cual ya que no hay nada que ordenar.
		return;
	}
	if (nElem == 2) { //si el nº de elementos es dos, comprobamos si estan correctamente ordenados, de no ser asi los intercambiamos
		if (array[0] > array[1]) {
			int aux;
			aux = array[0];
			array[0] = array[1];
			array[1] = aux;
		}
		return;
	}
	// si el numero de elementos es >2 creamos un array de ayuda en memoria dinamica
	copiaArray = (int*)malloc(nElem * sizeof(int));
	if (copiaArray == NULL) {
		printf("No se pudo reservar la memoria dinamica");
		exit;
	}

	// tras ello recorremos el array original y vamos anotando si es mayor, menos o igual que el pivote
	for (int i = 0; i < nElem; i++) {
		if (array[i] < pivote) {
			copiaArray[menoresPivote] = array[i]; // los valores menores que el pivote los colocamos en el inicio del array de apoyo
			menoresPivote++;
		}
		if (array[i] > pivote) {
			copiaArray[nElem - mayoresPivote - 1] = array[i]; //los valores mayores que el pivote los colocamos desde el final del array de apoyo
			mayoresPivote++;
		}
		if (array[i] == pivote) {
			igualesPivote++; // los valores iguales que el pivote solo se cuentan 
		}
	}

	for (int i = 0; i < igualesPivote; i++) {
		copiaArray[menoresPivote + i] = pivote; //acabamos de rellenar el array de apoyo con los valores iguales que el pivote
	}

	memcpy(array, copiaArray, nElem * sizeof(int)); //copiamos el valores del array de apoyo al array original y liberamos la memoria dinamica
	free(copiaArray);

	// realizamos llamadas recursivas dividiendo cada vez nuestro vector en funcion de si son mayores que el pivote o menores y reajustando
	// el pivote
	quicksort(array, menoresPivote, pivote / 2);
	int posMayores = nElem - mayoresPivote;
	quicksort(array + posMayores, mayoresPivote, pivote * 3 / 2);

}

// creo que este codigo se podria optimizar si cada vez que se realiza una llamada recursiva se encarga un nuevo hilo, de esta manera
// los valores mayores que el pivote y menores que el pivote se ordenarian simultaneamente y se reduciria el tiempo, ya que actualmente primero 
// llamamos una vez a quircksort y le pasamos los valores menores que el pivote, esperamos a que termine y una vez termina realizamos el mismo proceso
// con los valores mayores al pivote. Esto se complementaria usando memoria compartida y que todos los hilos accedan al array original, esto no va 
// a ser problema ya que cada hilo va a acceder a posiciones de memoria diferentes, por lo que no se va a generar ningun tipo de conflicto. 