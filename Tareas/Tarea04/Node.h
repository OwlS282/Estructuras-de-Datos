/*
Instituto Tecnológico de Costa Rica

Nombre : Owel Jafet Gutiérrez Ortiz

Carnet : 2026800869

Profesor : Mauricio Avilés Cisneros

Semana 9 : Tarea Corta 4 – Listas Circulares

Fecha de entrega : 29 / 09 / 2026

*/

/*
Clase:
	Node: Nodo para listas enlazadas simples.
	Contiene un elemento genérico y un apuntador al siguiente nodo.
*/


#pragma once

template <typename	E>
class Node {
public:
	E element;  // Dato almacenado
	Node<E>* next;  // puntero al siguiente nodo

	// Constructor con elemento y siguiente
	Node(E element, Node<E>* next = nullptr) {
		this->element = element;
		this->next = next;
	}
	// Constructor sin elemento (para nodo centinela)
	Node(Node<E>* next = nullptr) {
		this->next = next;
	}
};
