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
	DLinkedList: Implementación de lista doblemente enlazada.
	Usa nodos con apuntadores al siguiente y anterior.
	Permite navegación en ambas direcciones.
*/

#pragma once

#include <stdexcept>
#include <iostream>
#include "List.h"
#include "DNode.h"

using std::runtime_error;
using std::cout;
using std::endl;

template<typename E>
class DLinkedList : public List<E> {
private:
	DNode<E>* head;  // Nodo centinela al inicio
	DNode<E>* tail;  // Nodo centinela al final
	DNode<E>* current;  // Posición actual
	int size;  // Cantidad de elementos

public:
	DLinkedList() {
		// Creación de nodos centinela
		current = head = new DNode<E>(nullptr, nullptr);
		tail = new DNode<E>(nullptr, head);
		size = 0;
	}

	~DLinkedList() {
		clear();
		delete head;
		delete tail;
	}

	// Inserta en posición actual
	void insert(E element) {
		current->next = new DNode<E>(element, current->next, current);
		current->next->next->previous = current->next;
		size++;
	}

	// Agrega al final
	void append(E element) {
		tail->previous->next = new DNode<E>(element, tail, tail->previous);
		tail->previous = tail->previous->next;
		size++;
	}

	// Reemplaza elemento actual
	void setElement(E element) {
		if (size == 0)
			throw runtime_error("Error, List is empty.");
		if (current->next == tail)
			throw runtime_error("Error, no current element.");
		current->next->element = element;
	}

	// Elimina elemento actual
	E remove() {
		if (size == 0)
			throw runtime_error("Error, List is empty.");
		if (current->next == tail)
			throw runtime_error("Error, no current element.");
		E result = current->next->element;
		current->next = current->next->next;
		delete current->next->previous;
		current->next->previous = current;
		size--;
		return result;
	}

	// Limpia la lista
	void clear() {
		current = head;
		while (current->next != tail) {
			current->next = current->next->next;
			delete current->next->previous;
		}
		tail->previous = head;
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
		current = tail->previous;
	}

	// Mueve a posición específica
	void goToPos(int pos) {
		if (pos < 0 || pos > size)
			throw runtime_error("Error, index out of range.");
		current = head;
		for (int i = 0; i < pos; i++)
			current = current->next;
	}

	// Avanza una posición
	void next() {
		if (current != tail->previous)
			current = current->next;
	}

	// Retrocede una posición
	void previous() {
		if (current != head)
			current = current->previous;
	}

	// Verifica si está al final
	bool atEnd() {
		return current == tail->previous;
	}

	// Verifica si está al inicio
	bool atStart() {
		return current == head;
	}

	// Obtiene posición actual
	int getPos() {
		DNode<E>* temp = head;
		int pos = 0;
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
		DNode<E>* temp = head->next;
		while (temp != tail) {
			cout << temp->element;
			if (temp != tail->previous) {
				cout << ", ";
			}
			temp = temp->next;
		}
		cout << "]" << endl;
	}
};

