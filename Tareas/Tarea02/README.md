# Tarea Corta 2 - Colas: Atención de Emergencias

## Descripción
Esta tarea consiste en la implementación de un sistema de **triage de emergencias** en C++ utilizando colas genéricas. Los pacientes llegan a una sala de emergencias con una condición de gravedad del 1 al 5, y siempre se atiende primero al paciente más urgente; entre pacientes de la misma gravedad, se atiende primero al que llegó antes. Para lograrlo se implementa una **cola de prioridad** formada por un arreglo de colas enlazadas, una por cada nivel de urgencia. El programa permite:
- Ingresar pacientes indicando su ID y su condición (nivel 1 a 5)
- Atender al siguiente paciente según su prioridad y su orden de llegada
- Ver en pantalla, antes de cada acción, el estado de la cola de espera
- Registrar la hora de llegada y de atención de cada paciente, y calcular cuánto esperó
- Validar la entrada del usuario sin que el programa se cierre inesperadamente

## Requisitos del problema

### Niveles de condición (triage)

| Nivel | Color | Descripción | Prioridad |
|-------|-------|-------------|-----------|
| 1 | Azul | Resucitación | Más alta |
| 2 | Rojo | Emergencia | |
| 3 | Amarillo | Urgente | |
| 4 | Verde | Menos urgente | |
| 5 | Blanco | No urgente | Más baja |

### Patient
- **Id**: Identificador del paciente (texto)
- **Nivel**: Condición de gravedad, de 1 a 5
- **Hora de llegada**: Se guarda automáticamente al crear el paciente
- **Hora de atención**: Se guarda al atender al paciente
- **Tiempo de espera**: Segundos entre la llegada y la atención
- **attend()**: Marca al paciente como atendido, guarda la hora y calcula la espera
- **print()**: Muestra ID, condición, hora de llegada, hora de atención y espera
- **operator<<**: Permite imprimir un paciente con `cout`, en la forma `(Id: 111, Nivel: 4)`

### Queue (clase abstracta genérica)
- TAD de una cola FIFO; solo declara las operaciones
- **enqueue(element)**, **dequeue()**, **frontValue()**, **clear()**, **isEmpty()**, **getSize()** y **print()**
- Constructor de copia y operador de asignación eliminados; destructor virtual

### LinkedQueue
- Implementación de `Queue` con **nodos enlazados** y un **nodo centinela** al frente
- El centinela simplifica `enqueue` y `dequeue`, porque la cola nunca tiene el `front` vacío
- `enqueue` y `dequeue` se hacen en tiempo constante, gracias a los punteros `front` y `back`

### Node
- Nodo genérico enlazado: guarda un `element` y un puntero `next`
- Tiene un segundo constructor sin elemento, usado para crear el nodo centinela

### PriorityQueue (clase abstracta genérica)
- TAD de una cola de prioridad; solo declara las operaciones
- **insert(element, priority)**, **min()**, **removeMin()**, **clear()**, **getSize()**, **isEmpty()** y **print()**
- La prioridad `0` es la más alta

### LinkedPriorityQueue
- Implementación de `PriorityQueue` con un **arreglo de `LinkedQueue`**, una cola por cada prioridad posible
- `insert` agrega el elemento al final de la cola de su prioridad
- `min` y `removeMin` buscan la primera cola no vacía, de la prioridad más alta (índice 0) a la más baja
- Por eso, dentro de una misma prioridad, el orden es el de llegada (FIFO)

### main (programa principal)
- Muestra el menú, lee y valida los datos y usa una `LinkedPriorityQueue<Patient>` de 5 niveles
- Funciones auxiliares: `leerEntero()`, `leerTexto()`, `mostrarEstado()`, `ingresarPaciente()` y `atenderPaciente()`

