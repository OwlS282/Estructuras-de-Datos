/*
Instituto Tecnológico de Costa Rica

Nombre : Owel Jafet Gutiérrez Ortiz

Carnet : 2026800869

Profesor : Mauricio Avilés Cisneros

Semana 8 : Tarea Corta 3 – Lista: Caja de Herramientas

Fecha de entrega : 24 / 09 / 2026

*/

/*
Clase:
	Tool: Representa una herramienta con nombre, peso y volumen.
	Implementa el operador << para imprimir herramientas.
*/

#pragma once

#include <string>
#include <iostream>
#include <iomanip>

using std::string;
using std::cout;
using std::ostream;
using std::fixed;
using std::setprecision;

class Tool {
public:
	string name;  // Nombre de la herramienta
	double weight;  // Peso de la herramienta
	double volume;  // Volumen de la herramienta

	// Constructor vacío
	Tool() {
		name = "";
		weight = 0.0;
		volume = 0.0;
	}

	// Constructor con parámetros
	Tool(string name, double weight, double volume) {
		this->name = name;
		this->weight = weight;
		this->volume = volume;
	}

	~Tool() {}

	// Operador para imprimir herramienta (nombre, peso, volumen)
	// Usa fixed y setprecision(2) para mostrar decimales con 2 dígitos
	friend ostream& operator<<(ostream& os, const Tool& tool) {
		os << tool.name << " (w=" << fixed << setprecision(2)
			<< tool.weight << ", v=" << tool.volume << ")";
		return os;
	}
};