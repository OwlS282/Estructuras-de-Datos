# Tarea Corta 3 - Lista: Caja de Herramientas

## Descripción
Esta tarea consiste en la implementación de listas genéricas en C++ y su uso en una simulación de una **caja de herramientas**. Se implementa el TAD *Lista* de tres formas distintas (**arreglo dinámico**, **lista enlazada simple** y **lista doblemente enlazada**) a partir de una misma clase abstracta, y el usuario escoge cuál usar al iniciar el programa. La caja de herramientas tiene un **peso máximo** y un **volumen máximo**, y solo permite agregar herramientas mientras no se superen ambos límites. El programa permite:
- Escoger la implementación de lista (`ArrayList`, `LinkedList` o `DLinkedList`)
- Escoger el tamaño de la caja (pequeña, mediana o grande), que define sus límites de peso y volumen
- Agregar herramientas de un catálogo de 12 herramientas
- Remover una herramienta cualquiera de la caja
- Vaciar la caja por completo
- Ver en todo momento el contenido de la caja y el peso y volumen que lleva acumulados
- Validar las entradas del usuario sin que el programa se cierre inesperadamente

> Los mensajes que muestra el programa están en inglés, igual que los nombres de las herramientas.

## Requisitos del problema

### List (clase abstracta genérica)
- Define la interfaz común de todas las listas mediante métodos virtuales puros
- La lista mantiene una **posición actual** (cursor) con la que se navega y se opera
- **Modificar**: `insert(element)` (en la posición actual), `append(element)` (al final), `setElement(element)`, `remove()` y `clear()`
- **Consultar**: `getElement()`, `getPos()`, `getSize()`, `atStart()` y `atEnd()`
- **Navegar**: `goToStart()`, `goToEnd()`, `goToPos(pos)`, `next()` y `previous()`
- **print()**: Muestra la lista en pantalla
- Constructor de copia y operador de asignación eliminados; destructor virtual

### ArrayList
- Implementación con un **arreglo dinámico** de tamaño fijo (`DEFAULT_MAX` = 1024)
- La posición actual es el **índice** del elemento actual; `pos == size` significa que no hay elemento actual (el cursor está al final)
- `insert` y `remove` desplazan los elementos del arreglo
- `clear` es un borrado lógico (`pos = size = 0`)

### LinkedList
- Implementación con una **lista enlazada simple** y un **nodo centinela** al inicio (`head`)
- Mantiene un puntero al último nodo (`tail`), por lo que `append` es inmediato
- El puntero `current` apunta al nodo **anterior** al elemento actual; el elemento actual es `current->next`
- `previous()` debe recorrer la lista desde `head`, porque los nodos no conocen a su anterior

### DLinkedList
- Implementación con una **lista doblemente enlazada** con **dos nodos centinela** (`head` y `tail`)
- Cada nodo conoce a su siguiente y a su anterior (`DNode`), por lo que `previous()` es inmediato
- Igual que en `LinkedList`, `current` apunta al nodo anterior al elemento actual

### Node y DNode
- `Node<E>`: nodo de lista simple (`element` y `next`), con un segundo constructor sin elemento para el centinela
- `DNode<E>`: nodo de lista doble (`element`, `next` y `previous`), con un segundo constructor sin elemento para los centinelas

### Tool
- Representa una herramienta: **nombre**, **peso** y **volumen**
- `operator<<` permite imprimirla con `cout` como `Hammer (w=1.00, v=3.50)`
- Tiene constructor por defecto, necesario para los nodos centinela y para el arreglo de `ArrayList`

### ToolBox
- Caja de herramientas: guarda los límites (`maxWeight`, `maxVolume`), los valores acumulados (`currentWeight`, `currentVolume`) y un puntero `List<Tool>*`
- Según la opción del usuario, crea internamente un `ArrayList`, un `LinkedList` o un `DLinkedList`
- **add(tool)**: Agrega al final de la lista si no se excede el peso ni el volumen
- **remove(pos)**: Remueve la herramienta de la posición indicada (desde 0) y actualiza el peso y el volumen
- **clear()**, **getTool(pos)**, **toolCount()**, getters de los límites y valores actuales
- **print()**: Muestra el contenido numerado, el peso (`actual/máximo`) y el volumen (`actual/máximo`)

