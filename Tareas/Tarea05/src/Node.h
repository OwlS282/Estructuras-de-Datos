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
	// es una constructor opcional, quitarlo si se vuelve ambiguo 
	Node(Node<E>* next = nullptr) {
		this->next = next;
	}
};

