# Tarea Corta 3 - Listas: Caja de Herramientas

## Descripción
Esta tarea consiste en la implementación y utilización de dos estructuras de datos tipo Lista:
1. **ArrayList** - Lista implementada con arreglos dinámicos
2. **LinkedList** - Lista implementada con nodos enlazados

El programa simula un sistema de gestión de una caja de herramientas con operaciones de inserción, búsqueda y eliminación.

## Parte 1: Implementación de las clases

### ArrayList
- Constructor y destructor
- `void add(E element)` - Añade elemento al final
- `void add(int index, E element)` - Inserta elemento en posición
- `E remove(int index)` - Elimina elemento en posición
- `E get(int index)` - Retorna elemento en posición
- `void clear()` - Vacía la lista
- `bool isEmpty()` - Verifica si está vacía
- `int getSize()` - Retorna el tamaño actual
- `int indexOf(E element)` - Busca índice de elemento
- `void print()` - Imprime los elementos de la lista

### LinkedList
- Mismos métodos que ArrayList
- Implementación con nodos enlazados dinámicamente
- Manejo automático de memoria

## Parte 2: Sistema de Gestión de Herramientas

El programa gestiona una caja de herramientas:
- **Herramientas** - Nombre, tipo, cantidad
- **Operaciones** - Agregar, buscar, eliminar, listar
- **Persistencia** - Guardar y cargar herramientas

## Requisitos
- C++11 o superior
- Compilador: g++, clang o MSVC (Visual Studio)
- Conocimientos de listas y estructuras de datos

## Archivos incluidos
├── src/
│ ├── List.h - Clase abstracta List
│ ├── ArrayList.h - Declaración de ArrayList
│ ├── ArrayList.cpp - Implementación de ArrayList
│ ├── LinkedList.h - Declaración de LinkedList
│ ├── LinkedList.cpp - Implementación de LinkedList
│ ├── Herramienta.h - Clase Herramienta
│ ├── main.cpp - Programa principal
│ └── utilidades.h/cpp - Funciones auxiliares (opcional)
└── README.md


## Compilación

### En Windows (Visual Studio):
```bash
g++ -o caja_herramientas src/main.cpp src/ArrayList.cpp src/LinkedList.cpp
```

### En Linux/Mac:
```bash
g++ -std=c++11 -o caja_herramientas src/main.cpp src/ArrayList.cpp src/LinkedList.cpp
./caja_herramientas
```

## Uso
```bash
./caja_herramientas
```

El programa muestra un menú para gestionar la caja de herramientas.

**Ejemplo:**
Agregar herramienta
Buscar herramienta
Eliminar herramienta
Listar herramientas
Salir

Opción: 1
Nombre: Martillo
Tipo: Golpeo
Cantidad: 2


## Características implementadas

### Parte 1 - Estructuras de datos
- Clase abstracta List
- ArrayList con redimensionamiento
- LinkedList con nodos enlazados
- Métodos add, remove, get, clear, isEmpty, getSize, indexOf, print

### Parte 2 - Sistema de herramientas
- Creación de clase Herramienta
- Menú interactivo
- Agregar herramientas
- Buscar herramientas
- Eliminar herramientas
- Listar todas las herramientas
- Validación de entrada
- Manejo de errores con try/catch

## Notas importantes
- Se implementó inserción y eliminación en cualquier posición
- Se utilizó memoria dinámica con `new` y `delete`
- Las listas se pasan por referencia a las funciones
- Se validó que los índices sean válidos
- El programa muestra el estado de la lista después de cada operación

## Recomendaciones seguidas
1. Dividir el problema en subproblemas
2. Implementar clase Herramienta
3. Crear menú interactivo
4. Validar entrada de usuario
5. Usar try/catch para manejo de errores
6. Listas enviadas por referencia
7. Comentar el código
8. Mostrar el estado de la lista

## Autor
Owel Jafet Gutiérrez Ortiz

## Profesor
Mauricio Avilés Cisneros

## Fecha de entrega
24/09/2026

## Instituto
Instituto Tecnológico de Costa Rica
Escuela de Computación
Bachillerato en Ingeniería en Computación
IC-2001 Estructuras de Datos