# Tarea Corta 7 - Matrices

## Descripción
Esta tarea consiste en la implementación de una clase plantilla **`Matrix`** en C++ que representa una **matriz bidimensional** de elementos de cualquier tipo, construida con **memoria dinámica** (un arreglo de arreglos). La matriz puede cambiar de tamaño: se pueden agregar y eliminar filas y columnas, y también transponerla. El programa principal es un menú de consola que trabaja con una única matriz de enteros y permite probar todas las operaciones. El programa permite:
- Indicar las dimensiones iniciales de la matriz (filas y columnas)
- Llenar la matriz inicialmente con números aleatorios entre 0 y 99
- Consultar un valor (`getValue`) y asignar un valor (`setValue`) en una posición
- Consultar la cantidad de filas y de columnas
- Asignar un mismo valor a todas las celdas (`setAll`)
- Transponer la matriz (`transpose`)
- Agregar una fila o una columna al final con un valor inicial (`addRow` y `addColumn`)
- Eliminar una fila o una columna (`removeRow` y `removeColumn`)
- Volver a llenar la matriz con números aleatorios
- Ver la matriz y sus dimensiones antes de cada operación
- Validar las entradas del usuario e informar los errores sin que el programa se cierre inesperadamente

> Los mensajes que muestra el programa están en español (sin tildes).

## Requisitos del problema

### Matrix (clase plantilla)
- Guarda la cantidad de filas (`rows`), la cantidad de columnas (`columns`) y los elementos en un arreglo de arreglos (`E** matrix`)
- Cada fila es un arreglo dinámico independiente, y `matrix` es el arreglo de punteros a las filas
- **Constructor**: `Matrix(rows, columns)` reserva la memoria; ambas dimensiones deben ser mayores que cero
- **Consultar**: `getValue(row, column)`, `getRows()` y `getColumns()`
- **Modificar**: `setValue(row, column, value)` y `setAll(value)`
- **Transformar**: `transpose()`, que intercambia filas por columnas
- **Agregar**: `addRow(value)` y `addColumn(value)`, siempre al final y con un valor inicial para la nueva fila o columna
- **Eliminar**: `removeRow(row)` y `removeColumn(column)`
- **print()**: Muestra la matriz en pantalla, una fila por línea
- El destructor libera todas las filas y el arreglo de punteros
- Las posiciones empiezan en **0**
- Los elementos deben tener constructor por defecto, asignación y poder imprimirse con `<<`

### main (programa principal)
- Contiene las funciones `pedirEntero(mensaje)` y `llenarAleatorio(m)`, y el menú con las operaciones
- Crea **un único objeto** `Matrix<int>` en memoria dinámica, y lo libera con `delete` al salir
- Captura con `try/catch` los errores de la matriz, informa que la operación no se pudo realizar y continúa

## Opciones del menú

| Opción | Operación | Descripción |
|--------|-----------|-------------|
| 1 | `getValue` | Muestra el valor de una fila y una columna |
| 2 | `setValue` | Asigna un nuevo valor en una fila y una columna |
| 3 | `getRows` | Muestra la cantidad de filas |
| 4 | `getColumns` | Muestra la cantidad de columnas |
| 5 | `setAll` | Asigna un valor a todas las celdas |
| 6 | `transpose` | Transpone la matriz |
| 7 | `addRow` | Agrega una fila al final con un valor inicial |
| 8 | `addColumn` | Agrega una columna al final con un valor inicial |
| 9 | `removeRow` | Elimina la fila indicada |
| 10 | `removeColumn` | Elimina la columna indicada |
| 11 | Llenar con aleatorios | Reemplaza todos los valores por números entre 0 y 99 |
| 0 | Salir | Termina el programa |

## Estructura en memoria

La matriz es un **arreglo de punteros** (`matrix`), y cada puntero apunta a un **arreglo con los elementos de una fila**:

```
Matrix<int> de 2 filas y 3 columnas

 matrix (E**)          filas (E*)
 ┌───────┐            ┌────┬────┬────┐
 │ fila 0│──────────▶ │ 42 │  7 │ 91 │      matrix[0][0], matrix[0][1], matrix[0][2]
 ├───────┤            └────┴────┴────┘
 │ fila 1│──────────▶ │ 15 │ 63 │ 28 │      matrix[1][0], matrix[1][1], matrix[1][2]
 └───────┘            └────┴────┴────┘

 rows = 2      columns = 3
```