### main (programa principal)
- Contiene el catálogo de 12 herramientas, el menú y las funciones `clearInput()` y `getValidInput(min, max)`
- Crea la caja según el tipo de lista y el tamaño escogidos, y la libera al salir

## Tamaños de la caja

| Opción | Tamaño | Peso máximo | Volumen máximo |
|--------|--------|-------------|----------------|
| 1 | Small (pequeña) | 2 | 10 |
| 2 | Medium (mediana) | 4 | 14 |
| 3 | Large (grande) | 6 | 20 |

## Catálogo de herramientas

| # | Herramienta | Peso | Volumen |
|---|-------------|------|---------|
| 1 | Phillips screwdriver | 0.25 | 1.50 |
| 2 | Flat screwdriver | 0.25 | 1.50 |
| 3 | Hammer | 1.00 | 3.50 |
| 4 | French wrench | 0.75 | 3.00 |
| 5 | Hacksaw | 0.50 | 3.00 |
| 6 | Scissors | 0.25 | 2.20 |
| 7 | Cutter | 0.25 | 1.50 |
| 8 | Pliers | 0.50 | 1.80 |
| 9 | Pincers | 0.25 | 2.00 |
| 10 | Drill | 2.00 | 4.00 |
| 11 | Locking pliers | 0.50 | 2.50 |
| 12 | Measuring tape | 0.50 | 1.50 |

## Reglas del negocio
- Una herramienta solo se agrega si `peso actual + peso de la herramienta` **no supera** el peso máximo.
- Una herramienta solo se agrega si `volumen actual + volumen de la herramienta` **no supera** el volumen máximo.
- Se revisa primero el peso y después el volumen; si alguno se excede, la herramienta no se agrega y se muestra el error.
- Las herramientas se agregan siempre **al final** de la lista, y se pueden repetir (se puede agregar más de un martillo, por ejemplo).
- Al remover una herramienta se resta su peso y su volumen de los valores actuales.
- No se puede remover de una caja vacía.
- Al vaciar la caja, el peso y el volumen vuelven a 0.

## Reglas de validación
- Todas las opciones se leen como enteros y deben estar dentro del rango del menú correspondiente:
  - Tipo de lista: 1 a 3
  - Tamaño de la caja: 1 a 3
  - Operación: 0 a 3
  - Herramienta a agregar: 1 a 12
  - Herramienta a remover: 1 a la cantidad de herramientas en la caja
- Si se escribe algo que no es un número o un número fuera de rango, se muestra el error y se vuelve a pedir la opción.
- Los errores de la caja (límites excedidos, posición inválida) lanzan `runtime_error`, que se captura y se muestra sin cerrar el programa.

## Modelo de posición actual (cursor)

Las tres listas comparten la misma interfaz, pero cada una guarda la posición actual de forma distinta:

```
ArrayList (pos = índice del elemento actual)

 índice      0     1     2     3
          ┌─────┬─────┬─────┬─────┬─────┐
          │  A  │  B  │  C  │     │     │      size = 3
          └─────┴─────┴─────┴─────┴─────┘      pos = 1  →  elemento actual: B
                   ▲                           pos = 3  →  al final, no hay actual


LinkedList (current = nodo ANTERIOR al elemento actual)

 head                                      tail
 ┌──────────┐   ┌───┐   ┌───┐   ┌───┐
 │centinela │──▶│ A │──▶│ B │──▶│ C │──▶ null
 └──────────┘   └───┘   └───┘   └───┘
      pos 0       pos 1   pos 2   pos 3

 pos = 1  →  current apunta a A  →  elemento actual = current->next = B


DLinkedList (dos centinelas, enlaces en ambas direcciones)

 null ◀─ head ◀──▶ A ◀──▶ B ◀──▶ C ◀──▶ tail ─▶ null
        (centinela)                   (centinela)

 current también apunta al nodo anterior al elemento actual
```

