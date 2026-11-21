# Tarea Corta 8 - Árboles de búsqueda binaria y diccionarios

## Descripción
Esta tarea consiste en la implementación de un **árbol de búsqueda binaria** genérico (`BSTree`) en C++ y de un **diccionario** de pares llave-valor (`BSTDictionary`) construido sobre él. Se define el TAD *Diccionario* con una clase abstracta (`Dictionary`) y se implementa con un árbol donde se guardan los pares (`Pair`) ordenados por llave. Además de las operaciones básicas, el diccionario tiene `update` (copiar los pares de otro diccionario) y `zip` (empatar una lista de llaves con una lista de valores). El programa principal es un menú de consola que trabaja con **dos diccionarios** de llaves enteras y valores de texto. El programa permite:
- Elegir sobre cuál de los dos diccionarios se hace cada operación
- Insertar un par llave-valor (`insert`) y eliminar el par de una llave (`remove`)
- Consultar (`getValue`) y modificar (`setValue`) el valor de una llave
- Verificar si una llave existe (`contains`)
- Vaciar el diccionario (`clear`)
- Obtener las llaves (`getKeys`) y los valores (`getValues`) en una lista
- Copiar al diccionario actual los pares del otro (`update`)
- Empatar una lista de llaves con una lista de valores (`zip`)
- Ver en todo momento el contenido de los dos diccionarios
- Validar las entradas del usuario e informar los errores sin que el programa se cierre inesperadamente

> Los mensajes que muestra el programa están en inglés.

## Requisitos del problema

### Dictionary (clase abstracta genérica)
- Define la interfaz del diccionario mediante métodos virtuales puros, con una llave de tipo `K` y un valor de tipo `V`
- **Modificar**: `insert(key, value)`, `remove(key)`, `setValue(key, value)` y `clear()`
- **Consultar**: `getValue(key)`, `contains(key)`, `isEmpty()` y `getSize()`
- **Obtener**: `getKeys()` y `getValues()`, que retornan una lista en memoria dinámica
- **Operaciones adicionales**: `update(D)` y `zip(keys, values)`
- **print()**: Muestra el diccionario en pantalla
- Constructor de copia y operador de asignación eliminados; destructor virtual

### BSTDictionary
- Implementación de `Dictionary` con un `BSTree<Pair<K, V>>*` (atributo `pairs`)
- Los pares se guardan **ordenados por llave** y las llaves **no se pueden repetir**
- `insert`, `remove`, `getValue` y `contains` se resuelven llamando al árbol con un `Pair` que solo tiene llave (el árbol compara únicamente la llave)
- `setValue` elimina el par existente y lo inserta con el nuevo valor
- `getKeys()` y `getValues()` recorren los elementos del árbol en orden y arman una lista nueva; los valores salen según el orden de las llaves
- Quien llama a `getKeys()` o `getValues()` debe liberar la lista con `delete`
- **update(D)**: agrega todos los pares de `D`; si la llave ya existe actualiza el valor y si no la inserta. `D` no se modifica.
- **zip(keys, values)**: empata llaves y valores posición por posición, ignorando los sobrantes de la lista más larga; si la llave ya existe actualiza el valor. Las listas no se eliminan y su posición actual se restaura al terminar.

### BSTree (árbol de búsqueda binaria)
- Guarda los elementos en nodos (`BSTNode`); para cada nodo, los elementos menores están en el subárbol izquierdo y los mayores en el derecho
- **No admite elementos duplicados**
- **Modificar**: `insert(element)`, `remove(element)` y `clear()`
- **Consultar**: `contains(element)`, `find(element)`, `isEmpty()` y `getSize()`
- **getElements()**: Retorna en una lista (en memoria dinámica) todos los elementos en orden, mediante un recorrido **inorden**
- **print()**: Muestra los elementos en orden
- `insert`, `find`, `remove`, `clear`, `getElements` y `getSize` usan métodos auxiliares **recursivos** privados
- Lanza `runtime_error` al insertar un elemento repetido o al buscar/eliminar uno que no existe

