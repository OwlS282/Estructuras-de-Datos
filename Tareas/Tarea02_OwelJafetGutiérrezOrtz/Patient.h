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
	Patient: declaracion de la clase de logica que representa a un
	paciente que ingresa a emergencias (id, nivel, horas de llegada/atencion).
*/

#pragma once

#include <string>
#include <ctime> // manejo de horas
#include <iostream>

using std::string;
using std::ostream;

class Patient {
private:
	//id del usuario
	string id;
	// nivel de emergencia
	int level;
	//hora de llegada
	time_t arrival;
	//hora de atendido
	time_t attended;
	//tiempo que espero
	time_t waitingTime;

	//metodos de apoyo, solo se usan dentro de la clase
	string conditionText();
	//le damos formato
	string formatTime(time_t t);

public:
	//creamos el paciente nuevo
	Patient(string id, int level);
	Patient(); //constructor por defecto
	//lo marcamos como atendido, guarda la hora y calcula la espera
	void attend();
	//imprimimos en patalla
	void print();

	//permitimos hacer un print del paciente
	friend ostream& operator<<(ostream& os, const Patient& p);
};
