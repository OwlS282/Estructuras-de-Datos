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
	Queue: TAD abstracto de una cola FIFO generica. Solo declara las
	operaciones (enqueue, dequeue, frontValue, etc.), sin implementarlas.
*/

#pragma once

template <typename E>
class Queue {
public:
	Queue(const Queue<E>&) = delete;
	void operator = (const Queue<E>&) = delete;
	Queue() {} // si tiene llaves lleva no lleva ; , sino no lleva. 
	virtual ~Queue() {}
	virtual void enqueue(E element) = 0;
	virtual E dequeue() = 0;
	virtual E frontValue() = 0;
	virtual void clear() = 0;
	virtual bool isEmpty() = 0;
	virtual int getSize() = 0;
	virtual void print() = 0;
};
