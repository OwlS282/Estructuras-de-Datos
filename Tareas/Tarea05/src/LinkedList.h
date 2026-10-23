/*
Instituto Tecnologico de Costa Rica

Nombre : Owel Jafet Gutierrez Ortiz

Carnet : 2026800869

Profesor : Mauricio Aviles Cisneros

Semana 12 : Tarea Corta 5 - Radix Sort

Fecha de entrega : 22 / 10 / 2026

*/

/*
Clase LinkedList:
	Implementacion de la lista enlazada simple. Guarda los elementos en nodos
	enlazados y permite agregar, insertar, eliminar y recorrer elementos.
	En esta tarea se usa para almacenar los numeros a ordenar y para
	construir los baldes del Radix Sort.
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
	Node<E>* head;
	Node<E>* current;
	Node<E>* tail;
	int size;

public:
	LinkedList() {
		tail = current = head = new Node <E>();
		size = 0;
	}
	~LinkedList() {
		clear();
		delete head;
	}
	void insert(E element) {
		current->next = new Node<E>(element, current->next);
		if (current == tail)
			tail = current->next;
		size++;
	}
	void append(E element) {
		tail = tail->next = new Node<E>(element);
		size++;
	}
	void setElement(E element) {
		if (size == 0)
			throw runtime_error("Error, list is empty.");
		if (current == tail)
			throw runtime_error("Error, not current element.");
		current->next->element = element;
	}
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
	void clear() {
		while (head->next != nullptr) {
			Node<E>* temp = head->next->next;
			delete head->next;
			head->next = temp;
		}
		tail = current = head;
		size = 0;
	}
	E getElement() {
		if (size == 0)
			throw runtime_error("Error, list is empty.");
		if (current == tail)
			throw runtime_error("Error, not current element.");
		return current->next->element;
	}
	void goToStart() {
		current = head;
	}
	void goToEnd() {
		current = tail;
	}
	void goToPos(int pos) {
		if (pos < 0 || pos > size)
			throw runtime_error("Error, index out of range.");
		current = head;
		for (int i = 0; i < pos; i++)
			current = current->next;
	}
	void next() {
		if (current != tail)
			current = current->next;
	}
	void previous() {
		if (current != head) {
			Node<E>* temp = head;
			while (temp->next != current) {
				temp = temp->next;
			}
			current = temp;
		}
	}

	bool atEnd() {
		return current == tail;
	}

	bool atStart() {
		return current == head;
	}

	int getPos() {
		int pos = 0;
		Node<E>* temp = head;
		while (temp != current) {
			temp = temp->next;
			pos++;
		}
		return pos;
	}
	int getSize() {
		return size;
	}
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

