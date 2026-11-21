# Tarea 0 - Ejercicios con arreglos en memoria dinámica

## Descripción
Esta tarea consiste en la implementación de dos ejercicios en C++ que trabajan con arreglos creados en memoria dinámica (`new` y `delete[]`). Ambos programas se ejecutan uno después del otro desde un mismo archivo y se comunican con el usuario por consola. El programa permite:
- **Ejercicio 0**: Generar un arreglo con los números del 1 al N y desordenarlo mediante intercambios aleatorios
- **Ejercicio 1**: Leer un histograma no decreciente, mostrarlo y calcular y mostrar su transpuesta
- Validar todas las entradas del usuario sin que el programa se cierre inesperadamente
- Reservar y liberar la memoria de los arreglos de forma manual

## Requisitos del problema

### Ejercicio 0: Desordenar un arreglo
- Pedir al usuario la **cantidad de números** a generar
- Crear en memoria dinámica un arreglo de ese tamaño y llenarlo con los valores del 1 al N, en orden
- Mostrar el arreglo ordenado
- Desordenar el arreglo y mostrar el resultado
- Liberar la memoria del arreglo

### Ejercicio 1: Transponer un histograma no decreciente
- Pedir al usuario la **cantidad de números** a leer
- Leer los enteros de uno en uno; deben ingresarse en orden no decreciente
- Mostrar el arreglo ingresado y su histograma (una fila de asteriscos por cada número)
- Calcular el arreglo transpuesto en memoria dinámica
- Mostrar el arreglo transpuesto y su histograma
- Liberar la memoria de los arreglos

#### ¿Qué es la transpuesta de un histograma?
Si un histograma tiene filas de `1`, `3` y `4` asteriscos, el **nivel** `k` de la transpuesta cuenta cuántas filas del original llegan al menos a la altura `k`. Es como girar el histograma: las filas pasan a ser columnas.

```
Original (1, 3, 4)       Transpuesta (1, 2, 2, 3)
*                        *
***                      **
****                     **
                         ***
```

## Reglas de validación
- Las cantidades y los números ingresados deben ser **enteros válidos**; si se escribe otra cosa, se avisa y se vuelve a pedir.
- Ejercicio 0: la cantidad de números debe ser **mayor que 2**.
- Ejercicio 1: la cantidad de números debe ser **mayor que 0**.
- Ejercicio 1: cada número debe ser **mayor que 0**.
- Ejercicio 1: cada número debe ser **mayor o igual** al anterior (orden no decreciente).
- Cuando una entrada es inválida, se muestra el error y se repite la pregunta, sin avanzar.

## Algoritmos

### Ejercicio 0: desordenar
1. Se calcula la cantidad de repeticiones como `N / 2`.
2. En cada repetición se eligen dos posiciones aleatorias distintas (`rand() % N`), repitiendo la segunda si coincide con la primera.
3. Se intercambian los valores de ambas posiciones usando una variable temporal.

La semilla se inicializa con `srand(time(nullptr))`, por lo que el resultado cambia en cada ejecución.

### Ejercicio 1: transponer
1. El valor máximo del histograma es el **último elemento** del arreglo, porque está en orden no decreciente.
2. Se crea el arreglo transpuesto con tantas posiciones como el valor máximo.
3. Para cada nivel de `1` hasta el máximo, se cuenta cuántos elementos del original son mayores o iguales a ese nivel.
4. El arreglo transpuesto se muestra de atrás hacia adelante (del nivel más alto al más bajo), por lo que también queda en orden no decreciente.

## Conceptos implementados

- **Memoria dinámica**: Reserva con `new int[n]` y liberación con `delete[]`
- **Punteros**: Los arreglos se manejan mediante punteros (`int*`)
- **Arreglos**: Recorridos con ciclos `for`, acceso por índice
- **Validación de entrada**: Uso de `cin.fail()`, `cin.clear()` y `cin.ignore()` para recuperarse de entradas inválidas
- **Ciclos de validación**: `while (true)` con `continue` y `break`
- **Números pseudoaleatorios**: `srand()`, `time()` y `rand()`
- **Intercambio de valores**: Uso de una variable temporal (swap)
- **Reutilización de variables**: La variable `numero` y el puntero `arreglo` se reutilizan en el segundo ejercicio después de liberar la memoria

## Requisitos técnicos
- Compilador de C++ con soporte para C++11 o superior (se usa `nullptr`)
- IDE: Visual Studio, Code::Blocks, CLion o Visual Studio Code, o un compilador por terminal como `g++`

## Estructura del proyecto

```
Tarea0/
└── Tarea 0.cpp        - Contiene los dos ejercicios
```

## Compilación y ejecución

### Por terminal (g++):
```bash
g++ -std=c++11 -o tarea0 "Tarea 0.cpp"
./tarea0
```

### En Visual Studio:
1. Crear un proyecto de aplicación de consola vacío.
2. Agregar `Tarea 0.cpp` a los archivos de código fuente.
3. Ejecutar con `Ctrl + F5`.

## Ejemplo de ejecución

El resultado del Ejercicio 0 cambia en cada ejecución, porque el desorden es aleatorio.

