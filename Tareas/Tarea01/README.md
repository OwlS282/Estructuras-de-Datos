# Tarea Corta 1 - Pilas (Evaluador de expresiones)

## Descripción
Esta tarea consiste en la implementación de pilas genéricas en C++ y su uso para evaluar expresiones aritméticas ingresadas por el usuario. Se implementan dos versiones de la misma pila (una con **arreglo dinámico** y otra con **lista enlazada**) a partir de una clase abstracta, y el programa principal permite escoger cuál usar. La evaluación se hace con dos pilas, una de números y una de operadores, y se muestra paso a paso. El programa permite:
- Escoger entre `ArrayStack` y `LinkedStack` para evaluar la expresión
- Evaluar expresiones con números enteros, los operadores `+`, `-`, `*`, `/`, `^` y paréntesis
- Respetar la precedencia de los operadores y el uso de paréntesis
- Ver en pantalla cada token leído y el contenido de ambas pilas en cada paso
- Detectar errores de la expresión (caracteres inválidos, paréntesis desemparejados, división entre 0, expresión mal formada)
- Mantener en el proyecto la cola circular `ArrayQueue` de la tarea anterior, como referencia

## Requisitos del problema

### Stack (clase abstracta genérica)
- Define la interfaz común de todas las pilas, mediante métodos virtuales puros
- **push(element)**: Agrega un elemento en el tope
- **pop()**: Quita y retorna el elemento del tope
- **topValue()**: Retorna el elemento del tope sin quitarlo
- **clear()**, **isEmpty()**, **getSize()** y **print()**
- Tiene el constructor de copia y el operador de asignación eliminados (`= delete`) y un destructor virtual

### ArrayStack
- Implementación de la pila con un **arreglo dinámico**
- Cuando se llena, **duplica su capacidad** automáticamente (`expandArray()`)
- La capacidad inicial por defecto es 1024 (`DEFAULT_MAX`); lanza un error si se pide una capacidad menor que 1

### LinkedStack
- Implementación de la pila con una **lista enlazada de nodos** (`Node`)
- No tiene límite de tamaño: cada `push` crea un nodo nuevo que pasa a ser el tope
- El destructor libera todos los nodos mediante `clear()`

### Node
- Nodo genérico de una lista enlazada: guarda un `element` y un puntero `next` al siguiente nodo

### Queue y ArrayQueue (de la tarea anterior)
- `Queue` es la clase abstracta genérica de las colas (`enqueue`, `dequeue`, `frontValue`, `clear`, `isEmpty`, `getSize`, `print`)
- `ArrayQueue` la implementa con un **arreglo circular** de tamaño fijo; lanza un error si se intenta agregar a una cola llena
- Se mantienen en el proyecto como referencia y no se usan en el evaluador

### Util
- Almacena la constante de compilación `DEFAULT_MAX` (1024), usada como capacidad por defecto

### PilasColas (programa principal)
- Contiene el menú, el análisis de la expresión (tokens) y el algoritmo de evaluación
- Funciones auxiliares: `removeWhiteSpace()`, `getNextToken()`, `isNumber()`, `isOperator()`, `getPrecedence()` y `processOperation()`

## Algoritmo de evaluación

La expresión se recorre de izquierda a derecha, token por token, usando una pila de números (`Stack<double>`) y una pila de operadores (`Stack<char>`):

| Token | Acción |
|-------|--------|
| Número | Se convierte a `double` y se hace `push` en la pila de números |
| Operador | Mientras el tope de la pila de operadores no sea `(` y tenga **precedencia mayor o igual**, se procesa esa operación. Luego se hace `push` del operador nuevo |
| `(` | Se hace `push` en la pila de operadores |
| `)` | Se procesan operaciones hasta encontrar `(`, y luego se hace `pop` del `(`. Si no hay `(`, hay un error |
| Fin de la expresión | Se procesan todos los operadores que quedan. Debe quedar un solo número en la pila: el resultado |

**Procesar una operación** consiste en hacer `pop` de dos números (`b` y luego `a`), `pop` de un operador, calcular `a op b` y hacer `push` del resultado.

### Precedencia de los operadores

