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
│ ├── Queue.h - Clase abstracta Queue
│ ├── ArrayQueue.h - Declaración de ArrayQueue
│ ├── ArrayQueue.cpp - Implementación de ArrayQueue
│ ├── LinkedQueue.h - Declaración de LinkedQueue
│ ├── LinkedQueue.cpp - Implementación de LinkedQueue
│ ├── Paciente.h - Clase Paciente
│ ├── main.cpp - Programa principal
│ └── utilidades.h/cpp - Funciones auxiliares (opcional)
└── README.md

## Compilación

### En Windows (Visual Studio):
```bash
g++ -o emergencias src/main.cpp src/ArrayQueue.cpp src/LinkedQueue.cpp
```

### En Linux/Mac:
```bash
g++ -std=c++11 -o emergencias src/main.cpp src/ArrayQueue.cpp src/LinkedQueue.cpp
./emergencias
```

## Uso
```bash
./emergencias
```

El programa simula la atención de emergencias mostrando el flujo de pacientes.

**Ejemplo:**
Paciente registrado: Juan (Crítico)
Paciente registrado: María (Medio)
Atendiendo a: Juan (Crítico)
Atendiendo a: María (Medio)


## Características implementadas

### Parte 1 - Estructuras de datos
- Clase abstracta Queue
- ArrayQueue con manejo dinámico
- LinkedQueue con nodos enlazados
- Métodos enqueue, dequeue, front, clear, isEmpty, getSize, print

### Parte 2 - Sistema de emergencias
- Registro de pacientes con prioridad
- Cola de atención basada en prioridad
- Simulación del proceso de atención
- Validación de datos de entrada
- Manejo de errores con try/catch
- Impresión del estado de la cola

## Notas importantes
- Se implementó manejo de prioridades en las colas
- Se utilizó memoria dinámica con `new` y `delete`
- Las colas se pasan por referencia a las funciones
- Se validó que los datos sean correctos
- El programa muestra el estado de la cola en cada operación

## Recomendaciones seguidas
1. Dividir el problema en subproblemas
2. Implementar clase Paciente
3. Validar entrada de usuario
4. Usar try/catch para manejo de errores
5. Colas enviadas por referencia
6. Comentar el código
7. Mostrar el estado de la cola

## Autor
Owel Jafet Gutiérrez Ortiz

## Profesor
Mauricio Avilés Cisnero

## Fecha de entrega
10/09/2026

## Instituto
Instituto Tecnológico de Costa Rica
Escuela de Computación
Bachillerato en Ingeniería en Computación
IC-2001 Estructuras de Datos