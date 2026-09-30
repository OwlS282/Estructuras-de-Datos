/*
Instituto Tecnológico de Costa Rica

Nombre : Owel Jafet Gutiérrez Ortiz

Carnet : 2026800869

Profesor : Mauricio Avilés Cisneros

Semana 4 : Tarea Corta 1 – Pilas

Fecha de entrega : 02 / 09 / 2026

*/

/*
Clase:
	PilasColas: Archivo que use de base para elaborar la tarea 1. Se encuentra en main y
	donde evaluamos todas las expresiones ingresadas.
*/

#include <stdexcept>
#include <iostream>
#include <string>
#include <cmath> //para usar pow(a,b)
#include <cctype> //para verificar si es digito o espacio

#include "ArrayStack.h"
#include "LinkedStack.h"
#include "ArrayQueue.h"
#include "Util.h"

using std::runtime_error;
using std::string;
using std::exception;
using std::cout;
using std::cin;
using std::endl;
using std::getline;

//remover espacios
string removeWhiteSpace(const string& expr) {
    string result = "";
    for (char c : expr) {
        if (!isspace(c)) {
            result += c;
        }
    }
    return result;
}

//obtenemos el siguiente token
string getNextToken(string& expr) {
    if (expr.empty()) {
        return "";
    }

    string token = "";

    //si es un digito se lleva el numero completo
    if (isdigit(expr[0])) {
        while (!expr.empty() && isdigit(expr[0])) {
            token += expr[0];
            expr = expr.substr(1);
        }
    }
    //diferenciar si es un operador o un parentesis
    else if (expr[0] == '+' || expr[0] == '-' || expr[0] == '*' ||
        expr[0] == '/' || expr[0] == '^' || expr[0] == '(' ||expr[0] == ')') {
        token = expr[0];
        expr = expr.substr(1);
    }
	else {
		throw runtime_error("Error, Ingresó una expresión no válida!");
	}
    return token;
}

// diferenciar si es un numero
bool isNumber(const string& token) {
    if (token.empty())
        return false;
    for (char c : token) {
        if (!isdigit(c))
            return false;
    }
    return true;
}

// diferenciar si es operador
bool isOperator(const string& token) {
    return (token == "+" || token == "-" || token == "*" || token == "/" || token == "^");
}

//retorna la procedencia de un operador
int getPrecedence(char op) {
    switch (op) {
        case '^':
            return 3; //mayor precedencia
        case '*':
        case '/':
            return 2; // media procedencia
        case '+':
        case '-':
            return 1; //menor precedencia
        default:
            return 0;
    }
}
//proceamos la operacion
//hacemos pop de dos numeros, calculamos y push del resultado
void processOperation(Stack<double>& numStack, Stack<char>& opStack) {
    double b = numStack.pop();
    double a = numStack.pop();
    char op = opStack.pop();

    double result;
	//calculamos segun sea el operador
    switch (op) {
        case '+':
            result = a + b;
            break;
        case '-':
            result = a - b;
            break;
        case '*':
            result = a * b;
            break;
        case '/':
            if (b == 0) {
                throw runtime_error("Error, division entre 0.");
            }
            result = a / b;
            break;
        case '^':
            result = pow(a,b);
            break;
        default:
            throw runtime_error("Error, operador desconocido.");
    }
	//mostramos la operacion
	cout << "Procesando operación " << a << op << b << "=" << result << endl;
	cout << endl;
	//guardamos el resultado
    numStack.push(result);
}

