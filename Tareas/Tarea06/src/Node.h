/*
Instituto Tecnologico de Costa Rica

Nombre : Owel Jafet Gutierrez Ortiz

Carnet : 2026800869

Profesor : Mauricio Aviles Cisneros

Semana 14 : Tarea Corta 6 - Heaps

Fecha de entrega : 06 / 11 / 2026

*/

/*
Clase Node:
	Nodo de una lista enlazada. Guarda un elemento y un puntero al siguiente
	nodo.
*/
#pragma once

template <typename E>
class Node {
public:
	E element;
	Node<E>* next;

	Node(E element, Node<E>* next = nullptr) {
		this->element = element;
		this->next = next;
	}

	Node(Node<E>* next = nullptr) {
		this->next = next;
	}
};

