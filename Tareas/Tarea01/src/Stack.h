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
	Stack: Clase abstracta base que define la interfaz para todas las pilas.
	Define los métodos virtuales puros que debe implementar cualquier pila.
*/

#pragma once

template <typename E> // clase generica
class Stack { // como se llama la clase

public:
	//asignacion
	Stack() {}
	Stack(const Stack<E>&) = delete;
	void operator= (const Stack<E>&) = delete; // proteccion de la asignacion y del contrusctor de copia
	virtual ~Stack() {}
	virtual void push(E element) = 0;
	
	//definimos los metodos
	virtual E pop() = 0;
	virtual E topValue() = 0;
	virtual void clear() = 0;
	virtual bool isEmpty() = 0;
	virtual int  getSize() = 0;
	virtual void print() = 0;
};