## Reglas de validación
- La opción del menú debe ser un entero entre 1 y 3.
- El ID del paciente no puede estar vacío.
- El nivel de condición debe ser un entero entre 1 y 5.
- Si una entrada es inválida, se muestra "Entrada invalida, intente de nuevo." y se vuelve a pedir.
- Si se intenta atender y no hay pacientes, se avisa con el mensaje "No hay pacientes en espera." y se vuelve al menú.
- Los errores de la cola (prioridad inválida, cola vacía) lanzan `runtime_error`, que se captura en `main`.

## Algoritmos

### Ingresar un paciente
1. Se pide el ID y el nivel de condición.
2. Se crea el `Patient` (que guarda la hora de llegada actual).
3. Se inserta en la cola de prioridad con prioridad `nivel - 1` (los niveles van de 1 a 5, pero los índices del arreglo van de 0 a 4).

### Atender a un paciente
1. Si la cola está vacía, se avisa y termina.
2. `removeMin()` recorre las colas desde el índice 0 y saca el primer elemento de la primera cola que no esté vacía.
3. Se llama a `attend()` para guardar la hora de atención y calcular la espera.
4. Se muestran los datos del paciente.

### Complejidad
- `insert`, `enqueue` y `dequeue`: `O(1)`
- `min` y `removeMin`: `O(P)`, donde `P` es la cantidad de prioridades (5 en este programa), es decir, prácticamente constante

## Conceptos implementados

- **Plantillas (templates)**: `Queue<E>`, `LinkedQueue<E>`, `Node<E>`, `PriorityQueue<E>` y `LinkedPriorityQueue<E>` sirven para cualquier tipo; en el programa se usan con `Patient`
- **Tipos abstractos de datos (TAD)**: `Queue` y `PriorityQueue` definen *qué* se puede hacer; las clases `Linked...` definen *cómo*
- **Herencia y métodos virtuales puros**: Las implementaciones heredan de las clases abstractas
- **Destructor virtual y liberación de memoria**: `delete[]` sobre el arreglo de colas ejecuta el destructor de cada `LinkedQueue`, que a su vez libera todos sus nodos
- **Composición**: `LinkedPriorityQueue` contiene un arreglo de `LinkedQueue`
- **Nodo centinela**: Nodo falso al inicio de la lista que evita casos especiales al insertar y eliminar
- **Sobrecarga de operadores**: `operator<<` como función amiga (`friend`) de `Patient`
- **Encapsulamiento**: Atributos privados y métodos de apoyo privados (`conditionText()` y `formatTime()`)
- **Manejo de horas**: `time_t`, `time()` y `localtime()` de `<ctime>`
- **Manejo de excepciones**: `throw runtime_error` y `try/catch` en `main`
- **Copia deshabilitada**: Constructor de copia y asignación eliminados en las clases base

## Requisitos técnicos
- Compilador de C++ con soporte para C++11 o superior (se usan `nullptr` y `stoi`)
- IDE: Visual Studio, Code::Blocks, CLion o Visual Studio Code, o `g++` por terminal

## Estructura del proyecto

```
Emergencias/
├── main.cpp                 - Programa principal (menú y triage)
├── Patient.h                - Declaración de la clase Patient
├── Patient.cpp              - Implementación de Patient
├── Queue.h                  - Clase abstracta de las colas
├── LinkedQueue.h            - Cola con nodos enlazados y centinela
├── Node.h                   - Nodo enlazado genérico
├── PriorityQueue.h          - Clase abstracta de las colas de prioridad
└── LinkedPriorityQueue.h    - Cola de prioridad (arreglo de LinkedQueue)
```

Las clases genéricas son plantillas, por lo que su código completo está en los archivos `.h`. Solo `Patient` tiene archivo `.cpp`.

## Compilación y ejecución

### Por terminal (g++):
```bash
g++ -std=c++11 -o emergencias main.cpp Patient.cpp
./emergencias
```

### En Visual Studio:
1. Crear un proyecto de aplicación de consola vacío.
2. Agregar `main.cpp` y `Patient.cpp` a los archivos de código fuente, y los `.h` a los archivos de encabezado.
3. Ejecutar con `Ctrl + F5`.

