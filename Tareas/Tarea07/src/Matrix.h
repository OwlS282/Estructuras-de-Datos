/*
Instituto Tecnologico de Costa Rica

Nombre : Owel Jafet Gutierrez Ortiz

Carnet : 2026800869

Profesor : Mauricio Aviles Cisneros

Semana 15 : Tarea Corta 7 - Matrices

Fecha de entrega : 10 / 11 / 2026

*/

/*
Clase Matrix:
	Clase plantilla que representa una matriz bidimensional de elementos de tipo E,
    implementada con memoria dinamica (arreglo de arreglos). Permite consultar y
    modificar valores, asignar un valor a todas las celdas, transponer la matriz,
    agregar y eliminar filas y columnas, e imprimir su contenido en pantalla.
    Lanza una excepcion (runtime_error) cuando se violan las restricciones de
    sus metodos, como dimensiones o indices invalidos.
*/

#pragma once

#include <iostream>
#include <stdexcept>

using std::runtime_error;
using std::cout;
using std::endl;

template <typename E>
class Matrix {
private:
	int rows;
	int columns;
	E** matrix;

public:
	Matrix(int rows, int columns) {
		if (rows <= 0 || columns <= 0) {
			throw runtime_error("Error, Number of rows and columns must be greater than zero");
		}
		this->rows = rows;
		this->columns = columns;
		matrix = new E * [rows];
		for (int i = 0; i < rows; i++) {
			matrix[i] = new E[columns];
		}
	}
	~Matrix() {
		for (int i = 0; i < rows; i++) {
			delete[] matrix[i];
		}
		delete[] matrix;
	}

	E getValue(int row, int column) {
		if (row < 0 || row >= rows) {
			throw runtime_error("Error, invalid row.");
		}
		if (column < 0 || column >= columns) {
			throw runtime_error("Error, invalid column.");
		}
		return matrix[row][column];
	}

	void setValue(int row, int column, E value) {
		if (row < 0 || row >= rows) {
			throw runtime_error("Error, invalid row.");
		}
		if (column < 0 || column >= columns) {
			throw runtime_error("Error, invalid column.");
		}
		matrix[row][column] = value;
	}

	int getRows() {
		return rows;
	}

	int getColumns() {
		return columns;
	}

	void setAll(E value) {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				matrix[i][j] = value;
			}
		}
	}

	void transpose() {
		// Crear la estructura nueva con las dimensiones invertidas
		E** newMatrix = new E * [columns];
		for (int i = 0; i < columns; i++) {
			newMatrix[i] = new E[rows];
		}
		// Traspasar los elementos
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				newMatrix[j][i] = matrix[i][j];
			}
		}
		// Eliminar la estructura anterior
		for (int i = 0; i < rows; i++) {
			delete[] matrix[i];
		}
		delete[] matrix;
		// Actualizar atributos
		matrix = newMatrix;
		int temp = rows;
		rows = columns;
		columns = temp;
	}

	void addRow(E value) {
		E** newMatrix = new E * [rows + 1];
		for (int i = 0; i < rows + 1; i++) {
			newMatrix[i] = new E[columns];
		}
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				newMatrix[i][j] = matrix[i][j];
			}
		}
		for (int j = 0; j < columns; j++) {
			newMatrix[rows][j] = value;
		}
		for (int i = 0; i < rows; i++) {
			delete[] matrix[i];
		}
		delete[] matrix;
		matrix = newMatrix;
		rows++;
	}

	void addColumn(E value) {
		transpose();
		addRow(value);
		transpose();
	}

	void removeRow(int row) {
		if (row < 0 || row >= rows) {
			throw runtime_error("Error, invalid row.");
		}
		if (rows == 1) {
			throw runtime_error("Error, cannot remove the only row of the matrix.");
		}
		E** newMatrix = new E * [rows - 1];
		for (int i = 0; i < rows - 1; i++) {
			newMatrix[i] = new E[columns];
		}
		int newI = 0;
		for (int i = 0; i < rows; i++) {
			if (i == row) continue;
			for (int j = 0; j < columns; j++) {
				newMatrix[newI][j] = matrix[i][j];
			}
			newI++;
		}
		for (int i = 0; i < rows; i++) {
			delete[] matrix[i];
		}
		delete[] matrix;
		matrix = newMatrix;
		rows--;
	}

	void removeColumn(int column) {
		if (column < 0 || column >= columns) {
			throw runtime_error("Error, invalid column.");
		}
		if (columns == 1) {
			throw runtime_error("Error, cannot remove the only column of the matrix.");
		}
		transpose();
		removeRow(column);
		transpose();
	}

	void print() {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				cout << matrix[i][j] << "\t";
			}
			cout << endl;
		}
	}
};