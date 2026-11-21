# Tarea Corta 6 - Heaps

## Descripción
Esta tarea consiste en la implementación de un **heap de mínimos** (`MinHeap`) genérico en C++, guardado en un **arreglo dinámico**, y de tres operaciones adicionales sobre él: **heapify** (construir el heap a partir de un arreglo), **merge** (unir otro heap) y **removeTop** (extraer los `n` elementos menores en una lista). El programa principal es una prueba de todas esas operaciones con números aleatorios. El programa permite:
- Indicar la cantidad de elementos de dos heaps y llenarlos con números aleatorios entre 0 y 99
- Unir el segundo heap al primero con `merge`
- Extraer los `n` menores del heap con `removeTop` y verlos en una lista
- Vaciar el heap con `removeFirst`, que siempre saca el menor
- Probar `heapify` con un arreglo en memoria dinámica de números aleatorios
- Ver el contenido de los heaps y de las listas en cada paso

> Los mensajes que muestra el programa están en español (sin tildes).

## Requisitos del problema

### MinHeap (heap de mínimos genérico)
- Guarda los elementos en un **arreglo dinámico** de capacidad `max` (por defecto `DEFAULT_MAX` = 1024) y lleva la cantidad de elementos en `size`
- Cumple la **condición de heap de mínimos**: cada elemento es menor o igual que sus hijos, por lo que el menor siempre está en la posición 0
- **Insertar**: `insert(element)`
- **Consultar**: `first()` (el menor, sin sacarlo), `getSize()` e `isEmpty()`
- **Eliminar**: `removeFirst()` (saca el menor), `remove(pos)` (saca el elemento de una posición) y `clear()`
- **Operaciones adicionales**: `heapify(arr, n)`, `merge(other)` y `removeTop(n)`
- **print()**: Muestra el arreglo del heap en pantalla, en el orden en que está guardado
- Los elementos deben poder compararse con `<`, tener constructor por defecto e imprimirse con `<<`

### Métodos privados de MinHeap
- `parent(pos)`, `leftChild(pos)` y `rightChild(pos)`: calculan los índices del padre y de los hijos
- `isLeaf(pos)`: indica si la posición es una hoja (no tiene hijo izquierdo)
- `minChild(pos)`: retorna la posición del hijo menor
- `siftUp(pos)`: sube un elemento mientras sea menor que su padre
- `siftDown(pos)`: baja un elemento mientras tenga un hijo menor que él
- `swap(pos1, pos2)`: intercambia dos elementos del arreglo

### heapify(arr, n)
- **Copia** los `n` elementos de `arr` dentro del heap, **reemplazando** su contenido
- Luego recorre las posiciones desde la última hasta la 0 aplicando `siftDown` para que se cumpla la condición de heap
- Como el heap tiene su propia copia, el arreglo original se puede liberar después

### merge(other)
- Agrega todos los elementos de `other` a este heap, insertándolos uno por uno
- `other` **no se modifica**
- Lanza error si se intenta unir un heap consigo mismo o si no hay espacio suficiente

### removeTop(n)
- Saca del heap los `n` elementos de mayor prioridad (los menores) y los retorna en una **lista en memoria dinámica** (`List<E>*`, que en realidad es una `LinkedList`)
- La lista queda ordenada de menor a mayor
- Quien llama es responsable de liberar la lista con `delete`

### List y LinkedList
- `List<E>`: clase abstracta con la interfaz de la lista (insertar, agregar al final, eliminar, consultar, navegar e imprimir)
- `LinkedList<E>`: lista enlazada simple con nodo cabecera (`head`), puntero al último nodo (`tail`) y un puntero `current` al nodo anterior al elemento actual
- En esta tarea solo se usa para guardar lo que retorna `removeTop` (con `append`) y para imprimirlo

### Node y Util
- `Node<E>`: nodo de lista simple (`element` y `next`), con un segundo constructor sin elemento para la cabecera
- `Util.h`: define la constante `DEFAULT_MAX` (1024)

