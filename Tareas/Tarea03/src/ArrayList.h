/*
Instituto Tecnológico de Costa Rica

Nombre : Owel Jafet Gutiérrez Ortiz

Carnet : 2026800869

Profesor : Mauricio Avilés Cisneros

Semana 8 : Tarea Corta 3 – Lista: Caja de Herramientas

Fecha de entrega : 24 / 09 / 2026

*/

/*
Clase:
	ArrayList: Implementación de lista con arreglo dinámico.
	Almacena elementos en un arreglo de tamaño fijo.
	Mantiene posición actual para navegación.
*/

#pragma once

#include <stdexcept>
#include <iostream>
#include "List.h"
#include "Util.h"

using std::runtime_error;
using std::cout;
using std::endl;

template <typename E>
class ArrayList : public List<E> {
private:
	E* elements;  // Arreglo de elementos
	int max;  // Tamaño máximo del arreglo
	int size;  // Cantidad actual de elementos
	int pos;  // Posición actual

public:
	// Constructor con tamaño máximo
	ArrayList(int max = DEFAULT_MAX) {
		if (max < 1)
			throw runtime_error("Error, Invalid max size.");
		elements = new E[max];
		this->max = max;
		size = pos = 0;
	}
	~ArrayList() {
		delete[] elements;
	}

	// Inserta en posición actual
	void insert(E element) {
		if (size == max)
			throw runtime_error("Error, list is full.");
		for (int i = size - 1; i >= pos; i--)
			elements[i + 1] = elements[i];
		elements[pos] = element;
		size++;
	}

	// Agrega al final
	void append(E element) {
		if (size == max)
			throw runtime_error("Error, list is full.");
		elements[size] = element;
		size++;
	}

	// Reemplaza elemento actual
	void setElement(E element) {
		if (size == 0)
			throw runtime_error("Error, list is empty.");
		if (pos == size)
			throw runtime_error("Error, not current element.");
		elements[pos] = element;
	}

	// Elimina elemento actual
	E remove() {
		if (size == 0)
			throw runtime_error("Error, list is empty.");
		if (pos == size)
			throw runtime_error("Error, not current element.");
		E result = elements[pos];
		for (int i = pos; i < size - 1; i++)
			elements[i] = elements[i + 1];
		size--;
		return result;
	}

	// Limpia la lista, borrado logico
	void clear() {
		pos = size = 0;
	}

	// Obtiene elemento actual
	E getElement() {
		if (size == 0) {
			throw runtime_error("Error, list is empty.");
		}
		if (pos == size) {
			throw runtime_error("Error, not current element.");
		}
		return elements[pos];
	}

	// Mueve al inicio
	void goToStart() {
		pos = 0;
	}

	// Mueve al final
	void goToEnd() {
		pos = size;
	}

	// Mueve a posición actual
	void goToPos(int pos) {
		if (pos < 0 || pos > size)
			throw runtime_error("Error, index out of bounds.");
		this->pos = pos;
	}

	// Avanza una posición
	void next() {
		if (pos < size)
			pos++;
	}

	// Retrocede una posición
	void previous() {
		if (pos > 0)
			pos--;
	}

	// Verifica si está al inicio
	bool atStart() {
		return pos == 0;
	}

	// Verifica si está al final
	bool atEnd() {
		return pos == size;
	}

	// Obtiene posición actual
	int getPos() {
		return pos;
	}

	// Obtiene tamaño
	int getSize() {
		return size;
	}

	// Imprime la lista
	void print() {
		cout << "[";
		for (int i = 0; i < size; i++) {
			cout << elements[i];
			if (i < size - 1)
				cout << ", ";
		}
		cout << "]" << endl;
	}
};