## Funcionamiento de las operaciones

El tamaño de la matriz se cambia **creando una estructura nueva** con las dimensiones correctas, copiando los elementos y liberando la anterior:

### transpose
1. Crea una matriz nueva con `columns` filas y `rows` columnas.
2. Copia cada `matrix[i][j]` en `newMatrix[j][i]`.
3. Libera la estructura anterior, actualiza el puntero e intercambia `rows` y `columns`.

### addRow / removeRow
- **addRow**: crea una estructura con una fila más, copia los elementos, llena la última fila con el valor recibido y libera la anterior.
- **removeRow**: crea una estructura con una fila menos, copia todas las filas excepto la eliminada y libera la anterior.

### addColumn / removeColumn
No se repite el código: se reutilizan las operaciones de filas aplicándolas sobre la **matriz transpuesta**.

```
addColumn(0) sobre una matriz de 2x3

  [42  7 91]    transpose    [42 15]    addRow(0)    [42 15]    transpose    [42  7 91  0]
  [15 63 28]  ─────────────▶ [ 7 63]  ───────────▶  [ 7 63]  ─────────────▶ [15 63 28  0]
                             [91 28]                [91 28]
                                                    [ 0  0]

removeColumn(c): transpose → removeRow(c) → transpose
```

## Complejidad de las operaciones

Con una matriz de `r` filas y `c` columnas:

| Operación | Complejidad |
|-----------|-------------|
| `getValue` / `setValue` | O(1) |
| `getRows` / `getColumns` | O(1) |
| `setAll` | O(r · c) |
| `transpose` | O(r · c) |
| `addRow` / `removeRow` | O(r · c) |
| `addColumn` / `removeColumn` | O(r · c) (dos transposiciones más una operación de filas) |
| `print` | O(r · c) |
| Constructor / destructor | O(r · c) |

`transpose`, `addRow` y `removeRow` necesitan memoria adicional para la estructura nueva (del mismo orden que la matriz) mientras se copian los datos.

## Reglas del negocio
- Las dimensiones de la matriz siempre son **mayores que cero**.
- Las filas y las columnas se numeran desde **0**.
- `addRow` y `addColumn` agregan **al final**, y todas las celdas nuevas reciben el valor indicado.
- `removeRow` y `removeColumn` **no permiten eliminar la única fila ni la única columna**, para que la matriz nunca quede vacía.
- `transpose` convierte una matriz de `r x c` en una de `c x r`.
- Al iniciar, la matriz se llena con números aleatorios entre 0 y 99 (en el código hay una línea comentada, `setAll(0)`, para iniciarla en cero).
- Las operaciones que fallan no modifican la matriz.
- El programa usa un único objeto `Matrix<int>` durante toda la ejecución; sus dimensiones cambian con las operaciones.

## Reglas de validación
- Las dimensiones iniciales deben ser enteros mayores que cero; si no, se muestra el error y se piden de nuevo.
- Todos los datos numéricos se leen con `pedirEntero`: si se escribe algo que no es un número, se muestra el error, se limpia la entrada y se vuelve a pedir.
- Si la opción del menú no está entre 0 y 11 se muestra `Opcion no valida.`
- Los errores de la matriz lanzan `runtime_error`, que se captura en `main`, se muestra después de `Ha ocurrido un error...` y el programa continúa:

| Método | Condición del error | Mensaje |
|--------|---------------------|---------|
| Constructor | `rows <= 0` o `columns <= 0` | `Error, Number of rows and columns must be greater than zero` |
| `getValue`, `setValue`, `removeRow` | Fila fuera de `0` a `rows - 1` | `Error, invalid row.` |
| `getValue`, `setValue`, `removeColumn` | Columna fuera de `0` a `columns - 1` | `Error, invalid column.` |
| `removeRow` | La matriz solo tiene una fila | `Error, cannot remove the only row of the matrix.` |
| `removeColumn` | La matriz solo tiene una columna | `Error, cannot remove the only column of the matrix.` |

## Conceptos implementados