### main (programa principal)
- Crea `heap1` y `heap2` con la capacidad por defecto, los llena, los une, extrae el top, vacía el heap y prueba `heapify`
- Libera la lista del top, el arreglo del `heapify` y la lista final con `delete` / `delete[]`

## El heap en un arreglo

Un heap es un **árbol binario completo** guardado en un arreglo, sin punteros. Para la posición `i`:

| Elemento | Posición |
|----------|----------|
| Padre | `(i - 1) / 2` |
| Hijo izquierdo | `2i + 1` |
| Hijo derecho | `2i + 2` |

```
Heap después del merge del ejemplo:  [3, 7, 28, 83, 15, 60, 42, 91]

 índice:    0   1   2    3    4   5    6   7
          ┌───┬───┬────┬────┬────┬────┬────┬────┐
          │ 3 │ 7 │ 28 │ 83 │ 15 │ 60 │ 42 │ 91 │      size = 8
          └───┴───┴────┴────┴────┴────┴────┴────┘

 Como árbol:

                    3
              ┌─────┴─────┐
              7           28
          ┌───┴───┐    ┌──┴──┐
         83      15   60     42
        ┌─┘
        91
```

## Funcionamiento de las operaciones

### insert
1. Se coloca el elemento al final del arreglo (posición `size`).
2. `siftUp`: mientras sea menor que su padre, se intercambian y se sube.
3. Se incrementa `size`.

### removeFirst / remove(pos)
1. Se intercambia el elemento de la posición `pos` con el último del arreglo.
2. Se reduce `size`.
3. `siftDown` desde `pos`: el elemento que llegó se baja intercambiándolo con su hijo menor mientras ese hijo sea menor que él.
4. Se retorna el elemento que se sacó, que quedó en `elements[size]`.

`removeFirst()` es `remove(0)`.

### heapify
1. Se copian los `n` elementos del arreglo al heap y `size = n`.
2. Se aplica `siftDown` desde la última posición hasta la 0. Las hojas no se mueven, así que en la práctica el trabajo se hace en los nodos internos.

Ejemplo con `[50, 20, 80, 10, 35]`:

```
Inicial:         [50, 20, 80, 10, 35]
siftDown(1):     20 baja y 10 sube           → [50, 10, 80, 20, 35]
siftDown(0):     50 baja dos niveles         → [10, 20, 80, 50, 35]
```

### merge
- Recorre el arreglo de `other` y hace `insert` de cada elemento en este heap.
- Antes de empezar verifica que `size + other->size` no supere `max`; por eso el programa limita la cantidad inicial a `DEFAULT_MAX / 2`.

### removeTop
- Crea una `LinkedList` y llama `n` veces a `removeFirst()`, agregando cada resultado al final de la lista.
- Si `n` es el tamaño completo del heap, el resultado es todo el contenido ordenado de menor a mayor (como un *heap sort*).

## Complejidad de las operaciones

Con `n` elementos en el heap, `m` elementos en el heap que se une y `k` elementos extraídos:

| Operación | Complejidad |
|-----------|-------------|
| `insert` | O(log n) |
| `first` | O(1) |
| `removeFirst` | O(log n) |
| `remove(pos)` | O(log n) |
| `clear` | O(1) (borrado lógico: `size = 0`) |
| `isEmpty` / `getSize` | O(1) |
| `print` | O(n) |
| `heapify(arr, n)` | O(n) |
| `merge(other)` | O(m log(n + m)) (un `insert` por elemento) |
| `removeTop(k)` | O(k log n) |

