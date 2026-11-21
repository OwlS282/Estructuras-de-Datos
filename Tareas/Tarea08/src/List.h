/*
Instituto Tecnologico de Costa Rica

Nombre : Owel Jafet Gutierrez Ortiz

Carnet : 2026800869

Profesor : Mauricio Aviles Cisneros

Semana 16 : Tarea Corta 8 - Árboles de búsqueda binaria y diccionarios

Fecha de entrega : 19 / 11 / 2026

*/

/*
Clase List:
	Interfaz (clase abstracta) que define las operaciones de una lista:
	insertar, agregar al final, eliminar, consultar y modificar el elemento
	actual, y moverse por la lista. Las clases que la implementan, como
	LinkedList, definen cada una de esas operaciones.
*/

#pragma once

template <typename E>
class List {
public:
	List(const List<E>&) = delete;
	List() {}
	virtual ~List() {}
	virtual void insert(E element) = 0;
	virtual void append(E element) = 0;
	virtual	void setElement(E element) = 0;
	virtual E remove() = 0;
	virtual void clear() = 0;
	virtual E getElement() = 0;
	virtual void goToStart() = 0;
	virtual void goToEnd() = 0;
	virtual void goToPos(int pos) = 0;
	virtual void next() = 0;
	virtual void previous() = 0;
	virtual bool atEnd() = 0;
	virtual bool atStart() = 0;
	virtual int getPos() = 0;
	virtual int getSize() = 0;
	virtual void print() = 0;
};

