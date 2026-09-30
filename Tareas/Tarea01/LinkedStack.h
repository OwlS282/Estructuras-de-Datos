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
	LinkedStack: Implementación de pila usando una lista enlazada de nodos.
	No tiene límite de tamaño, crece dinámicamente según sea necesario.
*/

#pragma once

#include <iostream>
#include <stdexcept>
#include "Stack.h"
#include "Node.h"

using std::runtime_error;
using std::cout;
using std::endl;

//crear clases genericas
template <typename E>
class LinkedStack : public Stack<E> {
private:
	Node<E>* top;
	//tambien se puede usar unsigned int size;
	int size;

public:
	LinkedStack() {
		top = nullptr;
		size = 0;
	}
	~LinkedStack() {
		clear();
	}
	void push(E element) {
		top = new Node<E>(element, top);
		size++;
	}
	E pop() {
		if (size == 0)
			throw runtime_error("Error, stack is empty.");
		E result = top->element;
		Node<E>* temp = top->next;
		delete top;
		top = temp;
		size--;
		return result;
	}
	E topValue() {
		if (size == 0)
			throw runtime_error("Error, stack is empty.");
		return top->element;
	}
	void clear() {
		Node<E>* temp;
		while (top != nullptr) {
			temp = top->next;
			delete top;
			top = temp;
		}
		size = 0;
	}
	bool isEmpty() {
		return size == 0;
	}
	int getSize() {
		return size;
	}

	void print() {
		cout << "[ ";
		for (Node<E>* temp = top; temp != nullptr; temp = temp->next) {
			cout << temp->element;
			if (temp->next != nullptr)
				cout << ", ";
		}
		cout << " ]" << endl;
	}
};