## Reglas del negocio
- Los números del programa de prueba se generan al azar entre **0 y 99** (se pueden repetir).
- El heap es de **mínimos**: la raíz (posición 0) siempre es el menor.
- La capacidad del heap es fija (`DEFAULT_MAX` = 1024) y no se expande; `insert` lanza error si el heap está lleno.
- `merge` no modifica el heap que se une; los elementos se copian al heap actual.
- `heapify` reemplaza el contenido anterior del heap por el del arreglo.
- `removeTop(n)` elimina del heap los elementos que retorna.
- `clear` solo pone `size = 0`; el arreglo no se libera hasta el destructor.

## Reglas de validación
- La cantidad de elementos de cada heap debe estar entre **1 y 512** (`DEFAULT_MAX / 2`), para que `merge` siempre quepa en `heap1`.
- La cantidad `n` del top debe estar entre **1 y la cantidad de elementos de `heap1`** después del merge.
- El tamaño del arreglo para `heapify` debe estar entre **1 y 1024** (`DEFAULT_MAX`).
- Si el valor está fuera de rango, se vuelve a pedir (ciclo `do ... while`).
- Los errores de `MinHeap` lanzan `runtime_error`:

| Método | Condición del error |
|--------|---------------------|
| Constructor | `max < 1` |
| `insert` | El heap está lleno |
| `first` / `removeFirst` | El heap está vacío |
| `remove(pos)` | `pos` fuera de `0` a `size - 1` |
| `heapify` | `n < 0` o `n > max` |
| `merge` | Se une consigo mismo o no hay espacio suficiente |
| `removeTop` | `n < 1` o `n > size` |

## Conceptos implementados

- **Heap (montículo) de mínimos**: Árbol binario completo guardado en un arreglo, con el menor en la raíz
- **Operaciones sift**: `siftUp` y `siftDown` para restaurar la condición de heap
- **Heapify**: Construcción del heap a partir de un arreglo existente
- **Cola de prioridad**: `insert` y `removeFirst` funcionan como una cola donde sale primero el menor
- **Heap sort**: Extraer todos los elementos con `removeFirst` los entrega ordenados
- **Plantillas (templates)**: `MinHeap<E>`, `List<E>`, `LinkedList<E>` y `Node<E>`
- **Herencia y polimorfismo**: `removeTop` retorna un `List<E>*` que apunta a una `LinkedList`
- **Memoria dinámica**: Arreglo del heap con `new[]` y `delete[]`, lista retornada con `new` y `delete`
- **Manejo de excepciones**: `throw runtime_error`
- **Constantes de compilación**: `#define DEFAULT_MAX` y `#pragma once`
- **Encapsulamiento**: Atributos y métodos auxiliares privados en `MinHeap`

## Requisitos técnicos
- Compilador de C++ con soporte para C++11 o superior
- IDE: Visual Studio, Code::Blocks, CLion o Visual Studio Code, o `g++` por terminal

## Estructura del proyecto

```
Heaps/
├── main.cpp           - Programa principal (prueba de las operaciones del heap)
├── MinHeap.h          - Heap de mínimos con arreglo
├── List.h             - Clase abstracta de las listas
├── LinkedList.h       - Lista enlazada simple
├── Node.h             - Nodo de lista simple
└── Util.h             - Constantes compartidas (DEFAULT_MAX)
```

Todos los archivos están en la misma carpeta. Como el heap, las listas y el nodo son plantillas, su código completo está en los `.h`; el único archivo `.cpp` es `main.cpp`.

## Compilación y ejecución

### Por terminal (g++):
```bash
g++ -std=c++11 -o heaps main.cpp
./heaps
```

### En Visual Studio:
1. Crear un proyecto de aplicación de consola vacío.
2. Agregar `main.cpp` a los archivos de código fuente y los `.h` a los archivos de encabezado.
3. Ejecutar con `Ctrl + F5`.

## Ejemplo de ejecución

Prueba con 4 elementos por heap (los números son aleatorios, por lo que cambian en cada ejecución):