### BSTNode
- Guarda un `element` y los punteros `left` y `right` a sus hijos
- `childrenCount()` retorna la cantidad de hijos (0, 1 o 2) y `getOnlyChild()` el único hijo de un nodo; ambos facilitan la eliminación

### Pair
- Clase auxiliar con la **llave** (`key`) y el **valor** (`value`), ambos públicos
- Todos los operadores de comparación (`==`, `!=`, `<`, `<=`, `>`, `>=`) comparan **solo la llave**, lo que permite ordenar los pares en el árbol y buscar un par con solo su llave
- `operator<<` imprime el par como `(llave, valor)`
- Tiene tres constructores: con llave y valor, solo con llave (para buscar) y por defecto

### List, LinkedList y Node
- `List<E>`: clase abstracta con la interfaz de la lista (insertar, agregar al final, eliminar, consultar, navegar e imprimir)
- `LinkedList<E>`: lista enlazada simple con nodo cabecera, puntero al último nodo y un puntero `current` al nodo anterior al elemento actual
- `Node<E>`: nodo de lista simple (`element` y `next`)
- En esta tarea las listas se usan para retornar elementos del árbol (`getElements`), llaves y valores del diccionario, y como parámetros de `zip`

### main (programa principal)
- Crea dos `BSTDictionary<int, string>` en memoria dinámica y los libera con `delete` al salir
- Funciones: `readInt()`, `showDictionaries()`, `showMenu()` y `execute(op, d, other)`
- Pregunta la operación y el diccionario sobre el que se aplica; para `update`, el otro diccionario es el que se copia
- Captura con `try/catch` los errores del árbol y continúa

## Opciones del menú

| Opción | Operación | Descripción |
|--------|-----------|-------------|
| 1 | `insert` | Inserta un par (llave y valor); error si la llave ya existe |
| 2 | `remove` | Elimina la llave y muestra el valor que tenía; error si no existe |
| 3 | `getValue` | Muestra el valor de una llave; error si no existe |
| 4 | `setValue` | Cambia el valor de una llave; error si no existe |
| 5 | `contains` | Indica si la llave existe |
| 6 | `clear` | Vacía el diccionario |
| 7 | `getKeys` | Muestra la lista de llaves, en orden |
| 8 | `getValues` | Muestra la lista de valores, según el orden de las llaves |
| 9 | `update` | Copia al diccionario elegido los pares del otro diccionario |
| 10 | `zip` | Pide `n` llaves y `n` valores y los empata |
| 0 | Salir | Termina el programa |

## Funcionamiento del árbol

### Inserción
Se baja desde la raíz: si el elemento es menor se va al hijo izquierdo y si es mayor al derecho, hasta encontrar un lugar vacío donde se crea el nodo. Si se encuentra un elemento igual, se lanza el error.

### Eliminación
Según la cantidad de hijos que tenga el nodo que se elimina:

| Hijos | Qué se hace |
|-------|-------------|
| 0 (hoja) | Se elimina el nodo |
| 1 | Se elimina el nodo y su único hijo ocupa su lugar |
| 2 | Se busca el **sucesor** (el menor del subárbol derecho), se **intercambian** los elementos y se elimina el elemento en el subárbol derecho, donde ahora tiene 0 o 1 hijo |

La eliminación retorna el elemento que se eliminó, por lo que `BSTDictionary::remove` puede retornar su valor.

```
Eliminar 50 (dos hijos) del árbol:

          50                         60                        60
        ┌──┴──┐                    ┌──┴──┐                   ┌──┴──┐
       30     70     intercambia  30     70    elimina 50    30     70
      ┌─┴─┐  ┌─┴─┐   con 60     ┌─┴─┐  ┌─┴─┐   (hoja)      ┌─┴─┐     └─┐
     20  40 60  80              20  40 50  80               20  40       80
```

### Recorrido inorden
`getElements` visita primero el subárbol izquierdo, luego el nodo y por último el derecho, por lo que los elementos quedan **ordenados** por llave. Así `getKeys`, `getValues` y `print` siempre muestran los pares ordenados.

```
Árbol:      50                 Inorden:  20, 30, 40, 50, 60, 70, 80
          ┌──┴──┐
         30     70
        ┌─┴─┐  ┌─┴─┐
       20  40 60  80
```

