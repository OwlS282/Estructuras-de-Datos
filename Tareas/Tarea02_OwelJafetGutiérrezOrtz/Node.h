/*
Instituto Tecnológico de Costa Rica

Nombre : Owel Jafet Gutiérrez Ortiz

Carnet : 2026800869

Profesor : Mauricio Avilés Cisneros

Semana 6 : Tarea Corta 2 – Colas: Atención de Emergencias

Fecha de entrega : 10 / 09 / 2026

*/

/*
Clase:
	Node: nodo generico enlazado, usado internamente por LinkedQueue para
	guardar cada elemento junto con un puntero al siguiente nodo.
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
