/*
Instituto Tecnologico de Costa Rica

Nombre : Owel Jafet Gutierrez Ortiz

Carnet : 2026800869

Profesor : Mauricio Aviles Cisneros

Semana 12 : Tarea Corta 5 - Radix Sort

Fecha de entrega : 22 / 10 / 2026

*/

/*
Clase List:
	Clase abstracta que define la interfaz del TDA Lista (insertar, agregar,
	eliminar, recorrer, obtener el elemento actual y el tamano). Las clases
	que la heredan, como LinkedList, implementan estas operaciones.
*/

#pragma once

template <typename E>
class List {
public:
	List(const List <E>&) = delete;
	void operator=(const List <E>&) = delete;
	List() {}
	virtual ~List() {}
	virtual void insert(E element) = 0;
	virtual void append(E element) = 0;
	virtual void setElement(E element) = 0;
	virtual E remove() = 0;
	virtual void clear() = 0;
	virtual E getElement() = 0;
	virtual void goToStart() = 0;
	virtual void goToEnd() = 0;
	virtual void goToPos(int pos) = 0;
	virtual void next() = 0;
	virtual	void previous() = 0;
	virtual bool atEnd() = 0;
	virtual bool atStart() = 0;
	virtual int getPos() = 0;
	virtual int getSize() = 0;
	virtual void print() = 0;


};