| Operador | Operación | Precedencia |
|----------|-----------|-------------|
| `^` | Potencia | 3 (mayor) |
| `*`, `/` | Multiplicación, división | 2 |
| `+`, `-` | Suma, resta | 1 (menor) |

## Reglas de validación
- La opción del menú debe ser un entero; si no, se avisa y se vuelve a mostrar el menú.
- La expresión no puede estar vacía.
- Los espacios en blanco de la expresión se ignoran.
- Solo se aceptan **números enteros no negativos** (sin decimales ni signo), los operadores `+ - * / ^` y los paréntesis; cualquier otro carácter genera un error.
- Los paréntesis deben estar balanceados.
- No se permite la división entre 0.
- Al terminar, debe quedar exactamente un número en la pila de números; si no, la expresión está mal formada.
- Todos los errores de la expresión se capturan, se muestran y el programa vuelve al menú sin cerrarse.

## Conceptos implementados

- **Plantillas (templates)**: Clases genéricas `Stack<E>`, `ArrayStack<E>`, `LinkedStack<E>`, `Node<E>`, `Queue<E>` y `ArrayQueue<E>`
- **Clases abstractas y métodos virtuales puros**: `Stack` y `Queue` definen la interfaz, y las demás clases la implementan
- **Herencia y polimorfismo**: El programa usa punteros `Stack<double>*` y `Stack<char>*` que apuntan a `ArrayStack` o `LinkedStack` según la opción del usuario; las funciones reciben `Stack<...>&` sin saber qué implementación es
- **Destructor virtual**: Permite liberar correctamente el objeto con `delete` a través de un puntero a la clase base
- **Memoria dinámica**: Arreglo que se redimensiona (`new[]` y `delete[]`) y nodos creados y liberados uno a uno (`new` y `delete`)
- **Estructuras de datos**: Pila con arreglo, pila enlazada y cola circular
- **Manejo de excepciones**: `throw runtime_error`, y `try/catch` en el programa principal
- **Copia deshabilitada**: Constructor de copia y asignación eliminados para evitar copias superficiales de punteros
- **Constantes de compilación**: `#define DEFAULT_MAX` y `#pragma once` en los encabezados
- **Evaluación de expresiones con dos pilas**: Análisis en tokens, precedencia de operadores y paréntesis

## Requisitos técnicos
- Compilador de C++ con soporte para C++11 o superior
- IDE: Visual Studio, Code::Blocks, CLion o Visual Studio Code, o `g++` por terminal
- Se recomienda **Windows** (el programa usa `system("cls")` para limpiar la pantalla)

## Estructura del proyecto

```
PilasColas/
├── PilasColas.cpp     - Programa principal (menú y evaluación de expresiones)
├── Stack.h            - Clase abstracta de las pilas
├── ArrayStack.h       - Pila con arreglo dinámico
├── LinkedStack.h      - Pila con lista enlazada
├── Node.h             - Nodo de la lista enlazada
├── Queue.h            - Clase abstracta de las colas
├── ArrayQueue.h       - Cola con arreglo circular (tarea anterior)
└── Util.h             - Constantes compartidas (DEFAULT_MAX)
```

Todos los encabezados (`.h`) están en la misma carpeta que `PilasColas.cpp`. Como las clases son plantillas, su código está completo en los `.h` y no existen archivos `.cpp` separados para ellas.

## Compilación y ejecución

### Por terminal (g++):
```bash
g++ -std=c++11 -o pilas PilasColas.cpp
./pilas
```

### En Visual Studio:
1. Crear un proyecto de aplicación de consola vacío.
2. Agregar `PilasColas.cpp` a los archivos de código fuente y los `.h` a los archivos de encabezado.
3. Ejecutar con `Ctrl + F5`.

## Menú del programa

```
Seleccione el tipo de pila:
1. ArrayStack
2. LinkedStack
3. Salir
Opción:
```

Después de elegir la pila, el programa pide la expresión a evaluar. En esta versión la capacidad inicial de las pilas de `ArrayStack` es **5**, para que se pueda ver cómo se expanden al llenarse.

## Ejemplo de ejecución

