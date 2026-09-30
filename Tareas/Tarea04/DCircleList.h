/*
Instituto Tecnológico de Costa Rica

Nombre : Owel Jafet Gutiérrez Ortiz

Carnet : 2026800869

Profesor : Mauricio Avilés Cisneros

Semana 9 : Tarea Corta 4 - Listas Circulares

Fecha de entrega : 29 / 09 / 2026

*/

/*
Clase:
	DCircleList: Lista circular doblemente enlazada.
	Solo guarda un puntero current que señala al nodo ANTERIOR al frente de la lista
	(es decir, al ultimo nodo) y la cantidad de elementos.
	   frente = current->next
	   final  = current
*/

#pragma once

#include <stdexcept>
#include <iostream>
#include "CList.h"
#include "DNode.h"

using std::runtime_error;
using std::cout;
using std::endl;

template <typename E>
class DCircleList : public CList<E> {
private:
	DNode<E>* current;
	int size;

public:
	DCircleList() {
		current = nullptr;
		size = 0;
	}

	~DCircleList() {
		clear();
	}

	void insert(E element) {
		if (size == 0) {
			current = new DNode<E>(element, nullptr, nullptr);
			current->next = current;
			current->previous = current;
		}
		else {
			DNode<E>* node = new DNode<E>(element, current->next, current);
			current->next->previous = node;
			current->next = node;
		}
		size++;
	}

	void insertBack(E element) {
		insert(element);
		current = current->next; // el nuevo nodo pasa a ser el final
	}

	E remove() {
		if (size == 0) {
			throw runtime_error("Error, Circle list is empty.");
		}
		DNode<E>* temp = current->next; // nodo del frente
		E result = temp->element;
		if (size == 1) {
			current = nullptr;
		}
		else {
			current->next = temp->next;
			temp->next->previous = current;
		}
		delete temp;
		size--;
		return result;
	}

	E removeBack() {
		if (size == 0) {
			throw runtime_error("Error, Circle list is empty.");
		}
		DNode<E>* back = current;
		E result = back->element;
		if (size == 1) {
			current = nullptr;
		}
		else {
			DNode<E>* prev = current->previous;
			prev->next = current->next;
			current->next->previous = prev;
			current = prev;
		}
		delete back;
		size--;
		return result;
	}

	void clear() {
		while (size > 0) {
			remove();
		}
	}

	E getFront() {
		if (size == 0) {
			throw runtime_error("Error, Circle list is empty.");
		}
		return current->next->element;
	}

	E getBack() {
		if (size == 0) {
			throw runtime_error("Error, Circle list is empty.");
		}
		return current->element;
	}

	void next() {
		if (size > 0) {
			current = current->next;
		}
	}

	void previous() {
		if (size > 0) {
			current = current->previous;
		}
	}

	int getSize() {
		return size;
	}

	void print() {
		cout << "[";
		if (size > 0) {
			DNode<E>* temp = current->next;
			for (int i = 0; i < size; i++) {
				cout << temp->element;
				if (i < size - 1) {
					cout << ", ";
				}
				temp = temp->next;
			}
		}
		cout << "]" << endl;
	}
};