- **Matriz dinámica**: Arreglo de arreglos con `new` y `delete[]`, de tamaño que se decide en tiempo de ejecución
- **Punteros dobles**: `E**` para el arreglo de filas
- **Plantillas (templates)**: `Matrix<E>` funciona con cualquier tipo de elemento
- **Transposición de matrices**: Intercambio de filas por columnas
- **Reutilización de código**: `addColumn` y `removeColumn` se resuelven con `transpose` y las operaciones de filas
- **Constructor y destructor**: El constructor reserva la memoria y el destructor la libera completa
- **Memoria dinámica**: Cada cambio de tamaño crea una estructura nueva y libera la anterior
- **Manejo de excepciones**: `throw runtime_error` en la matriz y `try/catch` en `main`
- **Encapsulamiento**: Atributos privados en `Matrix`

## Requisitos técnicos
- Compilador de C++ con soporte para C++11 o superior
- IDE: Visual Studio, Code::Blocks, CLion o Visual Studio Code, o `g++` por terminal

## Estructura del proyecto

```
Matrices/
├── main.cpp           - Programa principal (menú de operaciones)
└── Matrix.h           - Clase plantilla de la matriz
```

Los dos archivos están en la misma carpeta. Como `Matrix` es una plantilla, su código completo está en el `.h`; el único archivo `.cpp` es `main.cpp`.

## Compilación y ejecución

### Por terminal (g++):
```bash
g++ -std=c++11 -o matrices main.cpp
./matrices
```

### En Visual Studio:
1. Crear un proyecto de aplicación de consola vacío.
2. Agregar `main.cpp` a los archivos de código fuente y `Matrix.h` a los archivos de encabezado.
3. Ejecutar con `Ctrl + F5`.

## Ejemplo de ejecución

Matriz de 2 filas y 3 columnas (los números son aleatorios, por lo que cambian en cada ejecución; el programa separa las columnas con tabuladores):

```
Menu Matrices
Ingrese la cantidad de fila : 2
Ingrese la cantidad de columnas : 3

----------------------------------------
Estado Actual de la Matriz (2x3):
42      7       91
15      63      28
----------------------------------------
1. getValue (Obtener valor)
2. setValue (Asignar valor)
3. getRows (Cantidad de filas)
4. getColumns (Cantidad de columnas)
5. setAll (Asignar valor a todas las celdas)
6. transpose (Transponer matriz)
7. addRow (Agregar fila al final)
8. addColumn (Agregar columna al final)
9. removeRow (Eliminar fila)
10. removeColumn (Eliminar columna)
11. Llenar con numeros aleatorios (0-99)
0. Salir
Elija una opcion: 1
Fila: 1
Columna: 2
Valor en [1][2]: 28

----------------------------------------
Estado Actual de la Matriz (2x3):
...
Elija una opcion: 6
Matriz traspuesta exitosamente.

----------------------------------------
Estado Actual de la Matriz (3x2):
42      15
7       63
91      28
----------------------------------------
...
Elija una opcion: 10
Indice de columna a eliminar: 1
Columna eliminada.

----------------------------------------
Estado Actual de la Matriz (3x1):
42
7
91
----------------------------------------
...
Elija una opcion: 10
Indice de columna a eliminar: 0

Ha ocurrido un error...Error, cannot remove the only column of the matrix.
```

Ejemplos de mensajes de error:

```
Error, Entrada invalida. Intente de nuevo:
Error: Las dimensiones deben ser mayores a cero.
Opcion no valida.
Ha ocurrido un error...Error, invalid row.
Ha ocurrido un error...Error, invalid column.
Ha ocurrido un error...Error, cannot remove the only row of the matrix.
```

---

# DIAGRAMAS

## Jerarquía de clases

```
┌──────────────────────┐
│ Matrix<E>            │
│ clase plantilla      │
└──────────────────────┘
```

`Matrix` no hereda de otra clase ni tiene clases derivadas; `main` la usa con `E = int`.

## Asociaciones

```
main (1) ──── matrix (1) ──── Matrix<int>*
        main crea la matriz con new y la libera con delete al salir

Matrix<E> (1) ──── matrix (rows) ──── E*      (una por fila)
E* (1) ──── elementos (columns) ──── E
```

---

# DIAGRAMA DE CLASES COMPLETO

