/*
Instituto Tecnologico de Costa Rica

Nombre : Owel Jafet Gutierrez Ortiz

Carnet : 2026800869

Profesor : Mauricio Aviles Cisneros

Semana 9 : Tarea Corta 4 - Listas Circulares

Fecha de entrega : 29 / 09 / 2026

*/

/*
Programa Principal:
	Juego "Zapatito Cochinito" (version del problema de Flavio Josefo).
	Permite elegir la cantidad de personas, el tipo de lista circular
	(CircleList o DCircleList) y el modo de juego (regular o dirigido).
*/

#include <iostream>
#include <string>
#include <stdexcept>
#include "CList.h"
#include "CircleList.h"
#include "DCircleList.h"
#include "Person.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::getline;
using std::to_string;
using std::runtime_error;

const int JUMPS = 8;      // la rima tiene 9 partes = 8 saltos
const int LEFT = 1;       // sentido de las manecillas del reloj
const int RIGHT = 2;      // sentido contrario a las manecillas del reloj

// Lista de nombres predeterminados
const int DEFAULT_NAMES_COUNT = 50;
string defaultNames[DEFAULT_NAMES_COUNT] = {
	"Isabel", "Eugenia", "Mario", "Sandra", "Camilo",
	"Andrea", "Luis", "Daniela", "Jose", "Valeria",
	"Carlos", "Fernanda", "Diego", "Paola", "Esteban",
	"Sofia", "Kevin", "Laura", "Marco", "Natalia",
	"Owel", "Jonathan", "David", "Dennys", "Alexander",
	"Mohamed", "Juan", "Jafet", "Loana", "Melany",
	"Melania", "Kathy", "Bismarck", "Miguel", "Liam",
	"Yahir", "Israel", "Samantha", "Amanda", "Alberto",
	"Sofia", "Marilyn", "Edwin", "Joshua", "Solangel",
	"Jair", "Zoe", "Yessenia", "Eduardo", "Johana"
};

// Limpia el buffer de entrada, lo que nos evita errores
void static clearInput() {
	cin.clear();
	cin.ignore(1000000, '\n');
}

// Obtiene entrada valida dentro de rango especificado
int static getValidInput(int minValue, int maxValue) {
	int value = 0;
	bool validInput = false;

	while (!validInput) {
		if (!(cin >> value)) { // Verifica que sea numero valido
			clearInput();
			cout << "Error: Ingrese un numero valido." << endl;
			cout << "Opcion: ";
			continue;
		}

		if (value < minValue || value > maxValue) { // Verifica que este en rango
			cout << "Error: La opcion debe estar entre " << minValue << " y " << maxValue << "." << endl;
			cout << "Opcion: ";
			continue;
		}

		validInput = true;
	}

	clearInput();
	return value;
}

// Pregunta la direccion del siguiente conteo
int static askDirection() {
	cout << "\nDireccion del siguiente conteo:" << endl;
	cout << "1. Izquierda (sentido de las manecillas del reloj)" << endl;
	cout << "2. Derecha (sentido contrario a las manecillas del reloj)" << endl;
	cout << "Opcion: ";
	return getValidInput(1, 2);
}

// Llena la lista con las personas del juego
void static fillList(CList<Person>* list, int amount, int nameMode) {
	for (int i = 0; i < amount; i++) {
		string name;
		if (nameMode == 1) {
			if (i < DEFAULT_NAMES_COUNT) {
				name = defaultNames[i];
			}
			else {
				name = "Persona " + to_string(i + 1);
			}
		}
		else {
			cout << "Nombre de la persona " << (i + 1) << ": ";
			getline(cin, name);
			if (name == "") {
				name = "Persona " + to_string(i + 1);
			}
		}
		list->insertBack(Person(name));
	}
}