Evaluación de `2 + 3 * 4` con `ArrayStack` (la salida real es más extensa; aquí se muestra abreviada):

```
Opción: 1
Escriba la expresión a analizar: 2 + 3 * 4
Pila números:		[ ]
Pila operadores:	[ ]
Expresión:		2+3*4

Token actual: 2
Es número. Push en pila de números.
Pila números:		[ 2 ]
Pila operadores:	[  ]
Expresión:		+3*4

Token actual: +
Es operador.
Push en la pila de operadores.
Pila números:		[ 2 ]
Pila operadores:	[ + ]
Expresión:		3*4

Token actual: 3
...
Token actual: *
Es operador.
Push en la pila de operadores.
Pila números:		[ 2, 3 ]
Pila operadores:	[ +, * ]
Expresión:		4

Token actual: 4
...
Fin de la expresión, procesando lo que queda en las pilas.
Pila números:		[ 2, 3, 4 ]
Pila operadores:	[ +, * ]

Procesando operación 3*4=12

Procesando operación 2+12=14

El resultado de la evaluación es: 14
```

Ejemplos de errores controlados:

```
Expresión: (2+3
Error, Hay un error en la expresión.
Detalles: Error, Paréntesis desemparejados

Expresión: 8/0
Detalles: Error, division entre 0.

Expresión: 2 $ 3
Detalles: Error, Ingresó una expresión no válida!

Expresión: 2 3
Detalles: Error, Expresión mal formada

Expresión: (vacía)
Error, Expresión vacía
```

---

# DIAGRAMAS

## Jerarquía de clases

```
        ┌──────────────────────┐              ┌──────────────────────┐
        │ Stack<E>             │              │ Queue<E>             │
        │ <<abstract>>         │              │ <<abstract>>         │
        └──────────┬───────────┘              └──────────┬───────────┘
                   │                                     │
          ┌────────┴─────────┐                           │
          │                  │                           │
┌─────────▼────────┐  ┌──────▼───────────┐     ┌─────────▼────────┐
│ ArrayStack<E>    │  │ LinkedStack<E>   │     │ ArrayQueue<E>    │
│ arreglo dinámico │  │ lista enlazada   │     │ arreglo circular │
└──────────────────┘  └────────┬─────────┘     └──────────────────┘
                               │ usa
                        ┌──────▼───────────┐
                        │ Node<E>          │
                        └──────────────────┘
```

## Asociaciones

```
PilasColas (main) ──── numStack (1) ──── Stack<double>*
PilasColas (main) ──── opStack (1) ──── Stack<char>*
        Apuntan a un ArrayStack o a un LinkedStack, según la opción elegida

LinkedStack<E> (1) ──── top (0..1) ──── Node<E>
Node<E> (1) ──── next (0..1) ──── Node<E>

ArrayStack<E> y ArrayQueue<E> incluyen Util.h (DEFAULT_MAX)
```

## Pila con arreglo vs. pila enlazada

```
ArrayStack (arreglo en el heap)          LinkedStack (nodos en el heap)

 índice   0   1   2   3   4              top
        ┌───┬───┬───┬───┬───┐             │
        │ 2 │ 3 │ 4 │   │   │             ▼
        └───┴───┴───┴───┴───┘           ┌───┬───┐   ┌───┬───┐   ┌───┬────┐
          base      ▲                   │ 4 │ ●─┼──▶│ 3 │ ●─┼──▶│ 2 │null│
                    size = 3            └───┴───┘   └───┴───┘   └───┴────┘
 Cuando size == max se duplica max.
```

## Expansión del arreglo (`expandArray`)

```
Antes (max = 5, lleno)        Después de un push más (max = 10)
┌───┬───┬───┬───┬───┐         ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
│ a │ b │ c │ d │ e │   ──▶   │ a │ b │ c │ d │ e │ f │   │   │   │   │
└───┴───┴───┴───┴───┘         └───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘
1. Crear un arreglo del doble de tamaño
2. Copiar los elementos
3. delete[] del arreglo viejo
4. elements apunta al nuevo arreglo y max = max * 2
```

---

# DIAGRAMA DE CLASES COMPLETO