## Menú del programa

```
TRIAGE - Cola de espera:
0: [ ]
1: [ ]
2: [ ]
3: [ ]
4: [ ]

1. Ingresar paciente
2. Atender paciente
3. Salir
Opcion:
```

Antes de cada opción se muestra el estado de la cola. El número a la izquierda de cada línea es el **índice de la cola** dentro del arreglo, que equivale al nivel de condición menos 1: la línea `0:` contiene a los pacientes de nivel 1 (Azul), la `1:` a los de nivel 2 (Rojo), y así sucesivamente.

## Ejemplo de ejecución

Ingreso de tres pacientes y atención del más urgente (las horas dependen del momento de ejecución):

```
Opcion: 1
ID: 111
CONDICION (1-Azul, 2-Rojo, 3-Amarillo, 4-Verde, 5-Blanco): 4

Opcion: 1
ID: 222
CONDICION (1-Azul, 2-Rojo, 3-Amarillo, 4-Verde, 5-Blanco): 2

Opcion: 1
ID: 333
CONDICION (1-Azul, 2-Rojo, 3-Amarillo, 4-Verde, 5-Blanco): 4

TRIAGE - Cola de espera:
0: [ ]
1: [ (Id: 222, Nivel: 2) ]
2: [ ]
3: [ (Id: 111, Nivel: 4), (Id: 333, Nivel: 4) ]
4: [ ]

1. Ingresar paciente
2. Atender paciente
3. Salir
Opcion: 2
PACIENTE EN ATENCION:
ID: 222
CONDICION: 2 ROJO - Emergencia
LLEGADA: 2026-9-10 14:3:21
ATENDIDO: 2026-9-10 14:3:48
ESPERA: 27 s
```

Al atender de nuevo, se atiende primero a `111` y luego a `333` (mismo nivel, orden de llegada).

Ejemplos de mensajes de error:

```
Opcion: 7
Entrada invalida, intente de nuevo.

ID:
Entrada invalida, intente de nuevo.

Opcion: 2          (sin pacientes en espera)
No hay pacientes en espera.
```

---

# DIAGRAMAS

## Jerarquía de clases

```
┌──────────────────────┐                ┌──────────────────────┐
│ Queue<E>             │                │ PriorityQueue<E>     │
│ <<abstract>>         │                │ <<abstract>>         │
└──────────┬───────────┘                └──────────┬───────────┘
           │                                       │
┌──────────▼───────────┐                ┌──────────▼───────────┐
│ LinkedQueue<E>       │◀───────────────│ LinkedPriorityQueue<E>│
└──────────┬───────────┘   0..* (arreglo)└──────────────────────┘
           │ usa
┌──────────▼───────────┐
│ Node<E>              │
└──────────────────────┘

main ──▶ LinkedPriorityQueue<Patient> ──▶ elementos de tipo Patient
```

## Asociaciones

```
main (1) ──── cola (1) ──── LinkedPriorityQueue<Patient>
LinkedPriorityQueue<E> (1) ──── queues (priorities) ──── LinkedQueue<E>
LinkedQueue<E> (1) ──── front, back (1) ──── Node<E>
Node<E> (1) ──── next (0..1) ──── Node<E>
Node<Patient> (1) ──── element (1) ──── Patient
```

## Cola de prioridad con 5 niveles

```
 insert(paciente, nivel - 1)

 índice   cola (FIFO)
 ───────  ─────────────────────────────────────────────
   0      [ nivel 1 - Azul ]       ◀── se atiende primero
   1      [ nivel 2 - Rojo ]
   2      [ nivel 3 - Amarillo ]
   3      [ nivel 4 - Verde ]
   4      [ nivel 5 - Blanco ]     ◀── se atiende al final

 removeMin(): recorre i = 0, 1, 2, ... y saca el primer elemento
              de la primera cola que no esté vacía
```

## LinkedQueue con nodo centinela

