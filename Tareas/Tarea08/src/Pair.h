/*
Instituto Tecnologico de Costa Rica

Nombre : Owel Jafet Gutierrez Ortiz

Carnet : 2026800869

Profesor : Mauricio Aviles Cisneros

Semana 16 : Tarea Corta 8 - Árboles de búsqueda binaria y diccionarios

Fecha de entrega : 19 / 11 / 2026

*/

/*
Clase Pair:
	Clase auxiliar que representa un par llave-valor. Sus atributos son
	públicos y los operadores de comparación (==, <, >, etc.) comparan
	únicamente la llave, lo que permite ordenar los pares dentro de un
	árbol de búsqueda binaria. También sobrecarga el operador << para
	imprimir el par con el formato (llave, valor).
*/

#pragma once

#include <string>
#include <iostream>

using std::string;
using std::ostream;

//datos publicos, es una clase auxiliar
template <typename K, typename V>
class Pair {
public:
	K key;
	V value;

	Pair(K key, V value) {
		this->key = key;
		this->value = value;
	}

	Pair(K key) {
		this->key = key;
	}

	Pair() {}

	bool operator==(const Pair<K, V>& other) {
		return key == other.key;
	}

	bool operator<(const Pair<K, V>& other) {
		return key < other.key;
	}

	bool operator<=(const Pair<K, V>& other) {
		return key <= other.key;
	}

	bool operator>(const Pair<K, V>& other) {
		return key > other.key;
	}

	bool operator>=(const Pair<K, V>& other) {
		return key >= other.key;
	}

	bool operator!=(const Pair<K, V>& other) {
		return key != other.key;
	}

	friend ostream& operator<<(ostream& os, const Pair<K, V>& pair) {
		os << "(" << pair.key << ", " << pair.value << ")";
		return os;
	}
};

