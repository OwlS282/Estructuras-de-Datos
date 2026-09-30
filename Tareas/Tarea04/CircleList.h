/*
Instituto Tecnolégico de Costa Rica

Nombre : Owel Jafet Gutiérrez Ortiz

Carnet : 2026800869

Profesor : Mauricio Avilés Cisneros

Semana 9 : Tarea Corta 4 - Listas Circulares

Fecha de entrega : 29 / 09 / 2026

*/

/*
Clase:
	CircleList: Lista circular simplemente enlazada.
	Solo guarda un puntero current que senala al nodo ANTERIOR al frente de la lista
	(es decir, al ultimo nodo) y la cantidad de elementos.
	   frente = current->next
	   final  = current
*/

#pragma once

#include <stdexcept>
#include <iostream>
#include "CList.h"
#include "Node.h"

using std::runtime_error;
using std::cout;
using std::endl;

template <typename E>
class CircleList : public CList<E> {
private:
	Node<E>* current;
	int size;

public:
	CircleList() {
		current = nullptr;
		size = 0;
	}

	~CircleList() {
		clear();
	}

	void insert(E element) {
		if (size == 0) {
			current = new Node<E>(element);
			current->next = current;
		}
		else {
			current->next = new Node<E>(element, current->next);
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
		Node<E>* temp = current->next; // nodo del frente
		E result = temp->element;
		if (size == 1) {
			current = nullptr;
		}
		else {
			current->next = temp->next;
		}
		delete temp;
		size--;
		return result;
	}

	E removeBack() {
		if (size == 0) {
			throw runtime_error("Error, Circle list is empty.");
		}
		Node<E>* back = current;
		E result = back->element;
		if (size == 1) {
			current = nullptr;
		}
		else {
			// buscamos el nodo anterior al final
			Node<E>* prev = current->next;
			while (prev->next != current) {
				prev = prev->next;
			}
			prev->next = current->next;
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
			Node<E>* temp = current;
			while (temp->next != current) {
				temp = temp->next;
			}
			current = temp;
		}
	}

	int getSize() {
		return size;
	}

	void print() {
		cout << "[";
		if (size > 0) {
			Node<E>* temp = current->next;
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