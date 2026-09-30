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
	ToolBox: Caja de herramientas que almacena herramientas.
	Controla peso y volumen máximos, utiliza listas para almacenar herramientas.
	Permite agregar, remover y limpiar herramientas respetando límites.
*/

#pragma once

#include <stdexcept>
#include <iostream>
#include <iomanip>
#include "List.h"
#include "ArrayList.h"
#include "LinkedList.h"
#include "DLinkedList.h"
#include "Tool.h"
#include "Util.h"

using std::runtime_error;
using std::cout;
using std::endl;
using std::fixed;
using std::setprecision;

class ToolBox {
private:
	double maxWeight;  // Peso máximo permitido
	double maxVolume;  // Volumen máximo permitido
	double currentWeight;  // Peso actual
	double currentVolume;  // Volumen actual
	List<Tool>* tools;  // puntero a la lista de herramientas

public:
	// Constructor que recibe tipo de lista y tamaños opcionales
	ToolBox(int listType, double maxWeight, double maxVolume) {
		tools = nullptr;
		this->maxWeight = maxWeight;
		this->maxVolume = maxVolume;
		currentWeight = 0.0;
		currentVolume = 0.0;

		// Crear la lista según tipo especificad
		if (listType == 1) {
			tools = new ArrayList<Tool>(DEFAULT_MAX);
		}
		else if (listType == 2) {
			tools = new LinkedList<Tool>();
		}
		else if (listType == 3) {
			tools = new DLinkedList<Tool>();
		}
	}

	~ToolBox() {
		if (tools != nullptr) {
			delete tools;
			tools = nullptr;
		}
	}

	// Agrega herramienta si no excede límites de peso y volumen
	void add(Tool tool) {
		// Verificar si excede el peso máximo
		if (currentWeight + tool.weight > maxWeight) {
			throw runtime_error("Error: The toolbox weight limit has been exceeded.");
		}

		// Verificar si excede el volumen máximo
		if (currentVolume + tool.volume > maxVolume) {
			throw runtime_error("Error: The toolbox volume limit has been exceeded.");
		}

		// Agregar la herramienta al final de la lista
		tools->append(tool);
		currentWeight += tool.weight;
		currentVolume += tool.volume;
	}

	// Remueve herramienta en posición especificada
	Tool remove(int pos) {
		if (tools->getSize() == 0) {
			// caja vacia
			throw runtime_error("Error: The toolbox is empty.");
		}

		if (pos < 0 || pos >= tools->getSize()) {
			throw runtime_error("Error: Invalid position.");
		}

		// Ir a la posición indicada
		tools->goToPos(pos);
		Tool removedTool = tools->getElement();
		tools->remove();

		// Actualizar pesos y volúmenes
		currentWeight -= removedTool.weight;
		currentVolume -= removedTool.volume;

		return removedTool;
	}

	// Vacía la caja de herramientas
	void clear() {
		tools->clear();
		currentWeight = 0.0;
		currentVolume = 0.0;
	}

	// Métodos getter 
	double getMaxWeight() const {
		return maxWeight;
	}

	double getMaxVolume() const {
		return maxVolume;
	}

	double getCurrentWeight() const {
		return currentWeight;
	}

	double getCurrentVolume() const {
		return currentVolume;
	}

	int toolCount() const {
		return tools->getSize();
	}

	// Obtiene herramienta en posición específica
	Tool getTool(int pos) {
		if (pos < 0 || pos >= tools->getSize()) {
			throw runtime_error("Error: Invalid position.");
		}
		tools->goToPos(pos);
		return tools->getElement();
	}

	// Imprime contenido y datos de la caja
	void print() {
		cout << "\nToolbox contents:" << endl;
		if (tools->getSize() == 0) {
			cout << "\t(empty)" << endl;
		}
		else {
			for (int i = 0; i < tools->getSize(); i++) {
				cout << "\t" << (i + 1) << ". " << getTool(i) << endl;
			}
		}
		cout << "Weight: " << fixed << setprecision(2)
			<< currentWeight << "/" << maxWeight << endl;
		cout << "Volume: " << fixed << setprecision(2)
			<< currentVolume << "/" << maxVolume << endl << endl;
	}
};