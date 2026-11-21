/*
Instituto Tecnologico de Costa Rica

Nombre : Owel Jafet Gutierrez Ortiz

Carnet : 2026800869

Profesor : Mauricio Aviles Cisneros

Semana 16 : Tarea Corta 8 - Árboles de búsqueda binaria y diccionarios

Fecha de entrega : 19 / 11 / 2026

*/

/*
Clase Node:
	Nodo simple de una lista enlazada. Guarda un elemento y un puntero
	al siguiente nodo. Es la unidad básica que usa LinkedList para
	almacenar sus datos.
*/

#pragma once

template <typename	E>
class Node {
public:
	E element;
	Node<E>* next;

	//hay una alternativa de inicializarlo en nullptr o dejarlo sin.
	Node(E element, Node<E>* next = nullptr) {
		this->element = element;
		this->next = next;
	}
	// es una constructor opcional, quitarlo si se vuelve ambiguo 
	Node(Node<E>* next = nullptr) {
		this->next = next;
	}
};