## Complejidad de las operaciones

Con `n` pares en el diccionario y un árbol de altura `h`:

| Operación | Complejidad |
|-----------|-------------|
| `insert` / `remove` / `getValue` / `contains` | O(h) |
| `setValue` | O(h) (un `remove` y un `insert`) |
| `getKeys` / `getValues` / `print` | O(n) |
| `getSize` | O(n) (se cuenta recorriendo el árbol) |
| `clear` | O(n) |
| `isEmpty` | O(1) |
| `update(D)` (con `m` pares en `D`) | O(m · h) (más lo que cuesta obtener las llaves de `D`) |
| `zip` (con `k` pares empatados) | O(k · h) |

La altura `h` es O(log n) cuando el árbol está **balanceado** (en promedio, si las llaves llegan en orden aleatorio) y O(n) en el peor caso, por ejemplo si las llaves se insertan en orden creciente: el árbol queda como una lista.

## Reglas del negocio
- Las llaves del diccionario **no se repiten**: insertar una llave que ya existe es un error.
- Consultar (`getValue`), modificar (`setValue`) o eliminar (`remove`) una llave que no existe es un error.
- Los pares se ordenan solo por la **llave**; el valor no participa en la comparación.
- `getKeys()` retorna las llaves en orden y `getValues()` los valores según ese mismo orden.
- `update(D)` no modifica a `D`: si la llave existe en este diccionario se actualiza su valor, y si no, se inserta.
- `zip` empata por posición y se detiene al terminar la lista más corta; los elementos sobrantes de la más larga se ignoran.
- En `zip`, si una llave aparece varias veces en la lista de llaves (o ya existía), queda el **último** valor que se le empató.
- Las listas que recibe `zip` y el diccionario que recibe `update` no se eliminan ni se modifican.
- Las operaciones que fallan no modifican el diccionario.

## Reglas de validación
- Los números (operación, diccionario, llaves y cantidad de elementos de `zip`) se leen con `readInt()`: si se escribe algo que no es un número se muestra el error, se limpia la entrada y se vuelve a pedir.
- El diccionario se elige con 1 o 2; cualquier otro número muestra `Error, invalid dictionary.`
- La operación debe estar entre 0 y 10; cualquier otro número muestra `Error, invalid option.`
- Los errores del árbol lanzan `runtime_error`, que se captura en `main` y se muestra después de `Error, the operation cannot be performed:`:

| Operación | Condición del error | Mensaje |
|-----------|---------------------|---------|
| `insert` | La llave ya existe | `Error, Duplicated element.` |
| `remove` | La llave no existe | `Error, element not found.` |
| `setValue` | La llave no existe (falla el `remove` interno) | `Error, element not found.` |
| `getValue` | La llave no existe | `Error, element not found` |

## Conceptos implementados

- **Árbol de búsqueda binaria (BST)**: Árbol donde cada nodo tiene menores a la izquierda y mayores a la derecha
- **Recursión**: Inserción, búsqueda, eliminación, recorrido y conteo se resuelven con métodos auxiliares recursivos
- **Recorrido inorden**: Entrega los elementos ordenados
- **Eliminación con sucesor inorden**: Caso de dos hijos resuelto con el menor del subárbol derecho
- **TAD Diccionario**: `Dictionary` define *qué* operaciones tiene; `BSTDictionary` define *cómo*
- **Composición**: `BSTDictionary` contiene un `BSTree`, y el árbol contiene nodos con pares
- **Plantillas (templates)**: `Dictionary<K, V>`, `BSTDictionary<K, V>`, `BSTree<E>`, `BSTNode<E>`, `Pair<K, V>`, `List<E>`, `LinkedList<E>` y `Node<E>`
- **Sobrecarga de operadores**: Comparaciones de `Pair` por llave y `operator<<` como función amiga (`friend`)
- **Herencia y polimorfismo**: `update` recibe un `Dictionary*` y `zip` recibe `List*`, por lo que funcionan con cualquier implementación
- **Destructor virtual**: Permite liberar los objetos correctamente a través de un puntero a la clase base
- **Memoria dinámica**: Nodos del árbol y de las listas creados y liberados uno por uno; listas retornadas que libera quien las pide
- **Manejo de excepciones**: `throw runtime_error` y `try/catch`
- **Encapsulamiento**: Atributos privados en `BSTDictionary`, `BSTree`, `LinkedList`

