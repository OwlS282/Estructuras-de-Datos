# Tarea Corta 0 – Ejercicios con Arreglos en Memoria Dinámica

## Descripción
Esta tarea consiste en la implementación de ejercicios básicos con arreglos dinámicos en C++, incluyendo:
- Creación de arreglos dinámicos
- Liberación de memoria
- Operaciones básicas (inserción, eliminación, búsqueda)
- Manejo correcto de punteros
- Redimensionamiento dinámico

## Parte 1: Implementación de funciones básicas

### Funciones a implementar
- `crearArreglo(int tamaño)` - Crea un arreglo dinámico
- `liberarArreglo(int* arr)` - Libera la memoria del arreglo
- `insertarElemento(int* &arr, int &tamaño, int posicion, int elemento)` - Inserta un elemento en una posición
- `eliminarElemento(int* &arr, int &tamaño, int posicion)` - Elimina un elemento en una posición
- `buscarElemento(int* arr, int tamaño, int elemento)` - Busca un elemento en el arreglo
- `imprimirArreglo(int* arr, int tamaño)` - Imprime los elementos del arreglo

## Parte 2: Aplicaciones prácticas

El programa implementa operaciones comunes con arreglos dinámicos:
- **Lectura de datos** - Capturar elementos del usuario
- **Inserción** - Agregar elementos en cualquier posición
- **Eliminación** - Remover elementos manteniendo orden
- **Búsqueda** - Encontrar elementos en el arreglo
- **Validación** - Verificar límites y errores

## Requisitos
- C++11 o superior
- Compilador: g++, clang o MSVC (Visual Studio)
- Conocimientos básicos de punteros y memoria dinámica

## Archivos incluidos

├── src/
│ ├── funciones.h - Declaración de funciones
│ ├── funciones.cpp - Implementación de funciones
│ ├── main.cpp - Programa principal
│ └── utilidades.h/cpp - Funciones auxiliares (opcional)
└── README.md


## Compilación

### En Windows (Visual Studio):
```bash
g++ -o arreglos src/main.cpp src/funciones.cpp
```

### En Linux/Mac:
```bash
g++ -std=c++11 -o arreglos src/main.cpp src/funciones.cpp
./arreglos
```

## Uso
```bash
./arreglos
```

El programa muestra un menú para realizar operaciones con arreglos dinámicos.

**Ejemplo:**
Crear arreglo
Insertar elemento
Eliminar elemento
Buscar elemento
Imprimir arreglo
Salir

Opción: 1
Tamaño del arreglo: 5
Arreglo creado exitosamente


## Características implementadas

### Parte 1 - Funciones básicas
- Creación de arreglos dinámicos con `new`
- Liberación de memoria con `delete`
- Inserción de elementos en cualquier posición
- Eliminación de elementos manteniendo orden
- Búsqueda de elementos
- Impresión de arreglos

### Parte 2 - Programa principal
- Menú interactivo
- Validación de entrada de usuario
- Manejo de errores con try/catch
- Visualización de operaciones paso a paso
- Control de límites de arreglo

## Notas importantes
- Se utilizó memoria dinámica con `new` y `delete`
- Los punteros se pasaron por referencia cuando fue necesario modificarlos
- Se validó que los índices sean válidos antes de acceder
- Se implementó detección de desbordamiento de memoria
- El programa muestra el estado del arreglo después de cada operación
- Se liberó correctamente toda memoria asignada

## Recomendaciones seguidas
1. Separación de funciones en archivos (.h y .cpp)
2. Validación de entrada de usuario
3. Uso de try/catch para manejo de excepciones
4. Punteros pasados por referencia cuando es necesario
5. Comentarios en el código
6. Impresión del estado del arreglo
7. Liberación correcta de memoria
8. Manejo de límites y errores

## Autor
Owel Jafet Gutiérrez Ortiz

## Profesor
Mauricio Avilés Cisneros

## Fecha de entrega
18/08/2026

## Instituto
Instituto Tecnológico de Costa Rica
Escuela de Computación
Bachillerato en Ingeniería en Computación
IC-2001 Estructuras de Datos