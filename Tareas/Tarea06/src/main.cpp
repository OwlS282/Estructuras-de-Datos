/*
Instituto Tecnologico de Costa Rica

Nombre : Owel Jafet Gutierrez Ortiz

Carnet : 2026800869

Profesor : Mauricio Aviles Cisneros

Semana 14 : Tarea Corta 6 - Heaps

Fecha de entrega : 06 / 11 / 2026

*/

/*
Programa principal:
	Programa de prueba de la tarea. Crea dos heaps con numeros aleatorios,
	los une con merge, extrae los n menores con removeTop, vacia el heap con
	removeFirst y, por ultimo, prueba heapify con un arreglo en memoria
	dinamica.
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "MinHeap.h"
#include "List.h"
#include "LinkedList.h"

using std::cout;
using std::cin;
using std::endl;

int main() {

	// Inicializa la semilla para que los numeros aleatorios cambien en cada ejecucion
	srand(time(0));

	// Se crean los dos heaps con la capacidad por defecto (DEFAULT_MAX)
	MinHeap<int> heap1;
	MinHeap<int> heap2;

	// Se pide la cantidad de elementos para cada heap (entero positivo).
	// El limite es DEFAULT_MAX / 2 para que al hacer merge quepan todos en heap1
	int cantidad;
	do {
		cout << "Cantidad de elementos para cada heap (1-" << DEFAULT_MAX / 2 << "): ";
		cin >> cantidad;
	} while (cantidad < 1 || cantidad > DEFAULT_MAX / 2);

	// Se insertan numeros aleatorios entre 0 y 99 en cada heap
	for (int i = 0; i < cantidad; i++) {
		heap1.insert(rand() % 100);
		heap2.insert(rand() % 100);
	}

	// Se imprimen los contenidos de ambos heaps
	cout << "Heap 1: ";
	heap1.print();
	cout << "Heap 2: ";
	heap2.print();

	// Se agregan todos los elementos de heap2 a heap1 (heap2 no se modifica)
	heap1.merge(&heap2);
	cout << "Heap 1 despues del merge: ";
	heap1.print();

	// Se pide n para el top; no puede ser mayor que la cantidad de elementos del heap
	int n;
	do {
		cout << "Cantidad n para el top (1-" << heap1.getSize() << "): ";
		cin >> n;
	} while (n < 1 || n > heap1.getSize());

	// removeTop saca los n menores del heap y los retorna en una lista dinamica
	List<int>* top = heap1.removeTop(n);
	cout << "Top " << n << ": ";
	top->print();
	delete top; // se libera la lista despues de imprimirla

	// Se vacia el heap con removeFirst, que siempre saca el menor
	cout << "Resto del heap 1: [";
	while (!heap1.isEmpty()) {
		cout << heap1.removeFirst();
		if (!heap1.isEmpty()) {
			cout << ", "; // coma entre elementos, pero no despues del ultimo
		}
	}
	cout << "]" << endl;

	// Se pide el tamano del arreglo para probar heapify; no puede superar la capacidad del heap
	int tam;
	do {
		cout << "Cantidad de elementos del arreglo (1-" << DEFAULT_MAX << "): ";
		cin >> tam;
	} while (tam < 1 || tam > DEFAULT_MAX);

	// Se crea el arreglo en memoria dinamica y se llena con numeros aleatorios
	int* arr = new int[tam];
	for (int i = 0; i < tam; i++) {
		arr[i] = rand() % 100;
	}

	// heapify copia el arreglo dentro del heap y lo ordena para cumplir la condicion de heap
	heap1.heapify(arr, tam);
	delete[] arr; // el heap tiene su propia copia, entonces el arreglo ya se puede liberar

	cout << "Heap 1 tras heapify: ";
	heap1.print();

	// Se extraen todos los elementos del heap; salen ordenados de menor a mayor
	List<int>* todos = heap1.removeTop(heap1.getSize());
	cout << "Contenido de removeTop: ";
	todos->print();
	delete todos;

	return 0;
}