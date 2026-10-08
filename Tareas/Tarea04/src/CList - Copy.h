/*
Instituto Tecnológico de Costa Rica

Nombre : Owel Jafet Gutiérrez Ortiz

Carnet : 2026800869

Profesor : Mauricio Avilés Cisneros

Semana 9 : Tarea Corta 4 - Listas Circulares

Fecha de entrega : 29 / 09 / 2026

*/

/*
Clase:
	CList: Clase abstracta que define la interfaz para las listas circulares.
	Define metodos virtuales puros que deben implementar CircleList y DCircleList.
*/

#pragma once

template <typename E>
class CList {
public:
	CList(const CList <E>&) = delete;
	void operator=(const CList <E>&) = delete;
	CList() {}
	virtual ~CList() {}

	virtual void insert(E element) = 0;
	virtual void insertBack(E element) = 0;
	virtual E remove() = 0;
	virtual E removeBack() = 0;
	virtual void clear() = 0;
	virtual E getFront() = 0;
	virtual E getBack() = 0;
	virtual void next() = 0;
	virtual void previous() = 0;
	virtual int getSize() = 0;
	virtual void print() = 0;
};