```
╔════════════════════════════════════════════════════════╗
║ <<abstract>> STACK<E>                                  ║
╠════════════════════════════════════════════════════════╣
║ Constructores:                                         ║
║ + Stack()                                              ║
║ + Stack(const Stack<E>&) = delete                      ║
║ + ~Stack() (virtual)                                   ║
╠════════════════════════════════════════════════════════╣
║ Métodos:                                               ║
║ + operator=(const Stack<E>&) = delete                  ║
║ + push(element: E): void (virtual puro)                ║
║ + pop(): E (virtual puro)                              ║
║ + topValue(): E (virtual puro)                         ║
║ + clear(): void (virtual puro)                         ║
║ + isEmpty(): bool (virtual puro)                       ║
║ + getSize(): int (virtual puro)                        ║
║ + print(): void (virtual puro)                         ║
╚════════════════════════════════════════════════════════╝

╔════════════════════════════════════════════════════════╗
║ ARRAYSTACK<E>                         (extends Stack<E>)║
╠════════════════════════════════════════════════════════╣
║ Atributos:                                             ║
║ - elements: E*                                         ║
║ - max: int                                             ║
║ - size: int                                            ║
╠════════════════════════════════════════════════════════╣
║ Constructores:                                         ║
║ + ArrayStack(max: int = 1024)                          ║
║ + ~ArrayStack()                                        ║
╠════════════════════════════════════════════════════════╣
║ Métodos:                                               ║
║ - expandArray(): void                                  ║
║ + push(element: E): void                               ║
║ + pop(): E                                             ║
║ + topValue(): E                                        ║
║ + clear(): void                                        ║
║ + isEmpty(): bool                                      ║
║ + getSize(): int                                       ║
║ + print(): void                                        ║
╚════════════════════════════════════════════════════════╝

╔════════════════════════════════════════════════════════╗
║ LINKEDSTACK<E>                        (extends Stack<E>)║
╠════════════════════════════════════════════════════════╣
║ Atributos:                                             ║
║ - top: Node<E>*                                        ║
║ - size: int                                            ║
╠════════════════════════════════════════════════════════╣
║ Constructores:                                         ║
║ + LinkedStack()                                        ║
║ + ~LinkedStack()                                       ║
╠════════════════════════════════════════════════════════╣
║ Métodos:                                               ║
║ + push(element: E): void                               ║
║ + pop(): E                                             ║
║ + topValue(): E                                        ║
║ + clear(): void                                        ║
║ + isEmpty(): bool                                      ║
║ + getSize(): int                                       ║
║ + print(): void                                        ║
╚════════════════════════════════════════════════════════╝

╔════════════════════════════════════════════════════════╗
║ NODE<E>                                                ║
╠════════════════════════════════════════════════════════╣
║ Atributos:                                             ║
║ + element: E                                           ║
║ + next: Node<E>*                                       ║
╠════════════════════════════════════════════════════════╣
║ Constructores:                                         ║
║ + Node(element: E, next: Node<E>* = nullptr)           ║
╚════════════════════════════════════════════════════════╝

╔════════════════════════════════════════════════════════╗
║ <<abstract>> QUEUE<E>                                  ║
╠════════════════════════════════════════════════════════╣
║ Métodos:                                               ║
║ + enqueue(element: E): void (virtual puro)             ║
║ + dequeue(): E (virtual puro)                          ║
║ + frontValue(): E (virtual puro)                       ║
║ + clear(): void (virtual puro)                         ║
║ + isEmpty(): bool (virtual puro)                       ║
║ + getSize(): int (virtual puro)                        ║
║ + print(): void (virtual puro)                         ║
║ (constructor de copia y asignación eliminados)         ║
╚════════════════════════════════════════════════════════╝

╔════════════════════════════════════════════════════════╗
║ ARRAYQUEUE<E>                         (extends Queue<E>)║
╠════════════════════════════════════════════════════════╣
║ Atributos:                                             ║
║ - elements: E*                                         ║
║ - front: int                                           ║
║ - back: int                                            ║
║ - size: int                                            ║
║ - max: int                                             ║
╠════════════════════════════════════════════════════════╣
║ Constructores:                                         ║
║ + ArrayQueue(max: int = DEFAULT_MAX)                   ║
║ + ~ArrayQueue()                                        ║
╠════════════════════════════════════════════════════════╣
║ Métodos:                                               ║
║ + enqueue(element: E): void                            ║
║ + dequeue(): E                                         ║
║ + frontValue(): E                                      ║
║ + clear(): void                                        ║
║ + isEmpty(): bool                                      ║
║ + getSize(): int                                       ║
║ + print(): void                                        ║
╚════════════════════════════════════════════════════════╝

╔════════════════════════════════════════════════════════╗
║ PILASCOLAS (funciones del programa principal)          ║
╠════════════════════════════════════════════════════════╣
║ Funciones:                                             ║
║ removeWhiteSpace(expr: const string&): string          ║
║ getNextToken(expr: string&): string                    ║
║ isNumber(token: const string&): bool                   ║
║ isOperator(token: const string&): bool                 ║
║ getPrecedence(op: char): int                           ║
║ processOperation(numStack: Stack<double>&,             ║
║ opStack: Stack<char>&): void                           ║
║ main(): int                                            ║
╚════════════════════════════════════════════════════════╝
```

