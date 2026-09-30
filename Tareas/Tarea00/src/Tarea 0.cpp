/**
Instituto Tecnológico de Costa Rica

Nombre: Owel Jafet Gutiérrez Ortiz

Carnet: 2026800869

Profesor: Mauricio Avilés Cisneros

Semana 3, Tarea #0: Ejercicios con arreglos en memoria dinámica

Fecha de entrega: 19/08/2026
*/

/**
Archivo donde se encuentran los dos ejercicios de la tarea.
*/



// librerias basicas de C++
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

//sirve para evitar escribir std:: antes de cada cosa que usemos de la libreria std
using std::string;
using std::cout;
using std::cin;
using std::endl;


int main()
{
	//  Inicio Ejercio 0 ============================================================================

	cout << "Inicio Ejercicio 0" << endl;

	// inicializar una semilla nueva en cade ejecucion
	srand(time(nullptr));

	cout << endl;
	cout << "Programa para desordenar un arreglo." << endl;

	int numero = 0;

	// validamos el numero
	while (true) {

		cout << "Indique la cantidad de números a generar: ";
		cin >> numero;

		//manejamos que no sea entero valido
		if (cin.fail()) {
			cout << "Error, entero no válido." << endl;
			cin.clear();
			cin.ignore(10000, '\n');
			continue;
		}

		//manejamos que sea mayor que 2
		if (numero <= 2) {
			cout << "Error, debe ser más de un número." << endl;
			continue;
		}

		break;
	};

	// inicializamos el arreglo dinamico con la cantidad de la variable numero
	int* arreglo = new int[numero];

	// rellenamos el arreglo del 1 a la cantidad de la variable numero
	for (int i = 0; i < numero; i++) {
		arreglo[i] = i + 1;
	}

	// mostramos el arreglo ordenado
	cout << "Arreglo Ordenado: ";
	cout << "	[ ";
	for (int i = 0; i < numero; i++) {
		cout << arreglo[i];
		if (i < numero - 1) {
			cout << ", ";
		}
	}
	cout << "]" << endl;

	// algoritmo para desordenar el arreglo, se hace la mitad de la cantidad de numeros, y se intercambian dos posiciones aleatorias
	int repeticiones = numero / 2;
	for (int i = 0; i < repeticiones; i++) {
		int indiceA = rand() % numero;
		int indiceB = rand() % numero;

		while (indiceB == indiceA) {
			indiceB = rand() % numero;
		}

		int numeroTemporal = arreglo[indiceA];
		arreglo[indiceA] = arreglo[indiceB];
		arreglo[indiceB] = numeroTemporal;
	}

	// mostramos el arreglo desordenado
	cout << "Arreglo Desordenado: ";
	cout << "	[ ";
	for (int i = 0; i < numero; i++) {
		cout << arreglo[i];
		if (i < numero - 1) {
			cout << ", ";
		}
	}
	cout << "]" << endl;

	// borramos el arreglo dinamico para liberar memoria
	delete[] arreglo;
	cout << endl;
	cout << "Fin Ejercicio 0" << endl;

	//  Fin Ejercio 0 ============================================================================

	//  Inicio Ejercio 1 ============================================================================
	cout << endl;
	cout << "Inicio Ejercicio 1" << endl;
	cout << endl;

	cout << "Programa para transponer un histograma no decreciente." << endl;

	// validamos la cantidad del numero de elementos del arreglo
	while (true) {

		cout << "Indique la cantidad de números a leer: ";
		cin >> numero;

		//manejamos que no sea entero valido
		if (cin.fail()) {
			cout << "Error, entero no válido." << endl;
			cin.clear();
			cin.ignore(10000, '\n');
			continue;
		}

		//manejamos que sea mayor que 0
		if (numero <= 0) {
			cout << "Error, debe ser mayor a 0." << endl;
			continue;
		}

		break;
	};

	//declaramos el arreglo dinamico de nuevo ya que lo borramos
	arreglo = new int[numero];

	cout << "Ingrese los enteros, deben estar en orden no decreciente. " << endl;

	// for para valdiar que los valores ingresados sean numero, mayores a 0 y que esten en orden no decreciente
	for (int i = 0; i < numero; i++) {
		while (true) {

			cout << "Ingrese el número " << i + 1 << ": ";
			cin >> arreglo[i];

			//manejamos que no sea entero valido
			if (cin.fail()) {
				cout << "Error, entero no válido." << endl;
				cin.clear();
				cin.ignore(10000, '\n');
				continue;
			}

			//manejamos elque sea mayor que 0
			if (arreglo[i] <= 0) {
				cout << "Error, debe ser mayor a 0." << endl;
				continue;
			}

			//manejamos que sea menor que el anterior
			if (i > 0 && arreglo[i] < arreglo[i - 1]) {
				cout << "Error, el número debe ser menor que el anterior" << endl;
				continue;
			}

			break;
		};
	}

	// mostramos el arreglo ingresado
	cout << "[ ";
	for (int i = 0; i < numero; i++) {
		cout << arreglo[i];
		if (i < numero - 1) {
			cout << ", ";
		}
	}
	cout << "]" << endl;

	// mostramos el histograma del arreglo ingresado
	for (int i = 0; i < numero; i++) {
		for (int j = 0; j < arreglo[i]; j++) {
			cout << "*";
		}
		cout << endl;
	}
	cout << endl;

	// obtenemos el numero maximo del arreglo ingresado, que es el ultimo elemento del arreglo ya que es no decreciente
	int numeroMaximo = arreglo[numero - 1];

	// declaramos el arreglo dinamico para el arreglo transpuesto
	int* arregloTranspuesto = new int[numeroMaximo];


	// for para contar cuantas veces se repite cada nivel del histograma y guardarlo en el arreglo transpuesto
	for (int nivel = 1; nivel <= numeroMaximo; nivel++) {
		int conteo = 0;
		for (int i = 0; i < numero; i++) {
			if (arreglo[i] >= nivel) {
				conteo++;
			}
		}
		// guardamos el conteo en el arreglo trans
		arregloTranspuesto[nivel - 1] = conteo;
	}

	// mostramos el arreglo transpuesto
	cout << "[ ";
	for (int i = numeroMaximo - 1; i >= 0; i--) {
		cout << arregloTranspuesto[i];
		if (i > 0) {
			cout << ", ";
		}
	}
	cout << "]" << endl;

	// mostramos el histograma transpuesto
	for (int i = numeroMaximo - 1; i >= 0; i--) {
		for (int j = 0; j < arregloTranspuesto[i]; j++) {
			cout << "*";
		}
		cout << endl;
	}

	// borramos el arreglo dinamico para liberar memoria
	delete[] arregloTranspuesto;

	cout << endl;
	cout << "Fin Ejercicio 0" << endl;
	//  Fin Ejercio 1 ============================================================================

	return 0;
}