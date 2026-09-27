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
	DNode: Nodo para listas doblemente enlazadas.
	Contiene un elemento genérico y apuntadores al siguiente y anterior nodo.
*/

#pragma once

template <typename E>
class DNode {
public:
	E element;  // Dato almacenado
	DNode<E>* next;  // puntero al siguiente nodo
	DNode<E>* previous;  // puntero al nodo anterior

	// Constructor con elemento, siguiente y anterior
	DNode(E element, DNode<E>* next, DNode<E>* previous) {
		this->element = element;
		this->next = next;
		this->previous = previous;
	}

	// Constructor sin elemento (para nodo centinela)
	DNode(DNode<E>* next, DNode<E>* previous) {
		this->next = next;
		this->previous = previous;
	}
};