```
 Cola con dos pacientes:

 front                                              back
   │                                                  │
   ▼                                                  ▼
 ┌────────────┬───┐   ┌────────────┬───┐   ┌────────────┬──────┐
 │ centinela  │ ●─┼──▶│ Paciente A │ ●─┼──▶│ Paciente B │ null │
 └────────────┴───┘   └────────────┴───┘   └────────────┴──────┘
                         ▲ frontValue() y dequeue() actúan aquí

 Cola vacía:  front y back apuntan al mismo nodo centinela
```

---

# DIAGRAMA DE CLASES COMPLETO

```
╔════════════════════════════════════════════════════════╗
║ PATIENT                                                ║
╠════════════════════════════════════════════════════════╣
║ Atributos:                                             ║
║ - id: string                                           ║
║ - level: int                                           ║
║ - arrival: time_t                                      ║
║ - attended: time_t                                     ║
║ - waitingTime: time_t                                  ║
╠════════════════════════════════════════════════════════╣
║ Constructores:                                         ║
║ + Patient(id: string, level: int)                      ║
║ + Patient()                                            ║
╠════════════════════════════════════════════════════════╣
║ Métodos:                                               ║
║ - conditionText(): string                              ║
║ - formatTime(t: time_t): string                        ║
║ + attend(): void                                       ║
║ + print(): void                                        ║
║ + friend operator<<(os: ostream&, p: const Patient&):   ║
║ ostream&                                               ║
╚════════════════════════════════════════════════════════╝

╔════════════════════════════════════════════════════════╗
║ <<abstract>> QUEUE<E>                                  ║
╠════════════════════════════════════════════════════════╣
║ Métodos:                                               ║
║ + enqueue(element: E): void (virtual puro)             ║
║ + dequeue(): E (virtual puro)                          ║
║ + frontValue(): E (virtual puro)                       ║
║ + clear(): void (virtual puro)                         ║
║ + isEmpty(): bool (virtual puro)                       ║
║ + getSize(): int (virtual puro)                        ║
║ + print(): void (virtual puro)                         ║
║ (constructor de copia y asignación eliminados)         ║
╚════════════════════════════════════════════════════════╝

╔════════════════════════════════════════════════════════╗
║ LINKEDQUEUE<E>                        (extends Queue<E>)║
╠════════════════════════════════════════════════════════╣
║ Atributos:                                             ║
║ - front: Node<E>*  (apunta al centinela)               ║
║ - back: Node<E>*                                       ║
║ - size: int                                            ║
╠════════════════════════════════════════════════════════╣
║ Constructores:                                         ║
║ + LinkedQueue()                                        ║
║ + ~LinkedQueue()                                       ║
╠════════════════════════════════════════════════════════╣
║ Métodos:                                               ║
║ + enqueue(element: E): void                            ║
║ + dequeue(): E                                         ║
║ + frontValue(): E                                      ║
║ + clear(): void                                        ║
║ + isEmpty(): bool                                      ║
║ + getSize(): int                                       ║
║ + print(): void                                        ║
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
║ <<abstract>> PRIORITYQUEUE<E>                          ║
╠════════════════════════════════════════════════════════╣
║ Métodos:                                               ║
║ + insert(element: E, priority: int): void (virtual     ║
║ puro)                                                  ║
║ + min(): E (virtual puro)                              ║
║ + removeMin(): E (virtual puro)                        ║
║ + clear(): void (virtual puro)                         ║
║ + getSize(): int (virtual puro)                        ║
║ + isEmpty(): bool (virtual puro)                       ║
║ + print(): void (virtual puro)                         ║
║ (constructor de copia y asignación eliminados)         ║
╚════════════════════════════════════════════════════════╝

╔════════════════════════════════════════════════════════╗
║ LINKEDPRIORITYQUEUE<E>          (extends PriorityQueue<E>)║
╠════════════════════════════════════════════════════════╣
║ Atributos:                                             ║
║ - queues: LinkedQueue<E>*  (arreglo, una por prioridad)║
║ - priorities: int                                      ║
║ - size: int                                            ║
╠════════════════════════════════════════════════════════╣
║ Constructores:                                         ║
║ + LinkedPriorityQueue(priorities: int = 20)            ║
║ + ~LinkedPriorityQueue()                               ║
╠════════════════════════════════════════════════════════╣
║ Métodos:                                               ║
║ + insert(element: E, priority: int): void              ║
║ + min(): E                                             ║
║ + removeMin(): E                                       ║
║ + clear(): void                                        ║
║ + getSize(): int                                       ║
║ + isEmpty(): bool                                      ║
║ + print(): void                                        ║
╚════════════════════════════════════════════════════════╝

╔════════════════════════════════════════════════════════╗
║ MAIN (funciones del programa principal)                ║
╠════════════════════════════════════════════════════════╣
║ Constantes:                                            ║
║ NIVELES: int = 5                                       ║
╠════════════════════════════════════════════════════════╣
║ Funciones:                                             ║
║ leerEntero(mensaje: string, minimo: int,               ║
║ maximo: int): int                                      ║
║ leerTexto(mensaje: string): string                     ║
║ mostrarEstado(cola: LinkedPriorityQueue<Patient>&)     ║
║ ingresarPaciente(cola: LinkedPriorityQueue<Patient>&)  ║
║ atenderPaciente(cola: LinkedPriorityQueue<Patient>&)   ║
║ main(): int                                            ║
╚════════════════════════════════════════════════════════╝
```