## Complejidad de las operaciones

| Operación | ArrayList | LinkedList | DLinkedList |
|-----------|-----------|------------|-------------|
| `append` | O(1) | O(1) | O(1) |
| `insert` (en la posición actual) | O(n) | O(1) | O(1) |
| `remove` (en la posición actual) | O(n) | O(1) | O(1) |
| `getElement` / `setElement` | O(1) | O(1) | O(1) |
| `next` | O(1) | O(1) | O(1) |
| `previous` | O(1) | O(n) | O(1) |
| `goToStart` / `goToEnd` | O(1) | O(1) | O(1) |
| `goToPos` | O(1) | O(n) | O(n) |
| `getPos` | O(1) | O(n) | O(n) |
| `clear` | O(1) (borrado lógico) | O(n) | O(n) |

## Conceptos implementados

- **Tipo abstracto de datos (TAD)**: `List` define *qué* operaciones tiene una lista; cada implementación define *cómo*
- **Plantillas (templates)**: `List<E>`, `ArrayList<E>`, `LinkedList<E>`, `DLinkedList<E>`, `Node<E>` y `DNode<E>`
- **Herencia y polimorfismo**: `ToolBox` usa un `List<Tool>*` y funciona igual con cualquiera de las tres implementaciones; la elegida se decide en tiempo de ejecución
- **Composición**: `ToolBox` contiene una lista, y la lista contiene herramientas
- **Destructor virtual**: Permite liberar la lista correctamente a través de un puntero a la clase base
- **Memoria dinámica**: Arreglo dinámico, nodos creados y liberados uno por uno
- **Nodos centinela**: Nodos sin dato al inicio (y al final, en la lista doble) que evitan casos especiales al insertar y eliminar
- **Sobrecarga de operadores**: `operator<<` como función amiga (`friend`) de `Tool`
- **Manejo de excepciones**: `throw runtime_error` y `try/catch`
- **Constantes de compilación**: `#define DEFAULT_MAX` y `#pragma once`
- **Encapsulamiento**: Atributos privados en las listas y en `ToolBox`

## Requisitos técnicos
- Compilador de C++ con soporte para C++11 o superior
- IDE: Visual Studio, Code::Blocks, CLion o Visual Studio Code, o `g++` por terminal

## Estructura del proyecto

```
CajaHerramientas/
├── main.cpp           - Programa principal (menús y catálogo de herramientas)
├── Tool.h             - Herramienta (nombre, peso y volumen)
├── ToolBox.h          - Caja de herramientas (límites y lista)
├── List.h             - Clase abstracta de las listas
├── ArrayList.h        - Lista con arreglo dinámico
├── LinkedList.h       - Lista enlazada simple
├── DLinkedList.h      - Lista doblemente enlazada
├── Node.h             - Nodo de lista simple
├── DNode.h            - Nodo de lista doble
└── Util.h             - Constantes compartidas (DEFAULT_MAX)
```

Todos los archivos están en la misma carpeta. Como las listas y los nodos son plantillas, su código completo está en los `.h`; el único archivo `.cpp` es `main.cpp`.

## Compilación y ejecución

### Por terminal (g++):
```bash
g++ -std=c++11 -o toolbox main.cpp
./toolbox
```

### En Visual Studio:
1. Crear un proyecto de aplicación de consola vacío.
2. Agregar `main.cpp` a los archivos de código fuente y los `.h` a los archivos de encabezado.
3. Ejecutar con `Ctrl + F5`.

## Ejemplo de ejecución

Uso de una caja pequeña (límites: peso 2 y volumen 10) con `ArrayList`:

```
Choose the type of list to use:
1. ArrayList
2. LinkedList
3. DLinkedList
Option: 1

Choose the size of the toolbox:
1. Small (max weight = 2, max volume = 10)
2. Medium (max weight = 4, max volume = 14)
3. Large (max weight = 6, max volume = 20)
Option: 1

Toolbox contents:
	(empty)
Weight: 0.00/2.00
Volume: 0.00/10.00

Choose toolbox operation:
1. Add tool
2. Remove tool
3. Clear toolbox
0. Exit
Option: 1

Choose tool to add:
1. Phillips screwdriver (w=0.25, v=1.50)
2. Flat screwdriver (w=0.25, v=1.50)
3. Hammer (w=1.00, v=3.50)
...
12. Measuring tape (w=0.50, v=1.50)
Option: 3
Tool added successfully!

Toolbox contents:
	1. Hammer (w=1.00, v=3.50)
Weight: 1.00/2.00
Volume: 3.50/10.00

Choose toolbox operation:
...
Option: 1
...
Option: 10
Error: The toolbox weight limit has been exceeded.

Toolbox contents:
	1. Hammer (w=1.00, v=3.50)
Weight: 1.00/2.00
Volume: 3.50/10.00

Choose toolbox operation:
...
Option: 2

Choose tool to remove:
1. Hammer (w=1.00, v=3.50)
Option: 1
Tool removed: Hammer (w=1.00, v=3.50)
```

Ejemplos de mensajes de error:

```
Error: Please enter a valid number.
Error: Option must be between 1 and 3.
Error: The toolbox weight limit has been exceeded.
Error: The toolbox volume limit has been exceeded.
Toolbox is empty!
```

---

# DIAGRAMAS

## Jerarquía de clases

```
                    ┌──────────────────────┐
                    │ List<E>              │
                    │ <<abstract>>         │
                    └──────────┬───────────┘
                               │
          ┌────────────────────┼────────────────────┐
          │                    │                    │
┌─────────▼────────┐  ┌────────▼─────────┐  ┌───────▼──────────┐
│ ArrayList<E>     │  │ LinkedList<E>    │  │ DLinkedList<E>   │
│ arreglo dinámico │  │ lista simple     │  │ lista doble      │
└──────────────────┘  └────────┬─────────┘  └───────┬──────────┘
                               │ usa                │ usa
                      ┌────────▼─────────┐  ┌───────▼──────────┐
                      │ Node<E>          │  │ DNode<E>         │
                      └──────────────────┘  └──────────────────┘
```

## Asociaciones

```
main (1) ──── toolbox (1) ──── ToolBox
main (1) ──── availableTools (12) ──── Tool

ToolBox (1) ──── tools (1) ──── List<Tool>*
        Apunta a un ArrayList, un LinkedList o un DLinkedList, según la opción elegida

List<Tool> (1) ──── elementos (0..*) ──── Tool
LinkedList<E> (1) ──── head, current, tail ──── Node<E>
DLinkedList<E> (1) ──── head, current, tail ──── DNode<E>
ArrayList<E> y ToolBox incluyen Util.h (DEFAULT_MAX)
```

---

# DIAGRAMA DE CLASES COMPLETO

