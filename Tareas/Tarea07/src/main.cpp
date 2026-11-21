/*
Instituto Tecnologico de Costa Rica

Nombre : Owel Jafet Gutierrez Ortiz

Carnet : 2026800869

Profesor : Mauricio Aviles Cisneros

Semana 15 : Tarea Corta 7 - Matrices

Fecha de entrega : 10 / 11 / 2026

*/

/*
Programa principal:
    Programa de consola que utiliza un unico objeto Matrix de numeros enteros.
    Solicita al usuario las dimensiones iniciales y luego, en un ciclo, muestra la
    matriz y un menu con todas las operaciones disponibles (getValue, setValue,
    getRows, getColumns, setAll, transpose, addRow, addColumn, removeRow,
    removeColumn y carga de numeros aleatorios). Si una operacion produce un error,
    informa que no se puede realizar y continua. Al salir, libera la memoria.
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include "Matrix.h"

using std::cout;
using std::cin;
using std::endl;
using std::runtime_error;

int pedirEntero(const char* mensaje) {
    int valor;

    cout << mensaje;

    while (!(cin >> valor)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Error, Entrada invalida. Intente de nuevo: ";
    }

    return valor;
}

void llenarAleatorio(Matrix<int>& m) {
    for (int i = 0; i < m.getRows(); i++) {
        for (int j = 0; j < m.getColumns(); j++) {
            m.setValue(i, j, rand() % 100);
        }
    }
}

int main() {
    srand((unsigned)time(nullptr));

    cout << "Menu Matrices" << endl;

    int r = 0;
    int c = 0;

    while (r <= 0 || c <= 0) {
        r = pedirEntero("Ingrese la cantidad de fila : ");
        c = pedirEntero("Ingrese la cantidad de columnas : ");

        if (r <= 0 || c <= 0) {
            cout << "Error: Las dimensiones deben ser mayores a cero."
                << endl;
        }
    }

    Matrix<int>* matrix = new Matrix<int>(r, c);

    //inicializarla con numeros aleatorios
    llenarAleatorio(*matrix);

    //inicializarla con 0
    //matrix->setAll(0);


    int opcion = -1;

    while (opcion != 0) {

        cout << "\n----------------------------------------" << endl;
        cout << "Estado Actual de la Matriz ("
            << matrix->getRows() << "x"
            << matrix->getColumns() << "):" << endl;

        matrix->print();

        cout << "----------------------------------------" << endl;
        cout << "1. getValue (Obtener valor)" << endl;
        cout << "2. setValue (Asignar valor)" << endl;
        cout << "3. getRows (Cantidad de filas)" << endl;
        cout << "4. getColumns (Cantidad de columnas)" << endl;
        cout << "5. setAll (Asignar valor a todas las celdas)" << endl;
        cout << "6. transpose (Transponer matriz)" << endl;
        cout << "7. addRow (Agregar fila al final)" << endl;
        cout << "8. addColumn (Agregar columna al final)" << endl;
        cout << "9. removeRow (Eliminar fila)" << endl;
        cout << "10. removeColumn (Eliminar columna)" << endl;
        cout << "11. Llenar con numeros aleatorios (0-99)" << endl;
        cout << "0. Salir" << endl;

        opcion = pedirEntero("Elija una opcion: ");

        try {

            switch (opcion) {

            case 1: {
                int fila = pedirEntero("Fila: ");
                int col = pedirEntero("Columna: ");

                cout << "Valor en ["
                    << fila << "]["
                    << col << "]: "
                    << matrix->getValue(fila, col)
                    << endl;

                break;
            }

            case 2: {
                int fila = pedirEntero("Fila: ");
                int col = pedirEntero("Columna: ");
                int val = pedirEntero("Nuevo valor: ");

                matrix->setValue(fila, col, val);

                cout << "Valor actualizado." << endl;
                break;
            }

            case 3:
                cout << "Cantidad de filas: "
                    << matrix->getRows()
                    << endl;
                break;

            case 4:
                cout << "Cantidad de columnas: "
                    << matrix->getColumns()
                    << endl;
                break;

            case 5: {
                int val = pedirEntero(
                    "Valor para todas las celdas: "
                );

                matrix->setAll(val);

                cout << "Matriz actualizada." << endl;
                break;
            }

            case 6:
                matrix->transpose();

                cout << "Matriz traspuesta exitosamente."
                    << endl;
                break;

            case 7: {
                int val = pedirEntero(
                    "Valor inicial para la nueva fila: "
                );

                matrix->addRow(val);

                cout << "Fila agregada." << endl;
                break;
            }

            case 8: {
                int val = pedirEntero(
                    "Valor inicial para la nueva columna: "
                );

                matrix->addColumn(val);

                cout << "Columna agregada." << endl;
                break;
            }

            case 9: {
                int fila = pedirEntero(
                    "Indice de fila a eliminar: "
                );

                matrix->removeRow(fila);

                cout << "Fila eliminada." << endl;
                break;
            }

            case 10: {
                int col = pedirEntero(
                    "Indice de columna a eliminar: "
                );

                matrix->removeColumn(col);

                cout << "Columna eliminada." << endl;
                break;
            }

            case 11:
                llenarAleatorio(*matrix);

                cout << "Matriz recargada con valores aleatorios."
                    << endl;
                break;

            case 0:
                cout << "Saliendo del programa..."
                    << endl;
                break;

            default:
                cout << "Opcion no valida."
                    << endl;
                break;
            }

        }
        catch (const runtime_error& e) {

            cout << "\nHa ocurrido un error..."
                << e.what()
                << endl;
        }
    }

    delete matrix;

    return 0;
}