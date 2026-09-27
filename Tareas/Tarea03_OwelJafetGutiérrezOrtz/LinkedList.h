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
	LinkedList: Implementación de lista enlazada simple.
	Usa nodos con apuntadores al siguiente.
	Mantiene posición actual para navegación.
*/

#pragma once

#include <stdexcept>
#include <iostream>
#include "List.h"
#include "Node.h"

using std::runtime_error;
using std::cout;
using std::endl;

template<typename E>
class LinkedList : public List<E> {
private:
	Node<E>* head;  // Nodo centinela al inicio
	Node<E>* current;  // Posición actual
	Node<E>* tail;  // Último nodo
	int size;  // Cantidad de elementos

public:
	// Constructor
	LinkedList() {
		tail = current = head = new Node <E>();
		size = 0;
	}
	~LinkedList() {
		clear();
		delete head;
	}

	// Inserta en posición actual
	void insert(E element) {
		current->next = new Node<E>(element, current->next);
		if (current == tail)
			tail = current->next;
		size++;
	}

	// Agrega al final
	void append(E element) {
		tail = tail->next = new Node<E>(element);
		size++;
	}

	// Reemplaza elemento actual
	void setElement(E element) {
		if (size == 0)
			throw runtime_error("Error, list is empty.");
		if (current == tail)
			throw runtime_error("Error, not current element.");
		current->next->element = element;
	}

	// Elimina elemento actual
	E remove() {
		if (size == 0)
			throw runtime_error("Error, list is empty.");
		if (current == tail)
			throw runtime_error("Error, not current element.");
		E result = current->next->element;
		Node<E>* temp = current->next->next;
		delete current->next;
		current->next = temp;
		if (size == 1)
			tail = current;
		size--;
		return result;
	}

	// Limpia la lista
	void clear() {
		while (head->next != nullptr) {
			Node<E>* temp = head->next->next;
			delete head->next;
			head->next = temp;
		}
		tail = current = head;
		size = 0;
	}

	// Obtiene elemento actual
	E getElement() {
		if (size == 0)
			throw runtime_error("Error, list is empty.");
		if (current == tail)
			throw runtime_error("Error, not current element.");
		return current->next->element;
	}

	// Mueve al inicio
	void goToStart() {
		current = head;
	}

	// Mueve al final
	void goToEnd() {
		current = tail;
	}

	// Mueve a la posicion actual
	void goToPos(int pos) {
		if (pos < 0 || pos > size)
			throw runtime_error("Error, index out of range.");
		current = head;
		for (int i = 0; i < pos; i++)
			current = current->next;
	}

	// Mueve al siguiente
	void next() {
		if (current != tail)
			current = current->next;
	}

	// Mueve al anterior
	void previous() {
		if (current != head) {
			Node<E>* temp = head;
			while (temp->next != current) {
				temp = temp->next;
			}
			current = temp;
		}
	}

	// Verifica si está al final
	bool atEnd() {
		return current == tail;
	}

	// Verifica si está al inicio
	bool atStart() {
		return current == head;
	}

	// Obtiene posición actual
	int getPos() {
		int pos = 0;
		Node<E>* temp = head;
		while (temp != current) {
			temp = temp->next;
			pos++;
		}
		return pos;
	}

	// Obtiene tamaño
	int getSize() {
		return size;
	}

	// Imprime la lista
	void print() {
		cout << "[";
		Node<E>* temp = head->next;
		while (temp != nullptr) {
			cout << temp->element;
			if (temp != tail) {
				cout << ", ";
			}
			temp = temp->next;
		}
		cout << "]" << endl;
	}
};