int main() {
	int choice;
	string expr;

	while (true) {
		//mostramos el menu
		cout << "Seleccione el tipo de pila:" << endl;
		cout << "1. ArrayStack" << endl;
		cout << "2. LinkedStack" << endl;
		cout << "3. Salir" << endl;
		cout << "Opción: ";

		// nos sirve para que no entre en bucle en caso de error
		if (!(cin >> choice)) {
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "Error, Ingrese un número válido" << endl;
			cin.get();
			system("cls");
			continue;
		}
		cin.ignore();

		//terminamos el programa
		if (choice == 3) {
			cout << "¡Saliendooo!" << endl;
			break;
		}

		try {
			//solicitamos la expresion
			cout << "Escriba la expresión a analizar: ";
			getline(cin, expr); //agarramos la linea completa
			
			//eliminamos los espacios en blanco
			expr = removeWhiteSpace(expr);

			// verificamos que no este vacia
			if (expr.empty()) {
				cout << "Error, Expresión vacía" << endl;
				continue;
			}

			//creamos la pila segun la elegida
			Stack<double>* numStack;
			Stack<char>* opStack;

			if (choice == 1) {
				// ArrayStack 
				numStack = new ArrayStack<double>(5);
				opStack = new ArrayStack<char>(5);
			}
			else if (choice == 2) {
				// LinkedStack
				numStack = new LinkedStack<double>();
				opStack = new LinkedStack<char>();
			}
			else {
				cout << "Opción no válida" << endl;
				continue;
			}

			try {
				cout << "Pila números:		[ ]" << endl;
				cout << "Pila operadores:	[ ]" << endl;
				cout << "Expresión:		" << expr << endl;
				cout << endl;

				//recorremos cada token
				while (!expr.empty()) {

					//obtenemos el siguiente token
					string token = getNextToken(expr);

					if (token.empty())
						continue;

					cout << "Token actual: " << token << endl;

					//si es numero, lo metemos a la pila de numeros
					if (isNumber(token)) {
						cout << "Es número. Push en pila de números." << endl;
						double num = stod(token);
						numStack->push(num);
						cout << "Pila números:		";
						numStack->print();
						cout << "Pila operadores:	";
						opStack->print();
						cout << "Expresión:		" << expr << endl;
						cout << endl;
					}

					//si es operador, procesamos las operaciones pendientes
					else if (isOperator(token)) {
						cout << "Es operador." << endl;
						char op = token[0];

						//procesamos operacion de mayor o igual precedencia
						while (!opStack->isEmpty() &&
							opStack->topValue() != '(' &&
							getPrecedence(opStack->topValue()) >= getPrecedence(op)) {
							cout << "Operador en tope tiene precedencia mayor o igual. Procesando operación." << endl;
							processOperation(*numStack, *opStack);
						}

						// metemos al nuevo operador
						cout << "Push en la pila de operadores." << endl;
						opStack->push(op);
						cout << "Pila números:		";
						numStack->print();
						cout << "Pila operadores:	";
						opStack->print();
						cout << "Expresión:		" << expr << endl;
						cout << endl;
					}
					//si es parentesis abierto, lo metemos en la pila de operadores
					else if (token == "(") {
						cout << "Es (. Push en la pila de operadores." << endl;
						opStack->push('(');
						cout << "Pila números:		";
						numStack->print();
						cout << "Pila operadores:	";
						opStack->print();
						cout << "Expresión:		" << expr << endl;
						cout << endl;
					}

					//si es parentesis cerrado, procesamos hasta el parentesis abierto
					else if (token == ")") {
						cout << "Es )." << endl;

						//procesamos la operaciones hasta encontrar donde se abrio el parentesis
						while (!opStack->isEmpty() && opStack->topValue() != '(') {
							cout << "Tope de la pila no es (. Procesando operación." << endl;
							processOperation(*numStack, *opStack);
						}

						//validamos que exista parentesis izquierdo
						if (opStack->isEmpty()) {
							throw runtime_error("Error, Paréntesis desemparejados");
						}

						//eliminamos el parentesis izquierdo
						cout << "Pop en la pila de operadores: (" << endl;
						opStack->pop();
						cout << "Pila números:		";
						numStack->print();
						cout << "Pila operadores:	";
						opStack->print();
						cout << "Expresión:		" << expr << endl;
						cout << endl;
					}
				}

				// Fin de expresion, procesamos los operadores restantes
				cout << "Fin de la expresión, procesando lo que queda en las pilas." << endl;
				cout << "Pila números:		";
				numStack->print();
				cout << "Pila operadores:	";
				opStack->print();
				cout << "Expresión:		" << endl;
				cout << endl;

				//procesamos los operadores que faltan
				while (!opStack->isEmpty()) {
					// Validar que no queden parentesis sueltos
					if (opStack->topValue() == '(' || opStack->topValue() == ')') {
						throw runtime_error("Error, Paréntesis desemparejados");
					}

					processOperation(*numStack, *opStack);
					cout << "Pila números:		";
					numStack->print();
					cout << "Pila operadores:	";
					opStack->print();
					cout << "Expresión:" << endl;
				}

				//validamos que quede un solo numero, el resultado
				if (numStack->getSize() != 1) {
					throw runtime_error("Error, Expresión mal formada");
				}

				// obtenemos el resultado y lo mostramos
				double resultado = numStack->pop();

				cout << endl;
				cout << "El resultado de la evaluación es: " << resultado << endl;
				cout << endl;

			}
			catch (const exception& e) {
				cout << "Error, Hay un error en la expresión." << endl;
				cout << "Detalles: " << e.what() << endl;
				cout << endl;
			}

			// liberamos memoria
			delete numStack;
			delete opStack;
		}
		//manejo de errores y los mostramos
		catch (const exception& e) {
			cout << "Error " << e.what() << endl;
		}
	}
	return 0;
}