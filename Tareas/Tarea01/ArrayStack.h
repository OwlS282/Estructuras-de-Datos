/*
Instituto Tecnológico de Costa Rica

Nombre : Owel Jafet Gutiérrez Ortiz

Carnet : 2026800869

Profesor : Mauricio Avilés Cisneros

Semana 4 : Tarea Corta 1 – Pilas

Fecha de entrega : 02 / 09 / 2026

*/

/*
Clase:
	ArrayStack: Implementación de pila usando un arreglo dinámico.
	Se redimensiona automáticamente cuando alcanza su capacidad máxima.
*/

#pragma once
//recomendacion hacer los include de las bibliotecas del lenguaje primero y luego los propios.

#include <stdexcept>	//lenguaje
#include <iostream>
#include "Stack.h"		//propio
#include "Util.h"

using std::runtime_error;
using std::cout;
using std::endl;

template <typename E> //es lo mismo que poner <class E>
class ArrayStack : public Stack<E> { //poner Stack tambien funciona
private:
	E* elements;
	int max;
	int size;

	void expandArray() {
		//creamos un nuevo arreglo temporal
		E* tempArray = new E[max * 2];
		//copiamos lo elementos del arreglos viajo al nuevo
		for (int i = 0; i < size; i++) {
			tempArray[i] = elements[i];
		}
		//borraos el arreglo viejo
		delete[] elements;
		//el atributo apunta al nuevo arreglo
		elements = tempArray;
		//duplicamos el atributo max
		max = max * 2;
	}


public:
	//si me mandan un valor en el parametro lo guardo y sino usamos por defecto 1024
	ArrayStack(int max = 1024) {
		//lanzamos un error
		if (max < 1) {
			throw runtime_error("Error, invalid max size.");
		}
		//podemos ponerlo sin this->
		elements = new E[max];

		this->max = max;
		size = 0;
	}
	//se borra todo
	~ArrayStack() {
		delete[] elements;
	}
	
	void push(E element) {
		if (size == max) {// si es igual al tamaño max
			expandArray();
		}
		elements[size] = element; // añadimos el elemento
		size++; //sumamos 1
	}

	E pop() {
		if (size == 0) // si el tamaño es igual a 0
			throw runtime_error("Error, stack overflow.");
		size--; //restamos 1
		return elements[size]; //returnamos el elemento
	}

	E topValue() { //tambien conocio como peak 
		if (size == 0) // si el tamaño es igual a 0
			throw runtime_error("Error, stack is empty.");
		return elements[size - 1]; //returnamos el elemento de la posicion especifica
	}

	void clear() {
		size = 0;
		//delete[] elements;
		//elements = new E[max]; //sirve para forzar el destructor de todos los elementos, casi no se usa (se usa si no sabemos que hacemos)
	}

	bool isEmpty() {
		return size == 0; //esto ya nos da un booleano
	}

	int getSize() {
		return size;
	}

	void print() {
		cout << "[ ";
		for (int i = 0; i < size; i++) {
			cout << elements[i];
			if (i < size - 1)
				cout << ", ";
		}
		cout << " ]" << endl;
	}
};

