# Tarea Corta 2 – Colas: Atención de Emergencias

## Descripción
Esta tarea consiste en la implementación y utilización de dos estructuras de datos tipo Cola:
1. **ArrayQueue** - Cola implementada con arreglos dinámicos
2. **LinkedQueue** - Cola implementada con nodos enlazados

El programa simula un sistema de atención de emergencias en un hospital usando colas de prioridad.

## Parte 1: Implementación de las clases

### ArrayQueue
- Constructor y destructor
- `void enqueue(E element)` - Añade elemento al final
- `E dequeue()` - Extrae elemento del frente
- `E front()` - Retorna el elemento del frente sin extraer
- `void clear()` - Vacía la cola
- `bool isEmpty()` - Verifica si está vacía
- `int getSize()` - Retorna el tamaño actual
- `void print()` - Imprime los elementos de la cola

### LinkedQueue
- Mismos métodos que ArrayQueue
- Implementación con nodos enlazados dinámicamente
- Manejo automático de memoria

## Parte 2: Sistema de Atención de Emergencias

El programa simula la atención de pacientes en una emergencia:
- **Cola de espera** - Almacena a los pacientes esperando
- **Niveles de prioridad** - Crítico, Alto, Medio, Bajo
- **Atención** - Procesa pacientes según prioridad

## Requisitos
- C++11 o superior
- Compilador: g++, clang o MSVC (Visual Studio)
- Conocimientos de colas y estructuras de datos

## Archivos incluidos
├── src/
│ ├── Stack.h - Clase abstracta Stack
│ ├── ArrayStack.h - Declaración de ArrayStack
│ ├── ArrayStack.cpp - Implementación de ArrayStack
│ ├── LinkedStack.h - Declaración de LinkedStack
│ ├── LinkedStack.cpp - Implementación de LinkedStack
│ ├── main.cpp - Programa principal y evaluador de expresiones
│ └── utilidades.h/cpp - Funciones auxiliares (opcional)
└── README.md


## Compilación

### En Windows (Visual Studio):
```bash
g++ -o evaluador src/main.cpp src/ArrayStack.cpp src/LinkedStack.cpp
```

### En Linux/Mac:
```bash
g++ -std=c++11 -o evaluador src/main.cpp src/ArrayStack.cpp src/LinkedStack.cpp
./evaluador
```

## Uso
```bash
./evaluador
```

El programa solicitará que ingrese una expresión matemática y mostrará el resultado paso a paso.

**Ejemplo:**


## Características implementadas

### Parte 1 - Estructuras de datos
- Clase abstracta Stack
- ArrayStack con redimensionamiento automático
- LinkedStack con nodos enlazados
- Métodos push, pop, topValue, clear, isEmpty, getSize, print

### Parte 2 - Evaluador de expresiones
- Lectura y tokenización de expresiones
- Validación de tokens (números, operadores, paréntesis)
- Manejo de precedencia de operadores
- Detección de errores en expresiones inválidas
- Uso de try/catch para manejo de excepciones
- Impresión de pasos del proceso

## Notas importantes
- Las expresiones se limpian de espacios en blanco al inicio
- Se valida que la expresión esté bien formada
- Se implementó manejo de errores con try/catch
- Las pilas se pasan por referencia a las funciones
- Se utilizó memoria dinámica con `new` y `delete`
- El programa muestra el estado de las pilas en cada paso

## Recomendaciones seguidas
1. Dividir el problema en subproblemas
2. Eliminar espacios en blanco de la expresión
3. Subrutina para obtener el siguiente token
4. Subrutinas para identificar tipo de token
5. Subrutina para precedencia de operadores
6. Subrutina para procesar operaciones
7. Uso de try/catch
8. Pilas enviadas por referencia
9. Consulta con profesor si hay inconvenientes

## Autor
Owel Jafet Gutiérrez Ortiz

## Profesor
Mauricio Avilés Cisneros

## Fecha de entrega
01/09/2026

## Instituto
Instituto Tecnológico de Costa Rica
Escuela de Computación
Bachillerato en Ingeniería en Computación
IC-2001 Estructuras de Datos