## Requisitos técnicos
- Compilador de C++ con soporte para C++11 o superior
- IDE: Visual Studio, Code::Blocks, CLion o Visual Studio Code, o `g++` por terminal

## Estructura del proyecto

```
Diccionarios/
├── main.cpp           - Programa principal (menú sobre dos diccionarios)
├── Dictionary.h       - Clase abstracta del diccionario
├── BSTDictionary.h    - Diccionario implementado con un árbol de búsqueda binaria
├── BSTree.h           - Árbol de búsqueda binaria
├── BSTNode.h          - Nodo del árbol
├── Pair.h             - Par llave-valor
├── List.h             - Clase abstracta de las listas
├── LinkedList.h       - Lista enlazada simple
└── Node.h             - Nodo de lista simple
```

Todos los archivos están en la misma carpeta. Como las clases son plantillas, su código completo está en los `.h`; el único archivo `.cpp` es `main.cpp`.

## Compilación y ejecución

### Por terminal (g++):
```bash
g++ -std=c++11 -o diccionarios main.cpp
./diccionarios
```

### En Visual Studio:
1. Crear un proyecto de aplicación de consola vacío.
2. Agregar `main.cpp` a los archivos de código fuente y los `.h` a los archivos de encabezado.
3. Ejecutar con `Ctrl + F5`.

## Ejemplo de ejecución

Uso de los dos diccionarios (el 1 con los pares `(5, cinco)`, `(2, dos)` y `(8, ocho)`, y el 2 con `(2, two)` y `(9, nine)`, ya insertados con la opción `insert`):

```
Dictionary 1: []
Dictionary 2: []

1. insert
2. remove
3. getValue
4. setValue
5. contains
6. clear
7. getKeys
8. getValues
9. update
10. zip
0. Exit
Operation: 1
Dictionary (1 or 2): 1
Key: 5
Value: cinco
Pair inserted.

...

Dictionary 1: [(2, dos), (5, cinco), (8, ocho)]
Dictionary 2: [(2, two), (9, nine)]

...
Operation: 1
Dictionary (1 or 2): 1
Key: 5
Value: otro
Error, the operation cannot be performed: Error, Duplicated element.

Dictionary 1: [(2, dos), (5, cinco), (8, ocho)]
Dictionary 2: [(2, two), (9, nine)]

...
Operation: 9
Dictionary (1 or 2): 1
Dictionary updated with the contents of the other one.

Dictionary 1: [(2, two), (5, cinco), (8, ocho), (9, nine)]
Dictionary 2: [(2, two), (9, nine)]

...
Operation: 7
Dictionary (1 or 2): 1
Keys: [2, 5, 8, 9]

Dictionary 1: [(2, two), (5, cinco), (8, ocho), (9, nine)]
Dictionary 2: [(2, two), (9, nine)]

...
Operation: 10
Dictionary (1 or 2): 2
Number of elements: 3
Key: 1
Key: 9
Key: 4
Value: uno
Value: nueve
Value: cuatro
Zip done.

Dictionary 1: [(2, two), (5, cinco), (8, ocho), (9, nine)]
Dictionary 2: [(1, uno), (2, two), (4, cuatro), (9, nueve)]

...
Operation: 2
Dictionary (1 or 2): 1
Key: 7
Error, the operation cannot be performed: Error, element not found.

...
Operation: 0
```

Ejemplos de mensajes de error:

```
Error, invalid input, try again:
Error, invalid option.
Error, invalid dictionary.
Error, the operation cannot be performed: Error, Duplicated element.
Error, the operation cannot be performed: Error, element not found.
```

---

# DIAGRAMAS

## Jerarquía de clases

