/*
Instituto Tecnológico de Costa Rica

Nombre : Owel Jafet Gutiérrez Ortiz

Carnet : 2026800869

Profesor : Mauricio Avilés Cisneros

Semana 6 : Tarea Corta 2 – Colas: Atención de Emergencias

Fecha de entrega : 10 / 09 / 2026

*/

/*
Clase:
	LinkedPriorityQueue: implementacion de PriorityQueue usando un arreglo
	de LinkedQueue, una cola por cada prioridad posible.
*/

#pragma once

#include <stdexcept>
#include <iostream>
#include "PriorityQueue.h"
#include "LinkedQueue.h"

using std::runtime_error;
using std::cout;
using std::endl;

template <typename E>
class LinkedPriorityQueue : public PriorityQueue<E> {
private:
	LinkedQueue<E>* queues; //arreglo de colas, una por cada prioridad
	int priorities; //cantidad maxima de prioridades
	int size; //cantidad de elementos en toda la estructura

public:
	LinkedPriorityQueue(int priorities = 20) {
		if (priorities <= 0)
			throw runtime_error("Error, priorities must be positive.");

		this->priorities = priorities;
		queues = new LinkedQueue<E>[priorities];
		size = 0;
	}

	~LinkedPriorityQueue() {
		//el delete[] llama al destructor de cada LinkedQueue del arreglo
		delete[] queues;
	}

	void insert(E element, int priority) {
		if (priority < 0 || priority >= priorities)
			throw runtime_error("Error, invalid priority.");

		queues[priority].enqueue(element);
		size++;
	}

	E min() {
		if (isEmpty())
			throw runtime_error("Error, PriorityQueue is empty.");

		//se busca la primera cola no vacia, de mayor a menor prioridad
		for (int i = 0; i < priorities; i++) {
			if (!queues[i].isEmpty())
				return queues[i].frontValue();
		}

		//nunca deberia llegar aqui, pero el compilador pide un retorno
		throw runtime_error("Error, PriorityQueue is empty.");
	}

	E removeMin() {
		if (isEmpty())
			throw runtime_error("Error, PriorityQueue is empty.");

		for (int i = 0; i < priorities; i++) {
			if (!queues[i].isEmpty()) {
				E result = queues[i].dequeue();
				size--;
				return result;
			}
		}

		throw runtime_error("Error, PriorityQueue is empty.");
	}

	void clear() {
		for (int i = 0; i < priorities; i++) {
			queues[i].clear();
		}
		size = 0;
	}

	int getSize() {
		return size;
	}

	bool isEmpty() {
		return size == 0;
	}

	void print() {
		for (int i = 0; i < priorities; i++) {
			cout << i << ": ";
			queues[i].print();
		}
	}
};
