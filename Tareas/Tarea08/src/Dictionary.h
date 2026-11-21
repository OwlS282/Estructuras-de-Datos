/*
Instituto Tecnologico de Costa Rica

Nombre : Owel Jafet Gutierrez Ortiz

Carnet : 2026800869

Profesor : Mauricio Aviles Cisneros

Semana 16 : Tarea Corta 8 - Árboles de búsqueda binaria y diccionarios

Fecha de entrega : 19 / 11 / 2026

*/

/*
Clase Dictionary:
	Interfaz (clase abstracta) que define las operaciones de un
	diccionario de pares llave-valor: insertar, eliminar, consultar y
	modificar valores, verificar si contiene una llave, obtener llaves
	y valores, y las operaciones update y zip. Las clases que la
	implementan, como BSTDictionary, definen cada una de esas operaciones.
*/

#pragma once

#include "List.h"

template <typename K, typename V>
class Dictionary {
public:
	Dictionary(const Dictionary <K, V>&) = delete;
	void operator=(const Dictionary <K, V>&) = delete;
	Dictionary() {}
	virtual ~Dictionary() {}
	virtual void insert(K key, V value) = 0;
	virtual V remove(K key) = 0;
	virtual V getValue(K key) = 0;
	virtual void setValue(K key, V value) = 0;
	virtual bool contains(K key) = 0;
	virtual void clear() = 0;
	virtual bool isEmpty() = 0;
	virtual List<K>* getKeys() = 0;
	virtual List<V>* getValues() = 0;
	virtual int getSize() = 0;
	virtual void print() = 0;
	virtual void update(Dictionary<K, V>* D) = 0;
	virtual void zip(List<K>* keys, List<V>* values) = 0;
};
