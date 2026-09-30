# Tarea Corta 4 – Listas Circulares

## Descripción
Esta tarea consiste en la implementación y utilización de dos estructuras de datos tipo Lista Circular:
1. **CircularArrayList** - Lista circular implementada con arreglos dinámicos
2. **CircularLinkedList** - Lista circular implementada con nodos enlazados

El programa implementa operaciones especializadas para listas circulares incluyendo rotación y búsqueda circular.

## Parte 1: Implementación de las clases

### CircularArrayList
- Constructor y destructor
- `void add(E element)` - Añade elemento al final
- `void add(int index, E element)` - Inserta elemento en posición
- `E remove(int index)` - Elimina elemento en posición
- `E get(int index)` - Retorna elemento en posición
- `void clear()` - Vacía la lista
- `bool isEmpty()` - Verifica si está vacía
- `int getSize()` - Retorna el tamaño actual
- `void rotate(int n)` - Rota la lista n posiciones
- `void print()` - Imprime los elementos de la lista circular

### CircularLinkedList
- Mismos métodos que CircularArrayList
- Implementación con nodos enlazados en forma circular
- El último nodo apunta al primero
- Manejo automático de memoria

## Parte 2: Aplicaciones de Listas Circulares

El programa implementa algoritmos que usan listas circulares:
- **Problema de Josephus** - Simulación de eliminación circular
- **Rotación de turnos** - Sistema de turnos circular
- **Búsqueda circular** - Búsqueda continua en la estructura

## Requisitos
- C++11 o superior
- Compilador: g++, clang o MSVC (Visual Studio)
- Conocimientos de listas circulares y estructuras de datos

## Archivos incluidos
├── src/
│ ├── CircularList.h - Clase abstracta CircularList
│ ├── CircularArrayList.h - Declaración de CircularArrayList
│ ├── CircularArrayList.cpp - Implementación de CircularArrayList
│ ├── CircularLinkedList.h - Declaración de CircularLinkedList
│ ├── CircularLinkedList.cpp - Implementación de CircularLinkedList
│ ├── main.cpp - Programa principal
│ └── utilidades.h/cpp - Funciones auxiliares (opcional)
└── README.md


## Compilación

### En Windows (Visual Studio):
```bash
g++ -o listas_circulares src/main.cpp src/CircularArrayList.cpp src/CircularLinkedList.cpp
```

### En Linux/Mac:
```bash
g++ -std=c++11 -o listas_circulares src/main.cpp src/CircularArrayList.cpp src/CircularLinkedList.cpp
./listas_circulares
```

## Uso
```bash
./listas_circulares
```

El programa muestra ejemplos de operaciones con listas circulares.

**Ejemplo:**

Lista circular: [1, 2, 3, 4, 5]
Rotación de 2 posiciones: [4, 5, 1, 2, 3]
Problema de Josephus (k=2): Eliminando cada 2do elemento

## Características implementadas

### Parte 1 - Estructuras de datos
- Clase abstracta CircularList
- CircularArrayList con manejo circular
- CircularLinkedList con nodos enlazados circulares
- Métodos add, remove, get, clear, isEmpty, getSize, rotate, print

### Parte 2 - Aplicaciones
- Implementación del problema de Josephus
- Sistema de turnos circular
- Búsqueda circular en la lista
- Rotación de elementos
- Validación de operaciones circulares
- Manejo de errores con try/catch
- Visualización del comportamiento circular

## Notas importantes
- En una lista circular el último nodo apunta al primero
- Se implementó rotación eficiente sin mover elementos
- Se utilizó memoria dinámica con `new` y `delete`
- Las listas se pasan por referencia a las funciones
- Se validó que los índices sean válidos en contexto circular
- El programa muestra el estado circular de la estructura

## Recomendaciones seguidas
1. Dividir el problema en subproblemas
2. Entender la naturaleza circular de la estructura
3. Implementar rotación eficientemente
4. Validar entrada de usuario
5. Usar try/catch para manejo de errores
6. Listas enviadas por referencia
7. Comentar el código
8. Mostrar ejemplos de uso

## Autor
Owel Jafet Gutiérrez Ortiz

## Profesor
Mauricio Avilés Cisneros

## Fecha de entrega
29/09/2026

## Instituto
Instituto Tecnológico de Costa Rica
Escuela de Computación
Bachillerato en Ingeniería en Computación
IC-2001 Estructuras de Datos