```
┌─────────────────────────────┐              ┌──────────────────────┐
│ Dictionary<K, V>            │              │ List<E>              │
│ <<abstract>>                │              │ <<abstract>>         │
└──────────────┬──────────────┘              └──────────┬───────────┘
               │                                        │
     ┌─────────▼──────────┐                   ┌─────────▼────────┐
     │ BSTDictionary<K,V> │                   │ LinkedList<E>    │
     └─────────┬──────────┘                   └─────────┬────────┘
               │ usa                                    │ usa
     ┌─────────▼──────────┐                   ┌─────────▼────────┐
     │ BSTree<E>          │                   │ Node<E>          │
     └─────────┬──────────┘                   └──────────────────┘
               │ usa
     ┌─────────▼──────────┐
     │ BSTNode<E>         │
     └────────────────────┘

Pair<K, V> es el elemento que guarda el árbol dentro de BSTDictionary
```

## Asociaciones

```
main (1) ──── dictionary1, dictionary2 (2) ──── BSTDictionary<int, string>*

BSTDictionary<K, V> (1) ──── pairs (1) ──── BSTree<Pair<K, V>>*
BSTree<E> (1) ──── root ──── BSTNode<E>        (0..* nodos en total)
BSTNode<E> (1) ──── left, right ──── BSTNode<E>   (0..1 cada uno)
BSTNode<E> (1) ──── element (1) ──── E          (aquí, un Pair<K, V>)

BSTree<E> ──── crea ──── LinkedList<E>          (en getElements)
BSTDictionary<K, V> ──── crea ──── LinkedList<K> y LinkedList<V>   (en getKeys y getValues)
LinkedList<E> (1) ──── head, current, tail ──── Node<E>
```

---

# DIAGRAMA DE CLASES COMPLETO