```
Inicio Ejercicio 0

Programa para desordenar un arreglo.
Indique la cantidad de números a generar: 5
Arreglo Ordenado: 	[ 1, 2, 3, 4, 5]
Arreglo Desordenado: 	[ 4, 5, 3, 1, 2]

Fin Ejercicio 0

Inicio Ejercicio 1

Programa para transponer un histograma no decreciente.
Indique la cantidad de números a leer: 3
Ingrese los enteros, deben estar en orden no decreciente.
Ingrese el número 1: 1
Ingrese el número 2: 3
Ingrese el número 3: 4
[ 1, 3, 4]
*
***
****

[ 1, 2, 2, 3]
*
**
**
***

Fin Ejercicio 1
```

Ejemplos de errores controlados:

```
Indique la cantidad de números a generar: abc
Error, entero no válido.

Indique la cantidad de números a leer: 0
Error, debe ser mayor a 0.

Ingrese el número 2: -4
Error, debe ser mayor a 0.
```

---

# DIAGRAMAS

## Flujo general del programa

```
┌──────────────────────────────┐
│ main()                       │
└──────────────┬───────────────┘
               │
               ▼
┌──────────────────────────────┐
│ EJERCICIO 0                  │
│  1. Leer N (validar, N > 2)  │
│  2. Crear arreglo de N       │
│  3. Llenar con 1..N          │
│  4. Mostrar ordenado         │
│  5. Desordenar (N/2 swaps)   │
│  6. Mostrar desordenado      │
│  7. delete[] arreglo         │
└──────────────┬───────────────┘
               │
               ▼
┌──────────────────────────────┐
│ EJERCICIO 1                  │
│  1. Leer N (validar, N > 0)  │
│  2. Crear arreglo de N       │
│  3. Leer N enteros           │
│     (> 0 y no decrecientes)  │
│  4. Mostrar arreglo e        │
│     histograma               │
│  5. Crear arreglo            │
│     transpuesto (tamaño      │
│     = valor máximo)          │
│  6. Contar por nivel         │
│  7. Mostrar transpuesta e    │
│     histograma               │
│  8. delete[] de los arreglos │
└──────────────────────────────┘
```

## Ciclo de validación de entrada

```
        ┌─────────────────────┐
   ┌───▶│ Pedir el dato (cin) │
   │    └──────────┬──────────┘
   │               ▼
   │      ¿cin.fail()?  ── sí ──▶ mostrar error, cin.clear(),
   │               │               cin.ignore() ──────────────┐
   │              no                                          │
   │               ▼                                          │
   │      ¿cumple la regla? ── no ──▶ mostrar error ──────────┤
   │               │                                          │
   │              sí                                          │
   │               ▼                                          │
   │          break (dato válido)                             │
   │                                                          │
   └──────────────────────────────────────────────────────────┘
```

## Memoria durante el Ejercicio 1

```
STACK                              HEAP
─────                              ────
numero = 3                         ┌───┬───┬───┐
arreglo ─────────────────────────▶ │ 1 │ 3 │ 4 │          (3 enteros)
                                   └───┴───┴───┘
numeroMaximo = 4                   ┌───┬───┬───┬───┐
arregloTranspuesto ──────────────▶ │ 3 │ 2 │ 2 │ 1 │      (4 enteros)
                                   └───┴───┴───┴───┘
                                     ▲               nivel 1, 2, 3, 4
                                     └─ conteo de filas con altura >= nivel
```

---

## Características implementadas

### Memoria dinámica
- Los arreglos se crean con `new` según el tamaño que indica el usuario
- Se libera la memoria con `delete[]` al terminar de usar cada arreglo
- El puntero `arreglo` se reutiliza para el Ejercicio 1 después de liberar el primer arreglo

### Validación
- Se rechazan entradas que no son números (`cin.fail()`), limpiando el estado de error y el buffer
- Se validan los rangos de cada cantidad y de cada número ingresado
- Se valida que los números se ingresen en orden no decreciente, comparando con el anterior

### Salida por consola
- Los arreglos se muestran con el formato `[ a, b, c]`
- Los histogramas se dibujan con una fila de asteriscos por elemento

### Complejidad
- Desordenar: `O(N)`
- Transponer: `O(N × M)`, donde `M` es el valor máximo del histograma

## Notas importantes
- El desorden del Ejercicio 0 realiza `N / 2` intercambios, por lo que algunos elementos pueden quedar en su posición original.
- El resultado del Ejercicio 0 es distinto en cada ejecución gracias a `srand(time(nullptr))`.
- El tamaño del arreglo transpuesto depende del valor más alto ingresado; números muy grandes generan histogramas y arreglos muy grandes.
- Los mensajes llevan tildes y signos especiales; en algunas consolas de Windows puede ser necesario configurar la codificación UTF-8 (por ejemplo, con `chcp 65001`) para verlos correctamente.
- Todos los comentarios del código explican cada paso del algoritmo.

## Autor
Owel Jafet Gutiérrez Ortiz

## Carnet
2026800869

## Profesor
Mauricio Avilés Cisneros

## Fecha de entrega
19/08/2026

## Institución
Instituto Tecnológico de Costa Rica
Escuela de Computación
Bachillerato en Ingeniería en Computación