```
╔════════════════════════════════════════════════════════╗
║ MATRIX<E>                                              ║
╠════════════════════════════════════════════════════════╣
║ Atributos:                                             ║
║ - rows: int                                            ║
║ - columns: int                                         ║
║ - matrix: E**                                          ║
╠════════════════════════════════════════════════════════╣
║ Constructores:                                         ║
║ + Matrix(rows: int, columns: int)                      ║
║ + ~Matrix()                                            ║
╠════════════════════════════════════════════════════════╣
║ Métodos:                                               ║
║ + getValue(row: int, column: int): E                   ║
║ + setValue(row: int, column: int, value: E): void      ║
║ + getRows(): int                                       ║
║ + getColumns(): int                                    ║
║ + setAll(value: E): void                               ║
║ + transpose(): void                                    ║
║ + addRow(value: E): void                               ║
║ + addColumn(value: E): void                            ║
║ + removeRow(row: int): void                            ║
║ + removeColumn(column: int): void                      ║
║ + print(): void                                        ║
╚════════════════════════════════════════════════════════╝

╔════════════════════════════════════════════════════════╗
║ MAIN (programa principal)                              ║
╠════════════════════════════════════════════════════════╣
║ Variables locales principales:                         ║
║ matrix: Matrix<int>*                                   ║
║ r: int                                                 ║
║ c: int                                                 ║
║ opcion: int                                            ║
╠════════════════════════════════════════════════════════╣
║ Funciones:                                             ║
║ pedirEntero(mensaje: const char*): int                 ║
║ llenarAleatorio(m: Matrix<int>&): void                 ║
║ main(): int                                            ║
╚════════════════════════════════════════════════════════╝
```

## Asociaciones y multiplicidades

```
main ────────────────────────────── Matrix<int>
1                                   1
(main crea la matriz y la libera con delete)

Matrix ──────────────────────────── E* (fila)
1                                   rows

E* (fila) ───────────────────────── E (elemento)
1                                   columns
```

---

## Características implementadas

### Matriz que cambia de tamaño
- Las operaciones que cambian las dimensiones crean una estructura nueva, copian los datos y liberan la anterior, de modo que la matriz siempre tiene exactamente `rows x columns` celdas
- Las operaciones que validan antes de modificar (`removeRow`, `removeColumn`) dejan la matriz intacta si lanzan un error

### Reutilización mediante la transpuesta
- `addColumn` y `removeColumn` no tienen su propio código de copia: transponen, aplican la operación de filas y vuelven a transponer

### Memoria dinámica
- El destructor libera cada fila y después el arreglo de punteros
- `main` libera la matriz con `delete` al elegir la opción de salir

### Validación y manejo de errores
- Lectura segura de enteros (`cin.clear()` y `cin.ignore()`)
- Los errores de la matriz se capturan con `try/catch` y se muestran sin terminar el programa

### Salida por consola
- Antes de cada operación se muestra el estado de la matriz con sus dimensiones (`filas x columnas`), una fila por línea

## Notas importantes
- Los mensajes del programa están en español y sin tildes; los mensajes de error de `Matrix` están en inglés.
- El constructor de `Matrix` reserva la memoria pero **no inicializa** los valores (en `int` quedan con basura); por eso `main` llena la matriz con aleatorios al crearla.
- Cada `addRow`, `removeRow` y `transpose` copia toda la matriz, y `addColumn` y `removeColumn` la copian tres veces; para matrices muy grandes o muchas operaciones seguidas es más lento que otras estructuras, pero el código es más simple.
- `Matrix` no define constructor de copia ni operador de asignación: copiar una matriz copiaría solo los punteros y se liberaría dos veces la misma memoria. En el programa solo existe un objeto, manejado con puntero.
- Si se piden dimensiones tan grandes que no hay memoria suficiente, `new` lanza `std::bad_alloc`, que no es un `runtime_error` y no se captura en `main`.
- `print()` separa las columnas con tabuladores, por lo que números muy largos pueden desalinear las columnas.
- Si se escribe algo como `12abc`, `pedirEntero` lee el `12` y deja `abc` en el buffer; el siguiente dato pedido muestra el error de entrada inválida y se vuelve a pedir.
- Los datos no se guardan en disco: al cerrar el programa se pierde la matriz.
- Se siguieron las convenciones de nomenclatura de C++ y se incluyó el encabezado con los datos del autor en todos los archivos.

## Autor
Owel Jafet Gutiérrez Ortiz

## Carnet
2026800869

## Profesor
Mauricio Avilés Cisneros

## Fecha de entrega
10/11/2026

## Institución
Instituto Tecnológico de Costa Rica
Escuela de Computación
Bachillerato en Ingeniería en Computación