```
╔════════════════════════════════════════════════════════╗
║ <<abstract>> LIST<E>                                   ║
╠════════════════════════════════════════════════════════╣
║ Constructores:                                         ║
║ + List()                                               ║
║ + List(const List<E>&) = delete                        ║
║ + ~List() (virtual)                                    ║
╠════════════════════════════════════════════════════════╣
║ Métodos (virtuales puros):                             ║
║ + insert(element: E): void                             ║
║ + append(element: E): void                             ║
║ + setElement(element: E): void                         ║
║ + remove(): E                                          ║
║ + clear(): void                                        ║
║ + getElement(): E                                      ║
║ + goToStart(): void                                    ║
║ + goToEnd(): void                                      ║
║ + goToPos(pos: int): void                              ║
║ + next(): void                                         ║
║ + previous(): void                                     ║
║ + atEnd(): bool                                        ║
║ + atStart(): bool                                      ║
║ + getPos(): int                                        ║
║ + getSize(): int                                       ║
║ + print(): void                                        ║
╚════════════════════════════════════════════════════════╝

╔════════════════════════════════════════════════════════╗
║ ARRAYLIST<E>                           (extends List<E>)║
╠════════════════════════════════════════════════════════╣
║ Atributos:                                             ║
║ - elements: E*                                         ║
║ - max: int                                             ║
║ - size: int                                            ║
║ - pos: int                                             ║
╠════════════════════════════════════════════════════════╣
║ Constructores:                                         ║
║ + ArrayList(max: int = DEFAULT_MAX)                    ║
║ + ~ArrayList()                                         ║
╠════════════════════════════════════════════════════════╣
║ Métodos:                                               ║
║ + (implementa todos los métodos de List<E>)            ║
╚════════════════════════════════════════════════════════╝

╔════════════════════════════════════════════════════════╗
║ LINKEDLIST<E>                          (extends List<E>)║
╠════════════════════════════════════════════════════════╣
║ Atributos:                                             ║
║ - head: Node<E>*  (centinela)                          ║
║ - current: Node<E>*                                    ║
║ - tail: Node<E>*                                       ║
║ - size: int                                            ║
╠════════════════════════════════════════════════════════╣
║ Constructores:                                         ║
║ + LinkedList()                                         ║
║ + ~LinkedList()                                        ║
╠════════════════════════════════════════════════════════╣
║ Métodos:                                               ║
║ + (implementa todos los métodos de List<E>)            ║
╚════════════════════════════════════════════════════════╝

╔════════════════════════════════════════════════════════╗
║ DLINKEDLIST<E>                         (extends List<E>)║
╠════════════════════════════════════════════════════════╣
║ Atributos:                                             ║
║ - head: DNode<E>*  (centinela inicial)                 ║
║ - tail: DNode<E>*  (centinela final)                   ║
║ - current: DNode<E>*                                   ║
║ - size: int                                            ║
╠════════════════════════════════════════════════════════╣
║ Constructores:                                         ║
║ + DLinkedList()                                        ║
║ + ~DLinkedList()                                       ║
╠════════════════════════════════════════════════════════╣
║ Métodos:                                               ║
║ + (implementa todos los métodos de List<E>)            ║
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
║ + Node(next: Node<E>* = nullptr)  (centinela)          ║
╚════════════════════════════════════════════════════════╝

╔════════════════════════════════════════════════════════╗
║ DNODE<E>                                               ║
╠════════════════════════════════════════════════════════╣
║ Atributos:                                             ║
║ + element: E                                           ║
║ + next: DNode<E>*                                      ║
║ + previous: DNode<E>*                                  ║
╠════════════════════════════════════════════════════════╣
║ Constructores:                                         ║
║ + DNode(element: E, next: DNode<E>*,                   ║
║ previous: DNode<E>*)                                   ║
║ + DNode(next: DNode<E>*, previous: DNode<E>*)          ║
║ (centinela)                                            ║
╚════════════════════════════════════════════════════════╝

╔════════════════════════════════════════════════════════╗
║ TOOL                                                   ║
╠════════════════════════════════════════════════════════╣
║ Atributos:                                             ║
║ + name: string                                         ║
║ + weight: double                                       ║
║ + volume: double                                       ║
╠════════════════════════════════════════════════════════╣
║ Constructores:                                         ║
║ + Tool()                                               ║
║ + Tool(name: string, weight: double, volume: double)   ║
║ + ~Tool()                                              ║
╠════════════════════════════════════════════════════════╣
║ Métodos:                                               ║
║ + friend operator<<(os: ostream&, tool: const Tool&):   ║
║ ostream&                                               ║
╚════════════════════════════════════════════════════════╝

╔════════════════════════════════════════════════════════╗
║ TOOLBOX                                                ║
╠════════════════════════════════════════════════════════╣
║ Atributos:                                             ║
║ - maxWeight: double                                    ║
║ - maxVolume: double                                    ║
║ - currentWeight: double                                ║
║ - currentVolume: double                                ║
║ - tools: List<Tool>*                                   ║
╠════════════════════════════════════════════════════════╣
║ Constructores:                                         ║
║ + ToolBox(listType: int, maxWeight: double,            ║
║ maxVolume: double)                                     ║
║ + ~ToolBox()                                           ║
╠════════════════════════════════════════════════════════╣
║ Métodos:                                               ║
║ + add(tool: Tool): void                                ║
║ + remove(pos: int): Tool                               ║
║ + clear(): void                                        ║
║ + getTool(pos: int): Tool                              ║
║ + toolCount(): int                                     ║
║ + getMaxWeight(): double                               ║
║ + getMaxVolume(): double                               ║
║ + getCurrentWeight(): double                           ║
║ + getCurrentVolume(): double                           ║
║ + print(): void                                        ║
╚════════════════════════════════════════════════════════╝

╔════════════════════════════════════════════════════════╗
║ MAIN (programa principal)                              ║
╠════════════════════════════════════════════════════════╣
║ Variables globales:                                    ║
║ availableTools: Tool[12]                               ║
╠════════════════════════════════════════════════════════╣
║ Funciones:                                             ║
║ clearInput(): void                                     ║
║ getValidInput(minValue: int, maxValue: int): int       ║
║ main(): int                                            ║
╚════════════════════════════════════════════════════════╝
```