```
Cantidad de elementos para cada heap (1-512): 4
Heap 1: [7, 15, 42, 83]
Heap 2: [3, 60, 28, 91]
Heap 1 despues del merge: [3, 7, 28, 83, 15, 60, 42, 91]
Cantidad n para el top (1-8): 3
Top 3: [3, 7, 15]
Resto del heap 1: [28, 42, 60, 83, 91]
Cantidad de elementos del arreglo (1-1024): 5
Heap 1 tras heapify: [10, 20, 80, 50, 35]
Contenido de removeTop: [10, 20, 35, 50, 80]
```

Cuando el valor está fuera de rango, el programa vuelve a pedirlo:

```
Cantidad de elementos para cada heap (1-512): 0
Cantidad de elementos para cada heap (1-512): 600
Cantidad de elementos para cada heap (1-512): 4
```

Mensajes de error de `MinHeap` (excepciones `runtime_error`):

```
Error, Heap is full.
Error, heap is empty.
Error, index out of bounds.
Error, n exceeds heap size.
Error, not enough space to merge heaps.
```

---

# DIAGRAMAS

## Jerarquía de clases

```
┌──────────────────────┐              ┌──────────────────────┐
│ MinHeap<E>           │              │ List<E>              │
│ heap de mínimos      │              │ <<abstract>>         │
└──────────┬───────────┘              └──────────┬───────────┘
           │                                     │
           │ removeTop retorna                   │
           │ un List<E>*                ┌────────▼─────────┐
           └──────────────────────────▶ │ LinkedList<E>    │
                                        │ lista simple     │
                                        └────────┬─────────┘
                                                 │ usa
                                        ┌────────▼─────────┐
                                        │ Node<E>          │
                                        └──────────────────┘
```

## Asociaciones

```
main (1) ──── heap1, heap2 (2) ──── MinHeap<int>
main (1) ──── top, todos ──── List<int>*
        Apuntan a una LinkedList creada por removeTop; main las libera con delete

MinHeap<E> (1) ──── elements (max) ──── E     (arreglo dinámico)
MinHeap<E> ──── crea ──── LinkedList<E>       (en removeTop)
LinkedList<E> (1) ──── head, current, tail ──── Node<E>
MinHeap<E> incluye Util.h (DEFAULT_MAX)
```

---

# DIAGRAMA DE CLASES COMPLETO

```
╔════════════════════════════════════════════════════════╗
║ MINHEAP<E>                                             ║
╠════════════════════════════════════════════════════════╣
║ Atributos:                                             ║
║ - elements: E*                                         ║
║ - max: int                                             ║
║ - size: int                                            ║
╠════════════════════════════════════════════════════════╣
║ Constructores:                                         ║
║ + MinHeap(max: int = DEFAULT_MAX)                      ║
║ + ~MinHeap()                                           ║
╠════════════════════════════════════════════════════════╣
║ Métodos privados:                                      ║
║ - parent(pos: int): int                                ║
║ - leftChild(pos: int): int                             ║
║ - rightChild(pos: int): int                            ║
║ - isLeaf(pos: int): bool                               ║
║ - minChild(pos: int): int                              ║
║ - siftUp(pos: int): void                               ║
║ - siftDown(pos: int): void                             ║
║ - swap(pos1: int, pos2: int): void                     ║
╠════════════════════════════════════════════════════════╣
║ Métodos públicos:                                      ║
║ + insert(element: E): void                             ║
║ + first(): E                                           ║
║ + removeFirst(): E                                     ║
║ + remove(pos: int): E                                  ║
║ + clear(): void                                        ║
║ + isEmpty(): bool                                      ║
║ + getSize(): int                                       ║
║ + print(): void                                        ║
║ + heapify(arr: E*, n: int): void                       ║
║ + merge(other: MinHeap<E>*): void                      ║
║ + removeTop(n: int): List<E>*                          ║
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
║ LINKEDLIST<E>                          (extends List<E>)║
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
║ UTIL.H                                                 ║
╠════════════════════════════════════════════════════════╣
║ Constantes:                                            ║
║ #define DEFAULT_MAX 1024                               ║
╚════════════════════════════════════════════════════════╝

╔════════════════════════════════════════════════════════╗
║ MAIN (programa principal)                              ║
╠════════════════════════════════════════════════════════╣
║ Funciones:                                             ║
║ main(): int                                            ║
╠════════════════════════════════════════════════════════╣
║ Variables locales principales:                         ║
║ heap1: MinHeap<int>                                    ║
║ heap2: MinHeap<int>                                    ║
║ top: List<int>*  (resultado de removeTop)              ║
║ arr: int*  (arreglo dinámico para heapify)             ║
╚════════════════════════════════════════════════════════╝
```

