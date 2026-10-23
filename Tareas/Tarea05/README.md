# Tarea Corta 5 – Radix Sort

## Descripción
Esta tarea consiste en la implementación del algoritmo de ordenamiento **Radix Sort** de forma que la **base numérica sea un parámetro** del algoritmo. Los baldes que utiliza el algoritmo se construyen con la estructura **LinkedList** implementada en tareas anteriores.

El programa permite ordenar listas de enteros aleatorios con la base que el usuario elija, y medir el tiempo de ejecución para comparar el desempeño de diferentes bases.

## Parte 1: Programa

El programa realiza lo siguiente:
1. Solicita al usuario el tamaño de la lista a ordenar
2. Solicita al usuario la base numérica a utilizar
3. Crea una lista de enteros del tamaño indicado
4. Llena la lista con números enteros aleatorios
5. Envía la lista por referencia a la subrutina `radixSort`, junto con la base
6. Dentro de `radixSort` crea los baldes (un `LinkedList` por cada dígito de la base)
7. Ordena los elementos y deja el resultado en la lista original
8. Imprime en pantalla el resultado del ordenamiento y el tiempo de ejecución
9. Pregunta al usuario si desea repetir

### Funciones principales
- `void radixSort(LinkedList<int>& lista, int base)` - Ordena la lista con Radix Sort usando la base indicada
- `int getMax(LinkedList<int>& lista)` - Obtiene el valor máximo para saber cuántas pasadas realizar
- `int numeroAleatorio()` - Genera un entero aleatorio entre 0 y 999999
- `int leerEntero(const char* mensaje, int minimo)` - Lee un entero validando la entrada del usuario

### Funcionamiento del algoritmo
Por cada dígito del número más grande (de menos a más significativo) se realizan dos fases:
- **Distribución:** cada elemento se saca de la lista y se coloca en el balde que corresponde a su dígito, calculado como `(valor / peso) % base`
- **Recolección:** los baldes se vacían en orden, del 0 al `base - 1`, para reconstruir la lista original

El `peso` inicia en 1 y se multiplica por la base en cada pasada.

## Parte 2: Pruebas e informe
Se realizaron pruebas con listas pequeñas y luego con tamaños cada vez mayores, comparando el tiempo de ordenamiento con diferentes bases. Los resultados y la configuración recomendada se explican en el documento de texto incluido en el proyecto (`Informe.txt`).

## Requisitos
- C++11 o superior
- Compilador: g++, clang o MSVC (Visual Studio)
- Estructura LinkedList de tareas anteriores

## Archivos incluidos
```
├── main.cpp         - Programa principal y algoritmo Radix Sort
├── List.h           - Clase abstracta List
├── LinkedList.h     - Implementación de la lista enlazada
├── Informe.txt      - Resultados de las pruebas y recomendación
└── README.md
```

## Compilación

### En Windows (Visual Studio):
Crear un proyecto de consola, agregar los archivos del proyecto y compilar con Ctrl + F5.

### En Linux/Mac:
```bash
g++ -std=c++11 -o radixsort main.cpp
./radixsort
```

## Uso
```bash
./radixsort
```

El programa solicita el tamaño de la lista y la base. Si el usuario escribe un dato inválido, vuelve a pedirlo.

**Ejemplo:**
```
Ingrese el tamano de la lista: 5
Ingrese la base numerica (minimo 2): 10

Lista ordenada:
[69332, 174344, 274745, 777046, 843540]

Tiempo: 0 ms

Desea repetir? (s/n): n
```

## Características implementadas
- Radix Sort con la base como parámetro
- Baldes construidos con LinkedList (arreglo dinámico de listas, uno por dígito)
- Lista enviada por referencia; el resultado queda en la lista original
- Números aleatorios entre 0 y 999999
- Validación de la entrada del usuario (tamaño >= 1, base >= 2)
- Medición del tiempo con las funciones de tiempo de C++ (`clock`)
- Opción de repetir el proceso

## Notas importantes
- El algoritmo funciona con enteros **no negativos**
- Se utilizó memoria dinámica con `new` y `delete[]` para los baldes, y se libera al terminar `radixSort`
- Con bases pequeñas se necesitan más pasadas; con bases muy grandes se crean y recorren más baldes
- El tiempo medido corresponde únicamente a la ejecución de `radixSort`
- Con listas pequeñas `clock()` puede mostrar 0 ms por su poca precisión

## Autor
Owel Jafet Gutiérrez Ortiz

## Profesor
Mauricio Avilés Cisneros

## Fecha de entrega
(completar)

## Instituto
Instituto Tecnológico de Costa Rica
Escuela de Computación
Bachillerato en Ingeniería en Computación
IC-2001 Estructuras de Datos
