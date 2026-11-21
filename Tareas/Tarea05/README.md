# Tarea Corta 5 - Radix Sort

## Descripción
Esta tarea consiste en la implementación del algoritmo de ordenamiento **Radix Sort** en C++ sobre una **lista enlazada simple** genérica (`LinkedList`), usando una **base numérica que se recibe como parámetro**. El programa genera una lista de enteros aleatorios, la ordena distribuyendo los números en **baldes** (`LinkedList`, uno por cada dígito posible de la base) y mide el tiempo que tarda, para poder comparar el rendimiento con distintas bases. El programa permite:
- Indicar el **tamaño de la lista** a generar
- Indicar la **base numérica** que usará el Radix Sort (mínimo 2)
- Llenar la lista con números enteros aleatorios entre 0 y 999999
- Ordenar la lista con `radixSort(lista, base)`
- Ver la lista ordenada y el **tiempo de ejecución** en milisegundos
- Repetir el proceso las veces que se desee, con otro tamaño y otra base
- Validar las entradas del usuario sin que el programa se cierre inesperadamente

> Los mensajes que muestra el programa están en español (sin tildes).

## Requisitos del problema

### List (clase abstracta genérica)
- Define la interfaz común de las listas mediante métodos virtuales puros
- La lista mantiene una **posición actual** (cursor) con la que se navega y se opera
- **Modificar**: `insert(element)` (en la posición actual), `append(element)` (al final), `setElement(element)`, `remove()` y `clear()`
- **Consultar**: `getElement()`, `getPos()`, `getSize()`, `atStart()` y `atEnd()`
- **Navegar**: `goToStart()`, `goToEnd()`, `goToPos(pos)`, `next()` y `previous()`
- **print()**: Muestra la lista en pantalla
- Constructor de copia y operador de asignación eliminados; destructor virtual

### LinkedList
- Implementación con una **lista enlazada simple** y un **nodo centinela** al inicio (`head`)
- Mantiene un puntero al último nodo (`tail`), por lo que `append` es inmediato
- El puntero `current` apunta al nodo **anterior** al elemento actual; el elemento actual es `current->next`
- `previous()` debe recorrer la lista desde `head`, porque los nodos no conocen a su anterior
- En esta tarea se usa para guardar los números a ordenar y para construir cada balde del Radix Sort

### Node
- `Node<E>`: nodo de lista simple (`element` y `next`), con un segundo constructor sin elemento para el centinela

### main (programa principal)
- Contiene las funciones `numeroAleatorio()`, `leerEntero(mensaje, minimo)`, `getMax(lista)` y `radixSort(lista, base)`
- Pide el tamaño y la base, genera la lista, la ordena, muestra el resultado y el tiempo, y pregunta si se desea repetir

## Funcionamiento del Radix Sort

El Radix Sort ordena los números **dígito por dígito**, empezando por el menos significativo (el de las unidades) y terminando por el más significativo. En cada pasada hay dos etapas:

1. **Distribución**: se saca cada número de la lista (siempre desde el inicio) y se agrega al **final** del balde que corresponde a su dígito actual.
2. **Recolección**: se recorren los baldes en orden, del 0 al `base - 1`, y se vuelven a agregar sus números al final de la lista original.

Como siempre se saca del inicio y se agrega al final, el ordenamiento es **estable**: los números con el mismo dígito conservan el orden que traían de la pasada anterior. Por eso, al terminar la pasada del dígito más significativo, la lista queda completamente ordenada.

### Pasos de `radixSort(lista, base)`
1. Si la lista está vacía o la base es menor que 2, no hace nada.
2. Crea un arreglo dinámico con `base` baldes (`LinkedList<int>`).
3. Busca el valor máximo con `getMax(lista)` para saber cuántas pasadas hacer.
4. Con `peso = 1` (luego `base`, `base^2`, ...) repite mientras `maxVal / peso > 0`:
   - Distribuye cada número `val` en `buckets[(val / peso) % base]`
   - Recolecta los baldes en orden hacia la lista
   - Multiplica `peso` por `base`