---

## Características implementadas

### Genericidad
- Todas las estructuras son plantillas, por lo que la misma clase sirve para `double`, `char` o cualquier otro tipo (el evaluador usa una pila de `double` y otra de `char`)

### Polimorfismo
- `processOperation()` recibe `Stack<double>&` y `Stack<char>&`: funciona igual con `ArrayStack` y con `LinkedStack`
- Para cambiar de implementación basta con cambiar el objeto que se crea, sin tocar el algoritmo

### Memoria dinámica
- `ArrayStack` libera el arreglo en su destructor y el arreglo viejo en cada expansión
- `LinkedStack` libera cada nodo al hacer `pop` y todos los nodos en su destructor
- El programa principal libera con `delete` las dos pilas después de cada evaluación, incluso si hubo un error en la expresión

### Validación y manejo de errores
- Lectura segura de la opción del menú (`cin.clear()` y `cin.ignore()`)
- Errores de la expresión con `runtime_error`, capturados y mostrados sin cerrar el programa
- Las pilas lanzan un error si se intenta hacer `pop` o `topValue` con la pila vacía

### Visualización paso a paso
- En cada token se muestra la acción realizada, el contenido de ambas pilas y lo que falta de la expresión
- Cada operación procesada se muestra con su resultado (por ejemplo, `Procesando operación 3*4=12`)

## Notas importantes
- Solo se aceptan **enteros no negativos**: no hay números decimales ni signo negativo unario (por ejemplo, `-3+2` o `2*-3` generan un error). Los resultados sí pueden tener decimales, porque el cálculo usa `double`.
- Todos los operadores se evalúan de izquierda a derecha cuando tienen la misma precedencia, incluida la potencia (`2^3^2` se evalúa como `(2^3)^2 = 64`).
- `ArrayStack` muestra sus elementos **de la base hacia el tope** (el tope queda a la derecha), mientras que `LinkedStack` los muestra **del tope hacia la base** (el tope queda a la izquierda).
- Las pilas de `ArrayStack` empiezan con capacidad 5 en el evaluador, solo para que se pueda ver la expansión; el valor por defecto de la clase es 1024.
- `ArrayQueue` tiene tamaño fijo y no se expande; `ArrayStack` sí.
- `ArrayQueue` y `Queue` se conservan de la tarea anterior y no intervienen en el evaluador.
- El programa usa `system("cls")`, que solo funciona en Windows; en Linux o macOS la limpieza de pantalla no se realiza.
- Los mensajes llevan tildes y signos especiales; en algunas consolas de Windows puede ser necesario configurar la codificación UTF-8 (por ejemplo, con `chcp 65001`).

## Autor
Owel Jafet Gutiérrez Ortiz

## Carnet
2026800869

## Profesor
Mauricio Avilés Cisneros

## Fecha de entrega
02/09/2026

## Institución
Instituto Tecnológico de Costa Rica
Escuela de Computación
Bachillerato en Ingeniería en Computación
