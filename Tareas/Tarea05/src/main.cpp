/*
Instituto Tecnologico de Costa Rica

Nombre : Owel Jafet Gutierrez Ortiz

Carnet : 2026800869

Profesor : Mauricio Aviles Cisneros

Semana 12 : Tarea Corta 5 - Radix Sort

Fecha de entrega : 22 / 10 / 2026

*/

/*
Programa Principal:
    Pide al usuario el tamano de la lista y la base numerica, llena una
    LinkedList con enteros aleatorios y la ordena con Radix Sort usando la
    base indicada. Muestra la lista ordenada y el tiempo de ejecucion, y
    permite repetir el proceso.
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "LinkedList.h"

using std::cout;
using std::cin;
using std::endl;

// Genera un numero aleatorio entre 0 y 999999.
// Se combinan dos rand() porque en algunos compiladores rand() solo llega a 32767.
int numeroAleatorio() {
    long long r = (long long)rand() * 32768 + rand();
    return (int)(r % 1000000);
}

// Pide un entero al usuario y repite hasta que sea valido (>= minimo)
int leerEntero(const char* mensaje, int minimo) {
    int valor;
    cout << mensaje;
    cin >> valor;
    while (cin.fail() || valor < minimo) {
        cout << "Error: debe ser un entero mayor o igual a " << minimo << endl;
        cin.clear();
        cin.ignore(1000, '\n');
        cout << mensaje;
        cin >> valor;
    }
    return valor;
}

// Busca el valor maximo de la lista (para saber cuantas pasadas hacer).
// Saca cada elemento del inicio y lo vuelve a agregar al final,
// asi la lista queda igual que antes.
int getMax(LinkedList<int>& lista) {
    int n = lista.getSize();
    int maxVal = 0;

    for (int i = 0; i < n; i++) {
        lista.goToStart();
        int val = lista.remove();
        if (val > maxVal) {
            maxVal = val;
        }
        lista.append(val);
    }
    return maxVal;
}

// Radix Sort con base como parametro (solo numeros >= 0)
void radixSort(LinkedList<int>& lista, int base) {
    if (lista.getSize() <= 0 || base < 2) return;

    // Un balde (LinkedList) por cada digito posible de la base
    LinkedList<int>* buckets = new LinkedList<int>[base];

    int maxVal = getMax(lista);
    long long peso = 1;   // 1, base, base^2, ...

    // Una pasada por cada digito del numero mas grande
    while (maxVal / peso > 0) {

        // Distribucion: de la lista a los baldes
        while (lista.getSize() > 0) {
            lista.goToStart();
            int val = lista.remove();
            int digito = (val / peso) % base;
            buckets[digito].append(val);
        }

        // Recoleccion: de los baldes (en orden) a la lista original
        for (int b = 0; b < base; b++) {
            while (buckets[b].getSize() > 0) {
                buckets[b].goToStart();
                int val = buckets[b].remove();
                lista.append(val);
            }
        }

        peso = peso * base;
    }

    delete[] buckets;
}

int main() {
    srand(time(NULL));

    char repetir = 's';

    while (repetir == 's' || repetir == 'S') {
        //pedimos tamaño de lista y base
        int n = leerEntero("Ingrese el tamaño de la lista: ", 1);
        int base = leerEntero("Ingrese la base numerica (minimo 2): ", 2);

        //creamos lista y la llenamos
        LinkedList<int> lista;
        for (int i = 0; i < n; i++) {
            lista.append(numeroAleatorio());
        }

        //ordenamos
        clock_t inicio = clock();
        radixSort(lista, base);
        clock_t fin = clock();
        double ms = (double)(fin - inicio) * 1000.0 / CLOCKS_PER_SEC;

        cout << "\nLista ordenada:" << endl;
        lista.print();
        cout << "\nTiempo: " << ms << " ms" << endl;

        cout << "\nDesea repetir? (s/n): ";
        cin >> repetir;
        cout << endl;
    }

    return 0;
}