5. Libera el arreglo de baldes con `delete[]`.

### Ejemplo (base 10)

Lista inicial: `[170, 45, 75, 90, 802, 24, 2, 66]` (el máximo es 802, por lo que se necesitan 3 pasadas)

```
Pasada 1 (unidades)
  balde 0: [170, 90]
  balde 2: [802, 2]
  balde 4: [24]
  balde 5: [45, 75]
  balde 6: [66]
  recolección → [170, 90, 802, 2, 24, 45, 75, 66]

Pasada 2 (decenas)
  balde 0: [802, 2]
  balde 2: [24]
  balde 4: [45]
  balde 6: [66]
  balde 7: [170, 75]
  balde 9: [90]
  recolección → [802, 2, 24, 45, 66, 170, 75, 90]

Pasada 3 (centenas)
  balde 0: [2, 24, 45, 66, 75, 90]
  balde 1: [170]
  balde 8: [802]
  recolección → [2, 24, 45, 66, 75, 90, 170, 802]
```

### Función `getMax`
- Recorre la lista sacando cada elemento del inicio y volviéndolo a agregar al final; después de `n` repeticiones la lista queda en el mismo orden que antes
- Parte de `maxVal = 0`, por lo que solo funciona con números mayores o iguales a 0

## Número de pasadas según la base

La cantidad de pasadas es la cantidad de dígitos que tiene el número más grande al escribirlo en esa base. Con números de hasta 999999, en el peor caso:

| Base | Pasadas | Baldes |
|------|---------|--------|
| 2 | 20 | 2 |
| 10 | 6 | 10 |
| 16 | 5 | 16 |
| 100 | 3 | 100 |
| 256 | 3 | 256 |
| 1000 | 2 | 1000 |
| 1024 | 2 | 1024 |
| 1000000 | 1 | 1000000 |

Una base pequeña implica **muchas pasadas con pocos baldes**; una base grande implica **pocas pasadas con muchos baldes** (más memoria y más baldes que recorrer en cada recolección). Por eso el rendimiento depende de la base escogida y del tamaño de la lista.

## Complejidad

### Radix Sort
Con `n` números, base `b` y `d` dígitos en el número más grande (`d = ⌊log_b(max)⌋ + 1`):

| Aspecto | Complejidad |
|---------|-------------|
| Tiempo | O(d · (n + b)) |
| Espacio adicional | O(n + b) (los números se mueven a los baldes, más los `b` baldes con su nodo centinela) |
| `getMax` | O(n) |

### Operaciones de LinkedList usadas

| Operación | LinkedList |
|-----------|------------|
| `append` | O(1) |
| `goToStart` | O(1) |
| `remove` (en la posición actual) | O(1) |
| `getSize` | O(1) |
| `print` | O(n) |
| `clear` | O(n) |

Como el programa siempre agrega al final y saca desde el inicio, todas las operaciones del algoritmo son O(1) por elemento.

## Reglas del negocio
- Los números se generan al azar entre **0 y 999999** (se combinan dos `rand()` porque en algunos compiladores `rand()` solo llega a 32767).
- La base se recibe como parámetro, por lo que la función no depende de una base fija.
- Solo se ordenan números **mayores o iguales a 0**.
- La lista se ordena **de menor a mayor**.
- El tiempo se mide con `clock()` justo antes y después de llamar a `radixSort`, por lo que **no incluye** la generación de los números ni la impresión; sí incluye la búsqueda del máximo.
- El tiempo se muestra en **milisegundos**.

## Reglas de validación
- El tamaño de la lista debe ser un entero **mayor o igual a 1**.
- La base debe ser un entero **mayor o igual a 2**.
- Si se escribe algo que no es un número o un número fuera de rango, se muestra el error, se limpia la entrada y se vuelve a pedir el dato.
- `radixSort` no hace nada si la lista está vacía o la base es menor que 2.
- Al final se pregunta si se desea repetir (`s` o `S` para repetir; cualquier otra cosa termina el programa).

