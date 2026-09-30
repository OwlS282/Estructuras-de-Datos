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
	main: programa principal del triage de emergencias. Muestra el menu,
	lee y valida la entrada del usuario, e ingresa/atiende pacientes usando
	una LinkedPriorityQueue<Patient>.
*/

#include <iostream>
#include <string>
#include <exception>
#include "LinkedPriorityQueue.h"
#include "Patient.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::getline;
using std::stoi;
using std::exception;
using std::invalid_argument;
using std::out_of_range;

const int NIVELES = 5; //cantidad de prioridades: 1-Azul ... 5-Blanco

int leerEntero(string mensaje, int minimo, int maximo);
string leerTexto(string mensaje);
void mostrarEstado(LinkedPriorityQueue<Patient>& cola);
void ingresarPaciente(LinkedPriorityQueue<Patient>& cola);
void atenderPaciente(LinkedPriorityQueue<Patient>& cola);

int main() {
	LinkedPriorityQueue<Patient> cola(NIVELES);
	int opcion;

	do {
		mostrarEstado(cola);
		opcion = leerEntero("Opcion: ", 1, 3);

		try {
			switch (opcion) {
			case 1:
				ingresarPaciente(cola);
				break;
			case 2:
				atenderPaciente(cola);
				break;
			case 3:
				cout << "Hasta luego." << endl;
				break;
			}
		}
		catch (exception& e) {
			cout << "Error: " << e.what() << endl;
		}

		cout << endl;
	} while (opcion != 3);

	//cola es un objeto de la pila, su destructor libera el arreglo interno
	//de LinkedQueue automaticamente al salir de main
	return 0;
}

void mostrarEstado(LinkedPriorityQueue<Patient>& cola) {
	cout << "TRIAGE - Cola de espera:" << endl;
	cola.print();
	cout << endl;
	cout << "1. Ingresar paciente" << endl;
	cout << "2. Atender paciente" << endl;
	cout << "3. Salir" << endl;
}

void ingresarPaciente(LinkedPriorityQueue<Patient>& cola) {
	string id = leerTexto("ID: ");
	int nivel = leerEntero("CONDICION (1-Azul, 2-Rojo, 3-Amarillo, 4-Verde, 5-Blanco): ", 1, 5);

	Patient paciente(id, nivel);
	//los niveles van de 1 a 5, pero la cola de prioridad usa indices de 0 a 4
	cola.insert(paciente, nivel - 1);
}

void atenderPaciente(LinkedPriorityQueue<Patient>& cola) {
	if (cola.isEmpty()) {
		cout << "No hay pacientes en espera." << endl;
		return;
	}

	Patient paciente = cola.removeMin();
	paciente.attend();

	cout << "PACIENTE EN ATENCION:" << endl;
	paciente.print();
}

string leerTexto(string mensaje) {
	string linea;
	bool valido = false;

	do {
		cout << mensaje;
		getline(cin, linea);

		if (linea.empty())
			cout << "Entrada invalida, intente de nuevo." << endl;
		else
			valido = true;
	} while (!valido);

	return linea;
}

int leerEntero(string mensaje, int minimo, int maximo) {
	string linea;
	int valor = 0;
	bool valido = false;

	do {
		cout << mensaje;
		getline(cin, linea);

		try {
			valor = stoi(linea);
			if (valor < minimo || valor > maximo)
				throw out_of_range("fuera de rango");
			valido = true;
		}
		catch (exception&) {
			cout << "Entrada invalida, intente de nuevo." << endl;
		}
	} while (!valido);

	return valor;
}