## Asociaciones y multiplicidades

```
ToolBox ─────────────────────────── List<Tool>
1                                   1
(Composición: la caja crea y destruye su lista)

List<Tool> ──────────────────────── Tool
1                                   0..*

LinkedList ──────────────────────── Node
1                                   0..*  (más el nodo centinela)

DLinkedList ─────────────────────── DNode
1                                   0..*  (más los dos nodos centinela)

main ────────────────────────────── ToolBox
1                                   1
```

---

## Características implementadas

### Polimorfismo
- `ToolBox` solo conoce la interfaz `List<Tool>`: el código de agregar, remover y mostrar es el mismo para las tres implementaciones
- Para cambiar de lista basta con cambiar el objeto que se crea en el constructor de `ToolBox`

### Control de límites
- La caja lleva la cuenta de peso y volumen acumulados y los actualiza al agregar, remover y vaciar
- La verificación se hace antes de modificar la lista, así que una herramienta rechazada no deja la caja en un estado inconsistente

### Memoria dinámica
- `ToolBox` libera su lista en el destructor, y cada lista libera sus nodos (o su arreglo) en el suyo
- El programa principal libera la caja al salir, también cuando ocurre un error fatal

### Validación y manejo de errores
- Lectura segura de enteros con rango (`cin.fail()`, `cin.clear()` y `cin.ignore()`)
- Los errores de la caja se capturan con `try/catch` y se muestran sin terminar el programa

### Salida por consola
- El contenido de la caja se muestra numerado, junto con el peso y el volumen en la forma `actual/máximo` con dos decimales

## Notas importantes
- Los mensajes del programa y los nombres de las herramientas están en inglés.
- La posición que se pide al usuario para remover empieza en 1, pero `ToolBox` trabaja internamente con posiciones desde 0.
- `ToolBox::print()` obtiene cada herramienta con `getTool(i)`, que usa `goToPos(i)`; en las listas enlazadas eso recorre la lista desde el inicio en cada herramienta, lo cual no importa con tan pocas herramientas.
- `ArrayList` tiene capacidad fija de 1024 elementos y no se expande; en este programa los límites de peso hacen imposible llegar a ese número.
- Los pesos y volúmenes son `double`, por lo que las comparaciones con los límites pueden verse afectadas por la precisión de los decimales (por ejemplo, los volúmenes `2.20` y `1.80`).
- Los datos no se guardan en disco: al cerrar el programa se pierde el contenido de la caja.
- Se siguieron las convenciones de nomenclatura de C++ y se incluyó el encabezado con los datos del autor en todos los archivos.

## Autor
Owel Jafet Gutiérrez Ortiz

## Carnet
2026800869

## Profesor
Mauricio Avilés Cisneros

## Fecha de entrega
24/09/2026

## Institución
Instituto Tecnológico de Costa Rica
Escuela de Computación
Bachillerato en Ingeniería en Computación
