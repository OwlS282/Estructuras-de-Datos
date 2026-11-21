/*
Instituto Tecnologico de Costa Rica

Nombre : Owel Jafet Gutierrez Ortiz

Carnet : 2026800869

Profesor : Mauricio Aviles Cisneros

Semana 16 : Tarea Corta 8 - Árboles de búsqueda binaria y diccionarios

Fecha de entrega : 19 / 11 / 2026

*/

/*
Programa principal:
	Menú interactivo en consola para probar dos diccionarios implementados
	con BSTDictionary (llaves enteras y valores de texto). Permite elegir
	sobre cuál diccionario trabajar y ejecutar las operaciones insert,
	remove, getValue, setValue, contains, clear, getKeys, getValues,
	update y zip. Valida que los números ingresados sean válidos y
	captura los errores lanzados por el árbol, como llaves duplicadas
	o inexistentes.
*/

#include <iostream>
#include <string>
#include <stdexcept>
#include "BSTDictionary.h"
#include "LinkedList.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::runtime_error;

// Lee un entero; si el usuario escribe algo que no es un numero, vuelve a pedirlo
int readInt() {
	int n;
	cin >> n;
	while (cin.fail()) {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Error, invalid input, try again: ";
		cin >> n;
	}
	cin.ignore(1000, '\n');
	return n;
}

void showDictionaries(BSTDictionary<int, string>* d1, BSTDictionary<int, string>* d2) {
	cout << "\nDictionary 1: ";
	d1->print();
	cout << "Dictionary 2: ";
	d2->print();
	cout << endl;
}

void showMenu() {
	cout << "1. insert\n2. remove\n3. getValue\n4. setValue\n5. contains\n"
		<< "6. clear\n7. getKeys\n8. getValues\n9. update\n10. zip\n0. Exit\n";
}

void execute(int op, BSTDictionary<int, string>* d, BSTDictionary<int, string>* other) {
	int k;
	string v;
	switch (op) {
	case 1:
		cout << "Key: ";
		k = readInt();
		cout << "Value: ";
		cin >> v;
		d->insert(k, v);
		cout << "Pair inserted.\n";
		break;
	case 2:
		cout << "Key: ";
		k = readInt();
		cout << "Removed, value: " << d->remove(k) << endl;
		break;
	case 3:
		cout << "Key: ";
		k = readInt();
		cout << "Value: " << d->getValue(k) << endl;
		break;
	case 4:
		cout << "Key: ";
		k = readInt();
		cout << "New value: ";
		cin >> v;
		d->setValue(k, v);
		cout << "Value updated.\n";
		break;
	case 5:
		cout << "Key: ";
		k = readInt();
		if (d->contains(k))
			cout << "The key exists.\n";
		else
			cout << "The key does NOT exist.\n";
		break;
	case 6:
		d->clear();
		cout << "Dictionary cleared.\n";
		break;
	case 7: {
		List<int>* keys = d->getKeys();
		cout << "Keys: ";
		keys->print();
		delete keys;
		break;
	}
	case 8: {
		List<string>* values = d->getValues();
		cout << "Values: ";
		values->print();
		delete values;
		break;
	}
	case 9:
		d->update(other);
		cout << "Dictionary updated with the contents of the other one.\n";
		break;
	case 10: {
		cout << "Number of elements: ";
		int n = readInt();
		List<int>* keys = new LinkedList<int>();
		List<string>* values = new LinkedList<string>();
		for (int i = 0; i < n; i++) {
			cout << "Key: ";
			k = readInt();
			keys->append(k);
		}
		for (int i = 0; i < n; i++) {
			cout << "Value: ";
			cin >> v;
			values->append(v);
		}
		d->zip(keys, values);
		delete keys;
		delete values;
		cout << "Zip done.\n";
		break;
	}
	default:
		cout << "Error, invalid option.\n";
	}
}

int main() {
	BSTDictionary<int, string>* dictionary1 = new BSTDictionary<int, string>();
	BSTDictionary<int, string>* dictionary2 = new BSTDictionary<int, string>();

	int op = -1;
	while (op != 0) {
		showDictionaries(dictionary1, dictionary2);
		showMenu();
		cout << "Operation: ";
		op = readInt();

		if (op != 0) {
			cout << "Dictionary (1 or 2): ";
			int which = readInt();

			if (which != 1 && which != 2) {
				cout << "Error, invalid dictionary.\n";
			}
			else {
				BSTDictionary<int, string>* d = dictionary1;
				BSTDictionary<int, string>* other = dictionary2;
				if (which == 2) {
					d = dictionary2;
					other = dictionary1;
				}

				try {
					execute(op, d, other);
				}
				catch (runtime_error& e) {
					cout << "Error, the operation cannot be performed: " << e.what() << endl;
				}
			}
		}
	}

	delete dictionary1;
	delete dictionary2;
	return 0;
}