/*
Instituto Tecnológico de Costa Rica

Nombre : Owel Jafet Gutiérrez Ortiz

Carnet : 2026800869

Profesor : Mauricio Avilés Cisneros

Semana 8 : Tarea Corta 3 – Lista: Caja de Herramientas

Fecha de entrega : 24 / 09 / 2026

*/

/*
Programa Principal:
	Simula una caja de herramientas interactiva.
	Permite al usuario seleccionar tipo de lista, tamaño de caja y realizar operaciones.
*/

#include <iostream>
#include <stdexcept>
#include "ToolBox.h"
#include "Tool.h"

using std::cout;
using std::cin;
using std::endl;
using std::runtime_error;

// Lista de herramientas disponibles
Tool availableTools[12] = {
	Tool("Phillips screwdriver", 0.25, 1.5),
	Tool("Flat screwdriver", 0.25, 1.5),
	Tool("Hammer", 1.0, 3.5),
	Tool("French wrench", 0.75, 3.0),
	Tool("Hacksaw", 0.5, 3.0),
	Tool("Scissors", 0.25, 2.2),
	Tool("Cutter", 0.25, 1.5),
	Tool("Pliers", 0.5, 1.8),
	Tool("Pincers", 0.25, 2.0),
	Tool("Drill", 2.0, 4.0),
	Tool("Locking pliers", 0.5, 2.5),
	Tool("Measuring tape", 0.5, 1.5)
};

// Limpia el buffer de entrada, lo que nos evita errores
void clearInput() {
	cin.clear();
	cin.ignore(1000000, '\n');
}

// Obtiene entrada válida dentro de rango especificado
int getValidInput(int minValue, int maxValue) {
	int value = 0;
	bool validInput = false;

	while (!validInput) { 
		if (!(cin >> value)) { // Verifica que sea número válido
			clearInput();
			cout << "Error: Please enter a valid number." << endl;
			cout << "Option: ";
			continue;
		}

		if (value < minValue || value > maxValue) { // Verifica que esté en rango
			cout << "Error: Option must be between " << minValue << " and " << maxValue << "." << endl;
			cout << "Option: ";
			continue;
		}

		validInput = true;
	}

	clearInput();
	return value;
}

int main() {
	int listType = 0;
	int boxSize = 0;
	ToolBox* toolbox = nullptr;
	int option = 0;
	int toolChoice = 0;
	int removeChoice = 0;

	try {
		// Elegir tipo de lista
		cout << "Choose the type of list to use:" << endl;
		cout << "1. ArrayList" << endl;
		cout << "2. LinkedList" << endl;
		cout << "3. DLinkedList" << endl;
		cout << "Option: ";
		listType = getValidInput(1, 3);

		// Elegir tamaño de caja
		cout << "\nChoose the size of the toolbox:" << endl;
		cout << "1. Small (max weight = 2, max volume = 10)" << endl;
		cout << "2. Medium (max weight = 4, max volume = 14)" << endl;
		cout << "3. Large (max weight = 6, max volume = 20)" << endl;
		cout << "Option: ";
		boxSize = getValidInput(1, 3);

		// Crear caja según tamaño seleccionado
		if (boxSize == 1) {
			toolbox = new ToolBox(listType, 2, 10);
		}
		else if (boxSize == 2) {
			toolbox = new ToolBox(listType, 4, 14);
		}
		else if (boxSize == 3) {
			toolbox = new ToolBox(listType, 6, 20);
		}

		// Verificar que se creó correctamente
		if (toolbox != nullptr) {
			// Ciclo principal del programa
			while (true) {
				// Mostrar estado actual de la caja
				toolbox->print();

				// Mostrar menú de opciones
				cout << "Choose toolbox operation:" << endl;
				cout << "1. Add tool" << endl;
				cout << "2. Remove tool" << endl;
				cout << "3. Clear toolbox" << endl;
				cout << "0. Exit" << endl;
				cout << "Option: ";
				option = getValidInput(0, 3); // Obtener opción válida

				// Opción 1: Agregar herramienta
				if (option == 1) {
					cout << "\nChoose tool to add:" << endl;
					for (int i = 0; i < 12; i++) {
						cout << (i + 1) << ". " << availableTools[i] << endl;
					}
					cout << "Option: ";
					toolChoice = getValidInput(1, 12);

					try {
						toolbox->add(availableTools[toolChoice - 1]);
						cout << "Tool added successfully!" << endl;
					}
					catch (runtime_error e) {
						cout << e.what() << endl;
					}

				}
				// Opción 2: Remover herramienta
				else if (option == 2) {
					if (toolbox->toolCount() == 0) {
						cout << "Toolbox is empty!" << endl;
					}
					else {
						cout << "\nChoose tool to remove:" << endl;
						for (int i = 0; i < toolbox->toolCount(); i++) {
							cout << (i + 1) << ". " << toolbox->getTool(i) << endl;
						}
						cout << "Option: ";
						removeChoice = getValidInput(1, toolbox->toolCount());

						try {
							Tool removed = toolbox->remove(removeChoice - 1);
							cout << "Tool removed: " << removed << endl;
						}
						catch (runtime_error e) {
							cout << e.what() << endl;
						}
					}

				}
				// Opción 3: Limpiar caja completamente
				else if (option == 3) {
					toolbox->clear();
					cout << "Toolbox cleared!" << endl;

				}
				// Opción 0: Salir del programa
				else if (option == 0) {
					cout << "Goodbye!" << endl;
					delete toolbox;
					toolbox = nullptr;
					return 0;
				}
			}
		}

	}
	// Capturar errores fatales del programa principal
	catch (runtime_error e) {
		cout << "Fatal error: " << e.what() << endl;
		if (toolbox != nullptr) {
			delete toolbox;
			toolbox = nullptr;
		}
		return 1;
	}

	// Limpieza final de memoria
	if (toolbox != nullptr) {
		delete toolbox;
		toolbox = nullptr;
	}
	return 0;
}