int main() {
	int amount = 0;
	int nameMode = 0;
	int listType = 0;
	int gameMode = 0;
	CList<Person>* list = nullptr;

	try {
		// Cantidad de personas
		cout << "Zapatito Cochinito" << endl;
		cout << "\nCantidad de personas (2 a 50): ";
		amount = getValidInput(2, 50);

		// Nombres
		cout << "\nComo desea asignar los nombres?" << endl;
		cout << "1. Automaticamente (lista predeterminada)" << endl;
		cout << "2. Ingresarlos manualmente" << endl;
		cout << "Opcion: ";
		nameMode = getValidInput(1, 2);

		// Tipo de lista
		cout << "\nElija el tipo de lista a utilizar:" << endl;
		cout << "1. CircleList" << endl;
		cout << "2. DCircleList" << endl;
		cout << "Opcion: ";
		listType = getValidInput(1, 2);

		// Modo de juego
		cout << "\nElija el modo de juego:" << endl;
		cout << "1. Regular (los conteos siempre van hacia la izquierda)" << endl;
		cout << "2. Dirigido (usted elige la direccion de cada conteo)" << endl;
		cout << "Opcion: ";
		gameMode = getValidInput(1, 2);

		if (listType == 1) {
			list = new CircleList<Person>();
		}
		else {
			list = new DCircleList<Person>();
		}
		cout << endl;
		fillList(list, amount, nameMode);

		// El frente de la lista es siempre la persona donde inicia el conteo
		bool firstCount = true;
		bool lastEliminated = false;
		int round = 0;

		while (list->getSize() > 1) {
			round++;
			int direction = LEFT;
			if (gameMode == 2) {
				direction = askDirection();
			}

			// Ubicar el inicio del conteo a la par de la ultima persona elegida.
			// Si la ultima persona cambio de pie, el frente es ella misma.
			// Si fue eliminada, el frente ya es la persona siguiente (a la izquierda).
			if (!firstCount) {
				if (direction == LEFT) {
					if (!lastEliminated) {
						list->next();
					}
				}
				else {
					list->previous();
				}
			}
			firstCount = false;

			cout << "\n ——————————————————————— Conteo " << round << " ———————————————————————" << endl;
			cout << "Personas en el circulo: " << list->getSize() << endl;
			cout << "Direccion: " << (direction == LEFT ? "izquierda (sentido del reloj)" : "derecha (sentido contrario al reloj)") << endl;
			cout << "El conteo inicia en: " << list->getFront().name << endl;
			cout << "Circulo (desde donde inicia el conteo): " << endl;
			list->print();

			// 8 saltos a partir de la persona donde se inicia
			int jumps = JUMPS % list->getSize();
			for (int i = 0; i < jumps; i++) {
				if (direction == LEFT) {
					list->next();
				}
				else {
					list->previous();
				}
			}

			// Ahora el frente es la persona donde cayo la ultima silaba
			Person chosen = list->remove();
			cout << "La ultima silaba (\"to\") cae en: " << chosen.name << endl;

			if (!chosen.leftFoot) {
				chosen.leftFoot = true;
				list->insert(chosen); // vuelve a quedar en el frente
				lastEliminated = false;
				cout << ">> " << chosen.name << " cambia a su pie izquierdo." << endl;
			}
			else {
				lastEliminated = true;
				cout << "\n——————————————————————————————————————————————" << endl;
				cout << "      " << chosen.name << " SALE DEL CIRCULO (eliminado/a)    " << endl;
				cout << "——————————————————————————————————————————————" << endl;
			}

			cout << "Resultado despues del conteo:" << endl;
			list->print();
		}

		cout << "\n——————————————————————————————————————————————" << endl;
		cout << "La persona elegida es: " << list->getFront().name << endl;
		cout << "——————————————————————————————————————————————" << endl;

		delete list;
		list = nullptr;
	}
	catch (const runtime_error& e) {
		cout << "Error fatal: " << e.what() << endl;
		if (list != nullptr) {
			delete list;
			list = nullptr;
		}
		return 1;
	}

	return 0;
}