## Asociaciones y multiplicidades

```
LinkedPriorityQueue ──────────────── LinkedQueue
1                                    priorities (5 en el programa)
(Composición: el arreglo de colas pertenece a la cola de prioridad)

LinkedQueue ──────────────────────── Node
1                                    0..*  (más el nodo centinela)

Node<Patient> ────────────────────── Patient
1                                    1

main ─────────────────────────────── LinkedPriorityQueue<Patient>
1                                    1
```

---

## Características implementadas

### Genericidad
- Las colas y los nodos no dependen del tipo de dato; el mismo código sirve para enteros, texto o pacientes
- `Patient` necesita un **constructor por defecto** porque el nodo centinela crea un elemento vacío

### Orden de atención
- Primero por **gravedad**: se recorre el arreglo desde la prioridad más alta
- Después por **llegada**: cada nivel es una cola FIFO, por lo que el primero en entrar es el primero en salir

### Memoria dinámica
- La `LinkedPriorityQueue` se crea como variable local de `main`; al terminar el programa su destructor libera el arreglo de colas
- Cada `LinkedQueue` libera todos sus nodos y su centinela en el destructor
- Al atender un paciente, su nodo se libera de inmediato

### Registro de tiempos
- La hora de llegada se guarda al crear el paciente y la de atención al llamar `attend()`
- El tiempo de espera se calcula como la diferencia de ambas, en segundos

### Validación
- Lectura de enteros con rango y de texto no vacío, con repetición de la pregunta
- Las excepciones de las colas se capturan en `main`, por lo que el programa no se cierra inesperadamente

## Notas importantes
- La cola se imprime con los **índices del arreglo** (0 a 4), que equivalen al nivel de condición menos 1.
- El programa no valida que el ID sea único: se pueden ingresar dos pacientes con el mismo ID.
- Las horas se imprimen sin ceros a la izquierda (por ejemplo, `14:3:7`).
- Los mensajes del programa se escriben sin tildes, para evitar problemas de codificación en la consola.
- Los datos no se guardan en disco: al cerrar el programa se pierde la cola de espera.
- `LinkedPriorityQueue` recibe la cantidad de prioridades en el constructor (el valor por defecto es 20); el programa usa 5.

## Autor
Owel Jafet Gutiérrez Ortiz

## Carnet
2026800869

## Profesor
Mauricio Avilés Cisneros

## Fecha de entrega
10/09/2026

## Institución
Instituto Tecnológico de Costa Rica
Escuela de Computación
Bachillerato en Ingeniería en Computación
