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
	ArrayQueue: Implementación de cola usando un arreglo circular dinámico.
	Implementada en la tarea anterior, se mantiene para referencia.
*/

#pragma once

#include <stdexcept>
#include <iostream>
#include "Queue.h"
#include "Util.h"

using std::runtime_error;
using std::cout;
using std::endl;

template <typename E>
class ArrayQueue : public Queue<E> {
private:
	E* elements;
	int front;
	int back;
	int size;
	int max;

public:
	ArrayQueue(int max = DEFAULT_MAX) {
		if (max < 1)
			throw runtime_error("Error, Invalid max size.");
		elements = new E[max];
		this->max = max;
		front = back = size = 0;
	}
	~ArrayQueue() {
		delete[] elements;
	}
	void enqueue(E element) {
		if (size == max)
			throw runtime_error("Queue is full.");
		elements[back] = element;
		back = (back + 1) % max;
		size++;
	}
	E dequeue() {
		if (size == 0)
			throw runtime_error("Error, queue is empty.");
		front = (front + 1) % max;
		size--;
		return elements[(front + max - 1) % max];
	}
	E frontValue() {
		if (size == 0)
			throw runtime_error("Error, queue is empty.");
		return elements[front];
	}
	void clear() {
		front = back = size = 0;
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
			cout << elements[(front + i) % max];
			if (i < size - 1)
				cout << ", ";
		}
		cout << "]" << endl;
	}

};

