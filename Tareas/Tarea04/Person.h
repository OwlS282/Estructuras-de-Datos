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
	Person: Representa a un jugador de "Zapatito Cochinito".
	Guarda el nombre y el pie que esta usando (false = derecho, true = izquierdo).
*/

#pragma once

#include <string>
#include <iostream>

using std::string;
using std::ostream;

class Person {
public:
	string name;
	bool leftFoot;

	Person() {
		name = "";
		leftFoot = false;
	}

	Person(string name) {
		this->name = name;
		this->leftFoot = false;
	}
};

inline ostream& operator<<(ostream& out, const Person& person) {
	out << person.name << " (" << (person.leftFoot ? "pie izquierdo" : "pie derecho") << ")";
	return out;
}