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
	PriorityQueue: TAD abstracto de una cola de prioridad generica. Solo
	declara las operaciones (insert, min, removeMin, etc.), sin implementarlas.
*/

#pragma once

template <typename E>
class PriorityQueue {
public:
	PriorityQueue(const PriorityQueue<E>&) = delete;
	void operator = (const PriorityQueue<E>&) = delete;
	PriorityQueue() {}
	virtual ~PriorityQueue() {}
	virtual void insert(E element, int priority) = 0;
	virtual E min() = 0;
	virtual E removeMin() = 0;
	virtual void clear() = 0;
	virtual int getSize() = 0;
	virtual bool isEmpty() = 0;
	virtual void print() = 0;
};
