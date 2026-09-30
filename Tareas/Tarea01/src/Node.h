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
	Node: Estructura que representa un nodo en una lista enlazada.
	Contiene un elemento y un puntero al siguiente nodo.
*/

#pragma once

template <typename	E>
class Node{
public:
	E element;
	Node<E>* next;
							//hay una alternativa de inicializarlo en nullptr o dejarlo sin.
	Node(E element, Node<E>* next = nullptr) {
		this->element = element;
		this->next = next;
	}
};