```
╔════════════════════════════════════════════════════════╗
║ <<abstract>> DICTIONARY<K, V>                          ║
╠════════════════════════════════════════════════════════╣
║ Constructores:                                         ║
║ + Dictionary()                                         ║
║ + Dictionary(const Dictionary<K, V>&) = delete         ║
║ + ~Dictionary() (virtual)                              ║
╠════════════════════════════════════════════════════════╣
║ Operadores:                                            ║
║ + operator=(const Dictionary<K, V>&) = delete          ║
╠════════════════════════════════════════════════════════╣
║ Métodos (virtuales puros):                             ║
║ + insert(key: K, value: V): void                       ║
║ + remove(key: K): V                                    ║
║ + getValue(key: K): V                                  ║
║ + setValue(key: K, value: V): void                     ║
║ + contains(key: K): bool                               ║
║ + clear(): void                                        ║
║ + isEmpty(): bool                                      ║
║ + getKeys(): List<K>*                                  ║
║ + getValues(): List<V>*                                ║
║ + getSize(): int                                       ║
║ + print(): void                                        ║
║ + update(D: Dictionary<K, V>*): void                   ║
║ + zip(keys: List<K>*, values: List<V>*): void          ║
╚════════════════════════════════════════════════════════╝

╔════════════════════════════════════════════════════════╗
║ BSTDICTIONARY<K, V>    (extends Dictionary<K, V>)      ║
╠════════════════════════════════════════════════════════╣
║ Atributos:                                             ║
║ - pairs: BSTree<Pair<K, V>>*                           ║
╠════════════════════════════════════════════════════════╣
║ Constructores:                                         ║
║ + BSTDictionary()                                      ║
║ + ~BSTDictionary()                                     ║
╠════════════════════════════════════════════════════════╣
║ Métodos:                                               ║
║ + (implementa todos los métodos de Dictionary)         ║
╚════════════════════════════════════════════════════════╝

╔════════════════════════════════════════════════════════╗
║ BSTREE<E>                                              ║
╠════════════════════════════════════════════════════════╣
║ Atributos:                                             ║
║ - root: BSTNode<E>*                                    ║
╠════════════════════════════════════════════════════════╣
║ Constructores:                                         ║
║ + BSTree()                                             ║
║ + ~BSTree()                                            ║
╠════════════════════════════════════════════════════════╣
║ Métodos privados:                                      ║
║ - insertAux(current: BSTNode<E>*, element: E):         ║
║   BSTNode<E>*                                          ║
║ - findNode(current: BSTNode<E>*, element: E):          ║
║   BSTNode<E>*                                          ║
║ - removeAux(current: BSTNode<E>*, element: E,          ║
║   result: E&): BSTNode<E>*                             ║
║ - findMin(current: BSTNode<E>*): BSTNode<E>*           ║
║ - swap(n1: BSTNode<E>*, n2: BSTNode<E>*): void         ║
║ - clearAux(current: BSTNode<E>*): void                 ║
║ - getElementsAux(current: BSTNode<E>*,                 ║
║   elements: List<E>*): void                            ║
║ - getSizeAux(current: BSTNode<E>*): int                ║
╠════════════════════════════════════════════════════════╣
║ Métodos públicos:                                      ║
║ + insert(element: E): void                             ║
║ + contains(element: E): bool                           ║
║ + find(element: E): E                                  ║
║ + remove(element: E): E                                ║
║ + clear(): void                                        ║
║ + getElements(): List<E>*                              ║
║ + isEmpty(): bool                                      ║
║ + getSize(): int                                       ║
║ + print(): void                                        ║
╚════════════════════════════════════════════════════════╝

╔════════════════════════════════════════════════════════╗
║ BSTNODE<E>                                             ║
╠════════════════════════════════════════════════════════╣
║ Atributos:                                             ║
║ + element: E                                           ║
║ + left: BSTNode<E>*                                    ║
║ + right: BSTNode<E>*                                   ║
╠════════════════════════════════════════════════════════╣
║ Constructores:                                         ║
║ + BSTNode(element: E, left: BSTNode<E>*,               ║
║   right: BSTNode<E>*)                                  ║
║ + BSTNode(element: E)                                  ║
╠════════════════════════════════════════════════════════╣
║ Métodos:                                               ║
║ + childrenCount(): int                                 ║
║ + getOnlyChild(): BSTNode<E>*                          ║
╚════════════════════════════════════════════════════════╝

╔════════════════════════════════════════════════════════╗
║ PAIR<K, V>                                             ║
╠════════════════════════════════════════════════════════╣
║ Atributos:                                             ║
║ + key: K                                               ║
║ + value: V                                             ║
╠════════════════════════════════════════════════════════╣
║ Constructores:                                         ║
║ + Pair(key: K, value: V)                               ║
║ + Pair(key: K)                                         ║
║ + Pair()                                               ║
╠════════════════════════════════════════════════════════╣
║ Operadores (comparan solo la llave):                   ║
║ + operator==(other: const Pair<K, V>&): bool           ║
║ + operator<, <=, >, >=, != (misma firma)               ║
║ + friend operator<<(os: ostream&,                      ║
║   pair: const Pair<K, V>&): ostream&                   ║
╚════════════════════════════════════════════════════════╝

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
║ LINKEDLIST<E>                    (extends List<E>)     ║
╠════════════════════════════════════════════════════════╣
║ Atributos:                                             ║
║ - head: Node<E>*  (cabecera)                           ║
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
║ NODE<E>                                                ║
╠════════════════════════════════════════════════════════╣
║ Atributos:                                             ║
║ + element: E                                           ║
║ + next: Node<E>*                                       ║
╠════════════════════════════════════════════════════════╣
║ Constructores:                                         ║
║ + Node(element: E, next: Node<E>* = nullptr)           ║
║ + Node(next: Node<E>* = nullptr)  (cabecera)           ║
╚════════════════════════════════════════════════════════╝

╔════════════════════════════════════════════════════════╗
║ MAIN (programa principal)                              ║
╠════════════════════════════════════════════════════════╣
║ Variables locales principales:                         ║
║ dictionary1: BSTDictionary<int, string>*               ║
║ dictionary2: BSTDictionary<int, string>*               ║
║ op: int                                                ║
╠════════════════════════════════════════════════════════╣
║ Funciones:                                             ║
║ readInt(): int                                         ║
║ showDictionaries(d1: BSTDictionary<int, string>*,      ║
║   d2: BSTDictionary<int, string>*): void               ║
║ showMenu(): void                                       ║
║ execute(op: int, d: BSTDictionary<int, string>*,       ║
║   other: BSTDictionary<int, string>*): void            ║
║ main(): int                                            ║
╚════════════════════════════════════════════════════════╝
```

