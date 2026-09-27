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
	LinkedQueue: implementacion de Queue usando nodos enlazados con un
	nodo centinela al frente, para simplificar enqueue/dequeue.
*/

#pragma once

#include <stdexcept>
#include <iostream>
#include "Queue.h"
#include "Node.h"

using std::runtime_error;
using std::cout;
using std::endl;

template <typename E>
class LinkedQueue : public Queue<E> {
private:
	Node<E>* front;
	Node<E>* back;
	int size;

public:
	LinkedQueue() {
		//los dos apuntan al nodo sentinal/placeholder
		front = back = new Node<E>();
		size = 0;
	}

	~LinkedQueue() {
		//borra iterando los datos de la cola
		clear();
		//se borra cualquiera de los dos, pero no los dos (front o back)
		delete front;
	}

	void enqueue(E element) {
		//el orden es importante, primero backnext y despues back
		back = back->next = new Node<E>(element);
		size++;
	}

	E dequeue() {
		if (size == 0)
			throw runtime_error("Error, Queue is empty.");

		E result = front->next->element;
		Node<E>* temp = front->next->next;
		delete front->next;
		front->next = temp;
		//esto lo hacemos para que back no apunte a la nada.
		if (size == 1)
			back = front;
		size--;
		return result;
	}

	E frontValue() {
		if (size == 0)
			throw runtime_error("Error, Queue is empty.");
		return front->next->element;
	}

	void clear() {
		//se recorre mientras el centinela tenga un siguiente nodo real
		while (front->next != nullptr) {
			Node<E>* temp = front->next->next;
			delete front->next;
			front->next = temp;
		}
		size = 0;
		back = front;
	}

	bool isEmpty() {
		return size == 0;
	}

	int getSize() {
		return size;
	}

	void print() {
		cout << "[ ";
		//el ] y el salto de linea van una sola vez, al final de todo el recorrido
		for (Node<E>* temp = front->next; temp != nullptr; temp = temp->next) {
			cout << temp->element;
			//si hay otro nodo despues, separa con coma; si no, deja un espacio antes del ]
			if (temp->next != nullptr) {
				cout << ", ";
			}
			else {
				cout << " ";
			}
		}
		cout << "]" << endl;
	}
};
