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
	Patient: implementacion de los metodos declarados en Patient.h
	(constructores, attend, print y el operador de extraccion <<).
*/

#define _CRT_SECURE_NO_WARNINGS // sirve para ocultar unas alertas

#include "Patient.h"
#include <sstream>

using std::cout;
using std::endl;
using std::ostringstream;

Patient::Patient(string id, int level) {
	this->id = id;
	this->level = level;
	arrival = time(nullptr); //hora actual
	attended = 0;
	waitingTime = 0;
}

Patient::Patient() {
	id = "";
	level = 0;
	arrival = 0;
	attended = 0;
	waitingTime = 0;
}

void Patient::attend() {
	attended = time(nullptr);
	waitingTime = attended - arrival;
}

string Patient::conditionText() {
	//devuelve el nivel, el nombre y la descripcion, tal como pide el enunciado
	switch (level) {
	case 1: return "1 AZUL - Resucitacion";
	case 2: return "2 ROJO - Emergencia";
	case 3: return "3 AMARILLO - Urgente";
	case 4: return "4 VERDE - Menos urgente";
	case 5: return "5 BLANCO - No urgente";
	default: return "Desconocida";
	}
}

string Patient::formatTime(time_t t) {
	struct tm* info = localtime(&t);
	ostringstream oss;
	oss << (info->tm_year + 1900) << "-" << (info->tm_mon + 1) << "-" << info->tm_mday
		<< " " << info->tm_hour << ":" << info->tm_min << ":" << info->tm_sec;
	return oss.str();
}

void Patient::print() {
	cout << "ID: " << id << endl;
	cout << "CONDICION: " << conditionText() << endl;
	cout << "LLEGADA: " << formatTime(arrival) << endl;
	cout << "ATENDIDO: " << formatTime(attended) << endl;
	cout << "ESPERA: " << waitingTime << " s" << endl;
}

ostream& operator<<(ostream& os, const Patient& p) {
	os << "(Id: " << p.id << ", Nivel: " << p.level << ")";
	return os;
}