## Asociaciones y multiplicidades

```
main ────────────────────────────── BSTDictionary<int, string>
1                                   2

BSTDictionary ───────────────────── BSTree<Pair<K, V>>
1                                   1
(Composición: el diccionario crea y destruye su árbol)

BSTree ──────────────────────────── BSTNode
1                                   0..*

BSTNode ─────────────────────────── BSTNode
1                                   0..2  (hijos izquierdo y derecho)

BSTNode ─────────────────────────── Pair
1                                   1     (el elemento que guarda)

Dictionary<K, V> ────────────────── BSTDictionary<K, V>
(herencia: BSTDictionary implementa Dictionary)

LinkedList ──────────────────────── Node
1                                   0..*  (más el nodo cabecera)
```

---

## Características implementadas

### Polimorfismo
- `update` recibe un `Dictionary<K, V>*` y `zip` recibe `List<K>*` y `List<V>*`, por lo que solo dependen de las interfaces y no de las implementaciones
- `BSTDictionary` usa `getKeys()` y `getValue()` del otro diccionario sin saber cómo está implementado

### Árbol sin duplicados
- La comparación se hace con los operadores del elemento; con `Pair`, solo cuenta la llave, así que el árbol nunca tiene dos pares con la misma llave
- Si falla una inserción o una eliminación, el árbol queda como estaba

### Búsqueda con un par sin valor
- Para buscar, eliminar o consultar una llave, el diccionario crea un `Pair` con solo la llave; como la comparación ignora el valor, el árbol encuentra el par completo y lo retorna

### Memoria dinámica
- `BSTDictionary` libera su árbol en el destructor, y el árbol libera todos sus nodos con `clear()`
- Las listas que retornan `getKeys()`, `getValues()` y `getElements()` se crean con `new`; `BSTDictionary` y `main` las liberan con `delete`
- `main` libera los dos diccionarios al salir

### Validación y manejo de errores
- Lectura segura de enteros (`cin.fail()`, `cin.clear()` y `cin.ignore()`)
- Los errores del árbol se capturan con `try/catch` y se muestran sin terminar el programa

### Salida por consola
- Antes de cada operación se muestran los dos diccionarios con sus pares en orden, en la forma `[(llave, valor), ...]`

## Notas importantes
- Los mensajes del programa están en inglés.
- Los valores de texto se leen con `cin >> v`, por lo que **no pueden tener espacios** (una palabra por valor).
- `getSize()` recorre todo el árbol: el atributo `size` del árbol está comentado en el código.
- El árbol **no se balancea**: si las llaves se insertan en orden creciente o decreciente, queda como una lista y las operaciones son O(n); además, como los métodos son recursivos, un árbol muy desbalanceado y muy grande podría agotar la pila.
- `setValue` no modifica el par en su lugar: elimina el par y lo inserta de nuevo con el nuevo valor.
- El mensaje de `getValue` para una llave inexistente (`Error, element not found`) no lleva punto final, a diferencia del de `remove`.
- `Pair(key)` solo inicializa la llave; es el constructor que se usa para buscar, y su valor no se utiliza.
- `update` y `zip` no dejan el diccionario a medias: las llaves existentes se actualizan y las nuevas se insertan, por lo que nunca hay errores de llave repetida.
- `BSTDictionary` no define constructor de copia; como `Dictionary` los tiene eliminados, los diccionarios no se pueden copiar.
- Los datos no se guardan en disco: al cerrar el programa se pierde el contenido de los diccionarios.
- Se siguieron las convenciones de nomenclatura de C++ y se incluyó el encabezado con los datos del autor en todos los archivos.

## Autor
Owel Jafet Gutiérrez Ortiz

## Carnet
2026800869

## Profesor
Mauricio Avilés Cisneros

## Fecha de entrega
19/11/2026

## Institución
Instituto Tecnológico de Costa Rica
Escuela de Computación
Bachillerato en Ingeniería en Computación
