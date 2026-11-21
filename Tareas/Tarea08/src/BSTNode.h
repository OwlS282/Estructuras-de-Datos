/*
Instituto Tecnologico de Costa Rica

Nombre : Owel Jafet Gutierrez Ortiz

Carnet : 2026800869

Profesor : Mauricio Aviles Cisneros

Semana 16 : Tarea Corta 8 - Árboles de búsqueda binaria y diccionarios

Fecha de entrega : 19 / 11 / 2026

*/

/*
Clase BSTNode:
	Nodo de un árbol de búsqueda binaria. Guarda un elemento y punteros
	a sus hijos izquierdo y derecho. Ofrece métodos para conocer la
	cantidad de hijos que tiene y para obtener su único hijo, lo que
	facilita la eliminación de nodos en el árbol.
*/

#pragma once

template <typename E>
class BSTNode {
public:
	E element;
	BSTNode<E>* left;
	BSTNode<E>* right;

	BSTNode(E element, BSTNode<E>* left, BSTNode<E>* right) {
		this->element = element;
		this->left = left;
		this->right = right;
	}

	BSTNode(E element) {
		this->element = element;
		left = right = nullptr;
	}

	// Cantidad de hijos: 0, 1 o 2
	int childrenCount() {
		return (left == nullptr ? 0 : 1) + (right == nullptr ? 0 : 1);
	}

	// Solo se usa cuando el nodo tiene exactamente un hijo
	BSTNode<E>* getOnlyChild() {
		return (left == nullptr ? right : left);
	}
};