## Modelo de posición actual (cursor)

`LinkedList` guarda la posición actual con un puntero al nodo **anterior** al elemento actual:

```
LinkedList (current = nodo ANTERIOR al elemento actual)

 head                                      tail
 ┌──────────┐   ┌───┐   ┌───┐   ┌───┐
 │centinela │──▶│ A │──▶│ B │──▶│ C │──▶ null
 └──────────┘   └───┘   └───┘   └───┘
      pos 0       pos 1   pos 2   pos 3

 pos = 0 (goToStart) →  current = head  →  elemento actual = current->next = A
 pos = 3 (goToEnd)   →  current = tail  →  no hay elemento actual
```

En `radixSort` solo se usa `goToStart()` seguido de `remove()` (sacar el primero) y `append()` (agregar al final), que son las dos operaciones más rápidas de esta lista.

## Conceptos implementados

- **Radix Sort (LSD)**: Ordenamiento no comparativo, dígito por dígito, del menos significativo al más significativo
- **Distribución en baldes**: Un balde por cada dígito posible de la base
- **Estabilidad**: Los elementos con el mismo dígito mantienen su orden relativo
- **Tipo abstracto de datos (TAD)**: `List` define *qué* operaciones tiene una lista; `LinkedList` define *cómo*
- **Plantillas (templates)**: `List<E>`, `LinkedList<E>` y `Node<E>`
- **Herencia y destructor virtual**: `LinkedList` hereda de `List`
- **Memoria dinámica**: Arreglo de baldes con `new[]` y `delete[]`, nodos creados y liberados uno por uno
- **Nodo centinela**: Nodo sin dato al inicio de la lista que evita casos especiales al insertar y eliminar
- **Manejo de excepciones**: `throw runtime_error` en la lista para operaciones inválidas
- **Medición de tiempo**: `clock()` y `CLOCKS_PER_SEC` de `<ctime>`
- **Números aleatorios**: `srand(time(NULL))` y `rand()`

## Requisitos técnicos
- Compilador de C++ con soporte para C++11 o superior
- IDE: Visual Studio, Code::Blocks, CLion o Visual Studio Code, o `g++` por terminal

## Estructura del proyecto

```
RadixSort/
├── main.cpp           - Programa principal (entrada, radixSort y medición de tiempo)
├── List.h             - Clase abstracta de las listas
├── LinkedList.h       - Lista enlazada simple
└── Node.h             - Nodo de lista simple
```

Todos los archivos están en la misma carpeta. Como la lista y el nodo son plantillas, su código completo está en los `.h`; el único archivo `.cpp` es `main.cpp`.

## Compilación y ejecución

### Por terminal (g++):
```bash
g++ -std=c++11 -o radix main.cpp
./radix
```

### En Visual Studio:
1. Crear un proyecto de aplicación de consola vacío.
2. Agregar `main.cpp` a los archivos de código fuente y los `.h` a los archivos de encabezado.
3. Ejecutar con `Ctrl + F5`.

## Ejemplo de ejecución

Ordenamiento de una lista de 10 números con base 10 (los números y el tiempo son ilustrativos: cambian en cada ejecución):

```
Ingrese el tamaño de la lista: 10
Ingrese la base numerica (minimo 2): 10

Lista ordenada:
[4213, 18764, 52310, 93481, 120045, 288901, 347762, 561230, 712358, 984120]

Tiempo: 0.012 ms

Desea repetir? (s/n): s

Ingrese el tamaño de la lista: 10
Ingrese la base numerica (minimo 2): 256

Lista ordenada:
[2750, 31877, 66402, 150339, 221064, 305918, 478120, 590043, 803371, 947688]

Tiempo: 0.021 ms

Desea repetir? (s/n): n
```

Ejemplos de mensajes de error:

```
Error: debe ser un entero mayor o igual a 1
Error: debe ser un entero mayor o igual a 2
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
                     ┌─────────▼────────┐
                     │ LinkedList<E>    │
                     │ lista simple     │
                     └─────────┬────────┘
                               │ usa
                     ┌─────────▼────────┐
                     │ Node<E>          │
                     └──────────────────┘
```

## Asociaciones

```
main (1) ──── lista (1) ──── LinkedList<int>
main (1) ──── buckets (base) ──── LinkedList<int>
        Los baldes se crean dentro de radixSort y se liberan al terminar

LinkedList<E> (1) ──── head, current, tail ──── Node<E>
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
║ Operadores:                                            ║
║ + operator=(const List<E>&) = delete                   ║
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
║ MAIN (programa principal)                              ║
╠════════════════════════════════════════════════════════╣
║ Funciones:                                             ║
║ numeroAleatorio(): int                                 ║
║ leerEntero(mensaje: const char*, minimo: int): int     ║
║ getMax(lista: LinkedList<int>&): int                   ║
║ radixSort(lista: LinkedList<int>&, base: int): void    ║
║ main(): int                                            ║
╚════════════════════════════════════════════════════════╝
```

## Asociaciones y multiplicidades

```
main ────────────────────────────── LinkedList<int>
1                                   1   (la lista con los números)

radixSort ───────────────────────── LinkedList<int>
1                                   base   (un balde por dígito)

LinkedList ──────────────────────── Node
1                                   0..*  (más el nodo centinela)
```

---

## Características implementadas

### Base como parámetro
- `radixSort(lista, base)` funciona con cualquier base mayor o igual a 2: el dígito de cada número se obtiene con `(val / peso) % base`
- Cambiar la base solo cambia la cantidad de baldes y de pasadas, no el código del algoritmo

### Baldes con LinkedList
- Los baldes son un arreglo dinámico de `LinkedList<int>` creado con `new LinkedList<int>[base]`
- Cada balde se vacía por completo en cada recolección, por lo que están listos para la siguiente pasada

### Memoria dinámica
- La lista libera sus nodos en el destructor, y el arreglo de baldes se libera con `delete[]` al final de `radixSort`

### Validación y manejo de entradas
- Lectura segura de enteros con mínimo (`cin.fail()`, `cin.clear()` y `cin.ignore()`)

### Salida por consola
- La lista ordenada se muestra entre corchetes y separada por comas, seguida del tiempo en milisegundos

## Notas importantes
- Los mensajes del programa están en español y sin tildes (excepto "tamaño" en el primer mensaje).
- `radixSort` solo funciona con números **no negativos**; los números generados siempre están entre 0 y 999999.
- Se usa `long long` para `peso`, para evitar desbordamientos al multiplicar por la base.
- Con bases muy grandes se crean muchos baldes (uno por dígito posible), y cada uno tiene su nodo centinela: la memoria y el tiempo de recolección aumentan aunque haya menos pasadas.
- Con listas muy grandes, imprimir la lista ordenada completa puede tardar y llenar la consola; el tiempo que se muestra no incluye la impresión.
- `clock()` mide tiempo de CPU del proceso, por lo que con listas muy pequeñas el tiempo puede salir en 0 ms o variar entre ejecuciones; conviene probar con listas grandes para comparar bases.
- Si se escribe algo como `12abc`, `cin` lee el `12` y deja `abc` en el buffer; esa entrada sobrante provoca un error en la siguiente lectura, que se corrige solo al volver a pedir el dato.
- Los datos no se guardan en disco: al cerrar el programa se pierde la lista.

## Autor
Owel Jafet Gutiérrez Ortiz

## Carnet
2026800869

## Profesor
Mauricio Avilés Cisneros

## Fecha de entrega
22/10/2026

## Institución
Instituto Tecnológico de Costa Rica
Escuela de Computación
Bachillerato en Ingeniería en Computación
