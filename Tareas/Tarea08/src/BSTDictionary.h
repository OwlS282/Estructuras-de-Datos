/*
Instituto Tecnologico de Costa Rica

Nombre : Owel Jafet Gutierrez Ortiz

Carnet : 2026800869

Profesor : Mauricio Aviles Cisneros

Semana 16 : Tarea Corta 8 - Árboles de búsqueda binaria y diccionarios

Fecha de entrega : 19 / 11 / 2026

*/

/*
Clase BSTDictionary:
	Implementación de Dictionary que almacena los pares llave-valor
	(Pair) en un árbol de búsqueda binaria ordenado por llave. Las
	llaves no se pueden repetir. Además de las operaciones básicas,
	implementa update (copia los pares de otro diccionario) y zip
	(empata una lista de llaves con una lista de valores).
*/

#pragma once

#include "Dictionary.h"
#include "BSTree.h"
#include "List.h"
#include "LinkedList.h"
#include "Pair.h"

template <typename K, typename V>
class BSTDictionary : public Dictionary<K, V> {
private:
	// Arbol binario de busqueda que guarda pares llave-valor, ordenados por llave
	BSTree<Pair<K, V>>* pairs;

public:
	BSTDictionary() {
		pairs = new BSTree<Pair<K, V>>();
	}

	~BSTDictionary() {
		delete pairs;
	}

	// Si la llave ya existe, el arbol lanza un error
	void insert(K key, V value) {
		pairs->insert(Pair<K, V>(key, value));
	}

	// Si la llave no existe, el arbol lanza un error
	V remove(K key) {
		return pairs->remove(Pair<K, V>(key)).value;
	}

	// Si la llave no existe, el arbol lanza un error
	V getValue(K key) {
		return pairs->find(Pair<K, V>(key)).value;
	}

	// Elimina el par existente y lo inserta con el nuevo valor.
	// Si la llave no existe, remove lanza un error.
	void setValue(K key, V value) {
		pairs->remove(Pair<K, V>(key));
		pairs->insert(Pair<K, V>(key, value));
	}

	bool contains(K key) {
		return pairs->contains(Pair<K, V>(key));
	}

	void clear() {
		pairs->clear();
	}

	bool isEmpty() {
		return pairs->isEmpty();
	}

	// Retorna una lista dinamica con las llaves en orden; quien la pide debe hacerle delete
	List<K>* getKeys() {
		List<Pair<K, V>>* elements = pairs->getElements();
		List<K>* keys = new LinkedList<K>();
		elements->goToStart();
		while (!elements->atEnd()) {
			keys->append(elements->getElement().key);
			elements->next();
		}
		delete elements;
		return keys;
	}

	// Retorna una lista dinamica con los valores, segun el orden de las llaves
	List<V>* getValues() {
		List<Pair<K, V>>* elements = pairs->getElements();
		List<V>* values = new LinkedList<V>();
		elements->goToStart();
		while (!elements->atEnd()) {
			values->append(elements->getElement().value);
			elements->next();
		}
		delete elements;
		return values;
	}

	int getSize() {
		return pairs->getSize();
	}

	void print() {
		pairs->print();
	}

	// Agrega todos los pares de D; si la llave existe actualiza el valor, si no la inserta.
	// D no se elimina.
	void update(Dictionary<K, V>* D) {
		List<K>* keys = D->getKeys();
		keys->goToStart();
		while (!keys->atEnd()) {
			K key = keys->getElement();
			V value = D->getValue(key);
			if (contains(key))
				setValue(key, value);
			else
				insert(key, value);
			keys->next();
		}
		delete keys;
	}

	// Empata llaves y valores posicion por posicion; ignora los sobrantes de la lista mas larga.
	// Las listas no se eliminan (se restaura su posicion actual al terminar).
	void zip(List<K>* keys, List<V>* values) {
		int posKeys = keys->getPos();
		int posValues = values->getPos();
		keys->goToStart();
		values->goToStart();
		while (!keys->atEnd() && !values->atEnd()) {
			K key = keys->getElement();
			V value = values->getElement();
			if (contains(key))
				setValue(key, value);
			else
				insert(key, value);
			keys->next();
			values->next();
		}
		keys->goToPos(posKeys);
		values->goToPos(posValues);
	}
};