## Asociaciones y multiplicidades

```
main ────────────────────────────── MinHeap<int>
1                                   2

MinHeap ─────────────────────────── List<E>
1                                   0..*
(removeTop crea la lista y quien la llama la libera)

List<E> ─────────────────────────── LinkedList<E>
(herencia: LinkedList implementa List)

LinkedList ──────────────────────── Node
1                                   0..*  (más el nodo cabecera)
```

---

## Características implementadas

### Heap de mínimos con arreglo
- No usa punteros entre nodos: padre e hijos se calculan con índices (`(i-1)/2`, `2i+1` y `2i+2`)
- `siftUp` y `siftDown` restablecen la condición de heap después de insertar o eliminar

### Heapify
- Construye el heap a partir de un arreglo copiando sus elementos y aplicando `siftDown`
- El arreglo original no se usa después de la copia, por lo que se puede liberar

### Merge y removeTop
- `merge` verifica el espacio antes de modificar el heap, así que si falla el heap queda como estaba
- `removeTop` retorna un `List<E>*`, por lo que quien lo usa solo depende de la interfaz de la lista

### Memoria dinámica
- `MinHeap` libera su arreglo en el destructor y `LinkedList` libera sus nodos en el suyo
- `main` libera con `delete` las listas que retorna `removeTop` y con `delete[]` el arreglo del `heapify`

### Manejo de errores
- Todos los métodos que pueden fallar validan sus parámetros y lanzan `runtime_error`
- `main` valida los rangos antes de llamar a los métodos, por lo que en una ejecución normal no se lanzan excepciones

## Notas importantes
- Los mensajes del programa están en español y sin tildes.
- El orden en que `print()` muestra el heap es el del arreglo, **no** está ordenado: solo se garantiza que cada padre es menor o igual que sus hijos. Los elementos salen ordenados al extraerlos con `removeFirst` o `removeTop`.
- `remove(pos)` reordena con `siftDown` desde `pos`. En el programa solo se usa con `pos = 0` (mediante `removeFirst`), caso en el que es correcto.
- El programa principal usa `do ... while` para validar rangos, pero no limpia la entrada si se escribe algo que no es un número; solo se validan los rangos.
- `main` no tiene `try/catch`: no hace falta porque valida los rangos antes de llamar a los métodos del heap.
- `heapify` reemplaza el contenido del heap, por lo que lo que tuviera antes se pierde.
- Los números aleatorios pueden repetirse (hay solo 100 valores posibles), y el heap acepta elementos repetidos.
- `MinHeap` no tiene constructor de copia propio; los heaps no se copian en este programa, solo se une uno a otro con `merge`.
- La capacidad es fija (1024) y no se expande.
- Los datos no se guardan en disco: al cerrar el programa se pierde el contenido de los heaps.
- Se siguieron las convenciones de nomenclatura de C++ y se incluyó el encabezado con los datos del autor en todos los archivos.

## Autor
Owel Jafet Gutiérrez Ortiz

## Carnet
2026800869

## Profesor
Mauricio Avilés Cisneros

## Fecha de entrega
06/11/2026

## Institución
Instituto Tecnológico de Costa Rica
Escuela de Computación
Bachillerato en Ingeniería en Computación
