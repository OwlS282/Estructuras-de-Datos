/*
Instituto Tecnologico de Costa Rica

Nombre : Owel Jafet Gutierrez Ortiz

Carnet : 2026800869

Profesor : Mauricio Aviles Cisneros

Semana 14 : Tarea Corta 6 - Heaps

Fecha de entrega : 06 / 11 / 2026

*/

/*
Clase MinHeap:
	Monticulo (heap) de minimos implementado con un arreglo. Permite insertar
	elementos, eliminar el de mayor prioridad (el menor) y, ademas, crear el
	heap a partir de un arreglo (heapify), unir otro heap (merge) y extraer
	los n elementos menores en una lista (removeTop).
*/

#pragma once

#include <stdexcept>
#include <iostream>
#include "Util.h"
#include "List.h"
#include "LinkedList.h"

using std::runtime_error;
using std::cout;
using std::endl;

template <typename E>
class MinHeap {
private:
	E* elements;
	int max;
	int size;

	int parent(int pos) {
		return (pos - 1) / 2;
	}

	int leftChild(int pos) {
		return pos * 2 + 1;
	}

	int rightChild(int pos) {
		return pos * 2 + 2;
	}

	bool isLeaf(int pos) {
		return leftChild(pos) >= size;
	}

	int minChild(int pos) {
		int right = rightChild(pos);
		int left = leftChild(pos);

		if (right < size && elements[right] < elements[left]) {
			return right;
		}
		return left;
	}

	void siftUp(int pos) {
		while (pos > 0 && elements[pos] < elements[parent(pos)]) {
			swap(pos, parent(pos));
			pos = parent(pos);
		}
	}

	void siftDown(int pos) {
		while (!isLeaf(pos) && elements[minChild(pos)] < elements[pos]) {
			int min = minChild(pos);
			swap(min, pos);
			pos = min;
		}
	}

	void swap(int pos1, int pos2) {
		E temp = elements[pos1];
		elements[pos1] = elements[pos2];
		elements[pos2] = temp;
	}

public:
	MinHeap(int max = DEFAULT_MAX) {
		if (max < 1) {
			throw runtime_error("Error, invalid max size.");
		}
		elements = new E[max];
		this->max = max;
		size = 0;
	}

	~MinHeap() {
		delete[] elements;
	}

	void insert(E element) {
		if (size == max) {
			throw runtime_error("Error, Heap is full.");
		}
		elements[size] = element;
		siftUp(size);
		size++;
	}

	E first() {
		if (size == 0) {
			throw runtime_error("Error, heap is empty.");
		}
		return elements[0];
	}

	E removeFirst() {
		if (size == 0) {
			throw runtime_error("Error, heap is empty.");
		}
		return remove(0);
	}

	E remove(int pos) {
		if (pos < 0 || pos >= size) {
			throw runtime_error("Error, index out of bounds.");
		}
		swap(pos, size - 1);
		size--;
		if (size > 0 && pos < size) {
			siftDown(pos); 
		}
		return elements[size];
	}

	void clear() {
		size = 0;
	}

	bool isEmpty() {
		return size == 0;
	}

	int getSize() {
		return size;
	}

	void print() {
		cout << "[";
		for (int i = 0; i < size; i++) {
			cout << elements[i];
			if (i < size - 1) {
				cout << ", ";
			}
		}
		cout << "]" << endl;
	}

	// Copia los n elementos de arr al heap (reemplazando su contenido)
	// y los reordena para cumplir la condicion de heap.
	void heapify(E* arr, int n) {
		if (n < 0 || n > max) {
			throw runtime_error("Error, n exceeds heap max size.");
		}

		for (int i = 0; i < n; i++) {
			elements[i] = arr[i];
		}
		size = n;
		for (int i = size - 1; i >= 0; i--) {
			siftDown(i);
		}
	}

	// Agrega todos los elementos de other a este heap. other no se modifica.
	void merge(MinHeap<E>* other) {
		if (other == this) {
			throw runtime_error("Error, cannot merge a heap with itself.");
		}
		if (size + other->size > max) {
			throw runtime_error("Error, not enough space to merge heaps.");
		}
		for (int i = 0; i < other->size; i++) {
			insert(other->elements[i]);
		}
	}

	// Retorna una lista (memoria dinamica) con los n elementos de mayor
	// prioridad (los menores) y los elimina del heap.
	List<E>* removeTop(int n) {
		if (n < 1) {
			throw runtime_error("Error, n must be positive.");
		}
		if (n > size) {
			throw runtime_error("Error, n exceeds heap size.");
		}
		List<E>* top = new LinkedList<E>();
		for (int i = 0; i < n; i++) {
			top->append(removeFirst());
		}
		return top;
	}
};