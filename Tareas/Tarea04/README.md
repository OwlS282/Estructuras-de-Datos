# Tarea Corta 4 - Listas Circulares: Zapatito Cochinito

## Descripción
Esta tarea consiste en la implementación de listas circulares genéricas en C++ y su uso en una simulación del juego infantil **"Zapatito Cochinito"**, una versión del problema de Flavio Josefo. Se implementa el TAD *Lista Circular* de dos formas distintas (**lista circular simplemente enlazada** y **lista circular doblemente enlazada**) a partir de una misma clase abstracta, y el usuario escoge cuál usar al iniciar el programa. Un grupo de personas forma un círculo y, en cada conteo, la rima cae sobre una persona: si estaba con el pie derecho cambia al izquierdo, y si ya estaba con el izquierdo sale del círculo. El juego termina cuando solo queda una persona. El programa permite:
- Escoger la cantidad de personas del círculo (de 2 a 50)
- Asignar los nombres automáticamente (lista predeterminada de 50 nombres) o ingresarlos manualmente
- Escoger la implementación de lista (`CircleList` o `DCircleList`)
- Escoger el modo de juego: **regular** (los conteos siempre van hacia la izquierda) o **dirigido** (el usuario elige la dirección de cada conteo)
- Ver en cada conteo el círculo completo, dónde inicia el conteo, en quién cae la última sílaba y cómo queda el círculo después
- Validar las entradas del usuario sin que el programa se cierre inesperadamente

> Los mensajes que muestra el programa están en español (sin tildes).

## Reglas del juego
- La rima tiene **9 partes**, por lo que el conteo hace **8 saltos** a partir de la persona donde inicia; la última sílaba (`"to"`) cae en la persona a la que se llega después de esos saltos.
- Si la persona elegida tenía el **pie derecho**, cambia al **pie izquierdo** y se queda en el círculo.
- Si la persona elegida ya tenía el **pie izquierdo**, **sale del círculo** (queda eliminada).
- El siguiente conteo inicia **a la par de la última persona elegida**, en la dirección que corresponda.
- Gana la **última persona que queda** en el círculo.

## Requisitos del problema

### CList (clase abstracta genérica)
- Define la interfaz común de las listas circulares mediante métodos virtuales puros
- **Modificar**: `insert(element)` (al frente), `insertBack(element)` (al final), `remove()` (del frente), `removeBack()` (del final) y `clear()`
- **Consultar**: `getFront()`, `getBack()` y `getSize()`
- **Navegar**: `next()` (el frente avanza una posición) y `previous()` (el frente retrocede una posición)
- **print()**: Muestra la lista en pantalla desde el frente
- Constructor de copia y operador de asignación eliminados; destructor virtual

### CircleList
- Implementación con una **lista circular simplemente enlazada**, sin nodos centinela
- Solo guarda un puntero `current` y la cantidad de elementos (`size`)
- `current` apunta al nodo **anterior al frente**, es decir, al **último** nodo: `frente = current->next` y `final = current`
- `removeBack()` y `previous()` deben recorrer la lista, porque los nodos no conocen a su anterior

### DCircleList
- Implementación con una **lista circular doblemente enlazada**, sin nodos centinela
- Guarda el mismo `current` y `size` que `CircleList`, con la misma convención (`frente = current->next`, `final = current`)
- Cada nodo conoce a su siguiente y a su anterior (`DNode`), por lo que `removeBack()` y `previous()` son inmediatos

### Node y DNode
- `Node<E>`: nodo de lista simple (`element` y `next`), con un segundo constructor sin elemento para nodo centinela
- `DNode<E>`: nodo de lista doble (`element`, `next` y `previous`), con un segundo constructor sin elemento para nodo centinela

### Person
- Representa a un jugador: **nombre** y **pie** que está usando (`leftFoot`: `false` = derecho, `true` = izquierdo)
- `operator<<` permite imprimirla con `cout` como `Isabel (pie derecho)`
- Tiene constructor por defecto y constructor con nombre (siempre inicia con el pie derecho)

### main (programa principal)
- Contiene la lista de 50 nombres predeterminados, el menú de configuración y las funciones `clearInput()`, `getValidInput(min, max)`, `askDirection()` y `fillList(list, amount, nameMode)`
- Crea la lista según el tipo escogido (usada mediante un puntero `CList<Person>*`), ejecuta los conteos hasta que queda una sola persona y libera la lista al salir

## Opciones del programa

| Pregunta | Opciones |
|----------|----------|
| Cantidad de personas | 2 a 50 |
| Nombres | 1. Automáticamente (lista predeterminada) / 2. Ingresarlos manualmente |
| Tipo de lista | 1. `CircleList` / 2. `DCircleList` |
| Modo de juego | 1. Regular (siempre izquierda) / 2. Dirigido (el usuario elige la dirección de cada conteo) |
| Dirección del conteo (solo en modo dirigido) | 1. Izquierda (sentido de las manecillas del reloj) / 2. Derecha (sentido contrario) |

## Reglas del negocio

### Cantidad de saltos
- En cada conteo se hacen `JUMPS % tamaño` saltos, con `JUMPS = 8`. Así se evitan vueltas completas innecesarias al círculo.
- Cuando quedan 2 personas, `8 % 2 = 0`, por lo que la última sílaba cae en la misma persona donde inicia el conteo.

### Dirección de los saltos
- **Izquierda** (sentido de las manecillas del reloj): cada salto es un `next()`
- **Derecha** (sentido contrario): cada salto es un `previous()`
- En modo regular la dirección siempre es izquierda

### Dónde inicia el siguiente conteo
El frente de la lista siempre es la persona donde inicia el conteo. Después de elegir a una persona, esta queda en el frente si cambió de pie (se vuelve a insertar con `insert`), o ya no existe si fue eliminada (el frente pasa a ser la persona siguiente a la izquierda). Según eso, el siguiente conteo se ubica así:

| Dirección del siguiente conteo | La persona elegida cambió de pie | La persona elegida fue eliminada |
|--------------------------------|----------------------------------|----------------------------------|
| Izquierda | `next()`: inicia en la persona a su izquierda | No se mueve: el frente ya es la persona a la izquierda |
| Derecha | `previous()`: inicia en la persona a su derecha | `previous()`: inicia en la persona a la derecha de la eliminada |

El primer conteo siempre inicia en la primera persona de la lista.

### Resultado del conteo
- La persona donde cae la última sílaba se remueve del frente con `remove()`
- Si `leftFoot` era `false`, se cambia a `true` y se vuelve a insertar al frente con `insert()`
- Si `leftFoot` era `true`, no se vuelve a insertar: queda eliminada
- El juego termina cuando `getSize()` es 1, y esa persona (`getFront()`) es la elegida

## Reglas de validación
- Todas las opciones se leen como enteros y deben estar dentro del rango del menú correspondiente:
  - Cantidad de personas: 2 a 50
  - Forma de asignar los nombres: 1 a 2
  - Tipo de lista: 1 a 2
  - Modo de juego: 1 a 2
  - Dirección del conteo: 1 a 2
- Si se escribe algo que no es un número o un número fuera de rango, se muestra el error y se vuelve a pedir la opción.
- Si un nombre ingresado manualmente se deja vacío, se usa `Persona N` (donde N es la posición de la persona).
- Los errores de las listas (por ejemplo, intentar remover o consultar en una lista vacía) lanzan `runtime_error`, que se captura en `main`, se muestra y libera la lista antes de terminar.

## Modelo de posición actual (current)

Las dos listas comparten la misma interfaz y la misma convención: `current` apunta al **último** nodo, que es el anterior al frente.

```
CircleList (lista circular simple)

        current
           │
           ▼
      ┌───────┐    ┌───────┐    ┌───────┐
  ┌──▶│   C   │───▶│   A   │───▶│   B   │──┐
  │   └───────┘    └───────┘    └───────┘  │
  │     (final)     (frente)                │
  └─────────────────────────────────────────┘

  current        →  C  (getBack)
  current->next  →  A  (getFront)

  next()      →  current avanza un nodo: el frente pasa a ser B
  previous()  →  se recorre la lista hasta encontrar el nodo anterior a current


DCircleList (lista circular doble)

        current
           │
           ▼
      ┌───────┐ ◀─▶ ┌───────┐ ◀─▶ ┌───────┐
  ┌──▶│   C   │     │   A   │     │   B   │──┐
  │   └───────┘     └───────┘     └───────┘  │
  │                                           │
  └───────────────────────────────────────────┘
        (el último y el primero también se enlazan en ambas direcciones)

  previous()  →  current = current->previous  (inmediato)
```

## Complejidad de las operaciones

| Operación | CircleList | DCircleList |
|-----------|------------|-------------|
| `insert` (al frente) | O(1) | O(1) |
| `insertBack` (al final) | O(1) | O(1) |
| `remove` (del frente) | O(1) | O(1) |
| `removeBack` (del final) | O(n) | O(1) |
| `getFront` / `getBack` | O(1) | O(1) |
| `next` | O(1) | O(1) |
| `previous` | O(n) | O(1) |
| `getSize` | O(1) | O(1) |
| `clear` | O(n) | O(n) |
| `print` | O(n) | O(n) |

## Conceptos implementados

- **Tipo abstracto de datos (TAD)**: `CList` define *qué* operaciones tiene una lista circular; cada implementación define *cómo*
- **Listas circulares**: El último nodo apunta al primero, por lo que no existe `nullptr` al final y el recorrido nunca se termina por sí solo
- **Plantillas (templates)**: `CList<E>`, `CircleList<E>`, `DCircleList<E>`, `Node<E>` y `DNode<E>`
- **Herencia y polimorfismo**: `main` usa un `CList<Person>*` y el mismo código funciona con cualquiera de las dos implementaciones; la elegida se decide en tiempo de ejecución
- **Destructor virtual**: Permite liberar la lista correctamente a través de un puntero a la clase base
- **Memoria dinámica**: Nodos creados y liberados uno por uno
- **Un solo puntero de acceso**: Con solo `current` se obtienen el frente (`current->next`) y el final (`current`) en O(1)
- **Sobrecarga de operadores**: `operator<<` para `Person`
- **Manejo de excepciones**: `throw runtime_error` y `try/catch`
- **Encapsulamiento**: Atributos privados en las listas (`current` y `size`)
- **Problema de Flavio Josefo**: Eliminación por conteo en un círculo hasta que queda una persona

## Requisitos técnicos
- Compilador de C++ con soporte para C++11 o superior
- IDE: Visual Studio, Code::Blocks, CLion o Visual Studio Code, o `g++` por terminal

## Estructura del proyecto

```
ZapatitoCochinito/
├── main.cpp           - Programa principal (menús, nombres y lógica del juego)
├── Person.h           - Jugador (nombre y pie que usa)
├── CList.h            - Clase abstracta de las listas circulares
├── CircleList.h       - Lista circular simplemente enlazada
├── DCircleList.h      - Lista circular doblemente enlazada
├── Node.h             - Nodo de lista simple
└── DNode.h            - Nodo de lista doble
```

Todos los archivos están en la misma carpeta. Como las listas y los nodos son plantillas, su código completo está en los `.h`; el único archivo `.cpp` es `main.cpp`.

## Compilación y ejecución

### Por terminal (g++):
```bash
g++ -std=c++11 -o zapatito main.cpp
./zapatito
```

### En Visual Studio:
1. Crear un proyecto de aplicación de consola vacío.
2. Agregar `main.cpp` a los archivos de código fuente y los `.h` a los archivos de encabezado.
3. Ejecutar con `Ctrl + F5`.

## Ejemplo de ejecución

Juego regular con 3 personas, nombres automáticos y `CircleList` (con 3 personas se hacen `8 % 3 = 2` saltos por conteo):

```
Zapatito Cochinito

Cantidad de personas (2 a 50): 3

Como desea asignar los nombres?
1. Automaticamente (lista predeterminada)
2. Ingresarlos manualmente
Opcion: 1

Elija el tipo de lista a utilizar:
1. CircleList
2. DCircleList
Opcion: 1

Elija el modo de juego:
1. Regular (los conteos siempre van hacia la izquierda)
2. Dirigido (usted elige la direccion de cada conteo)
Opcion: 1


 ——————————————————————— Conteo 1 ———————————————————————
Personas en el circulo: 3
Direccion: izquierda (sentido del reloj)
El conteo inicia en: Isabel
Circulo (desde donde inicia el conteo):
[Isabel (pie derecho), Eugenia (pie derecho), Mario (pie derecho)]
La ultima silaba ("to") cae en: Mario
>> Mario cambia a su pie izquierdo.
Resultado despues del conteo:
[Mario (pie izquierdo), Isabel (pie derecho), Eugenia (pie derecho)]

 ——————————————————————— Conteo 2 ———————————————————————
Personas en el circulo: 3
Direccion: izquierda (sentido del reloj)
El conteo inicia en: Isabel
Circulo (desde donde inicia el conteo):
[Isabel (pie derecho), Eugenia (pie derecho), Mario (pie izquierdo)]
La ultima silaba ("to") cae en: Mario

——————————————————————————————————————————————
      Mario SALE DEL CIRCULO (eliminado/a)
——————————————————————————————————————————————
Resultado despues del conteo:
[Isabel (pie derecho), Eugenia (pie derecho)]

...

 ——————————————————————— Conteo 5 ———————————————————————
Personas en el circulo: 2
Direccion: izquierda (sentido del reloj)
El conteo inicia en: Isabel
Circulo (desde donde inicia el conteo):
[Isabel (pie izquierdo), Eugenia (pie izquierdo)]
La ultima silaba ("to") cae en: Isabel

——————————————————————————————————————————————
      Isabel SALE DEL CIRCULO (eliminado/a)
——————————————————————————————————————————————
Resultado despues del conteo:
[Eugenia (pie izquierdo)]

——————————————————————————————————————————————
La persona elegida es: Eugenia
——————————————————————————————————————————————
```

En modo dirigido, antes de cada conteo se muestra:

```
Direccion del siguiente conteo:
1. Izquierda (sentido de las manecillas del reloj)
2. Derecha (sentido contrario a las manecillas del reloj)
Opcion: 
```

Ejemplos de mensajes de error:

```
Error: Ingrese un numero valido.
Error: La opcion debe estar entre 2 y 50.
Error: La opcion debe estar entre 1 y 2.
Error fatal: Error, Circle list is empty.
```

---

# DIAGRAMAS

## Jerarquía de clases

```
                    ┌──────────────────────┐
                    │ CList<E>             │
                    │ <<abstract>>         │
                    └──────────┬───────────┘
                               │
               ┌───────────────┴───────────────┐
               │                               │
     ┌─────────▼────────┐            ┌─────────▼────────┐
     │ CircleList<E>    │            │ DCircleList<E>   │
     │ circular simple  │            │ circular doble   │
     └─────────┬────────┘            └─────────┬────────┘
               │ usa                           │ usa
     ┌─────────▼────────┐            ┌─────────▼────────┐
     │ Node<E>          │            │ DNode<E>         │
     └──────────────────┘            └──────────────────┘
```

## Asociaciones

```
main (1) ──── list (1) ──── CList<Person>*
        Apunta a un CircleList o a un DCircleList, según la opción elegida

main (1) ──── defaultNames (50) ──── string

CList<Person> (1) ──── elementos (0..*) ──── Person
CircleList<E> (1) ──── current ──── Node<E>      (nodo anterior al frente)
DCircleList<E> (1) ──── current ──── DNode<E>    (nodo anterior al frente)
```

---

# DIAGRAMA DE CLASES COMPLETO

```
╔════════════════════════════════════════════════════════╗
║ <<abstract>> CLIST<E>                                  ║
╠════════════════════════════════════════════════════════╣
║ Constructores:                                         ║
║ + CList()                                              ║
║ + CList(const CList<E>&) = delete                      ║
║ + ~CList() (virtual)                                   ║
╠════════════════════════════════════════════════════════╣
║ Operadores:                                            ║
║ + operator=(const CList<E>&) = delete                  ║
╠════════════════════════════════════════════════════════╣
║ Métodos (virtuales puros):                             ║
║ + insert(element: E): void                             ║
║ + insertBack(element: E): void                         ║
║ + remove(): E                                          ║
║ + removeBack(): E                                      ║
║ + clear(): void                                        ║
║ + getFront(): E                                        ║
║ + getBack(): E                                         ║
║ + next(): void                                         ║
║ + previous(): void                                     ║
║ + getSize(): int                                       ║
║ + print(): void                                        ║
╚════════════════════════════════════════════════════════╝

╔════════════════════════════════════════════════════════╗
║ CIRCLELIST<E>                         (extends CList<E>)║
╠════════════════════════════════════════════════════════╣
║ Atributos:                                             ║
║ - current: Node<E>*  (nodo ANTERIOR al frente)         ║
║ - size: int                                            ║
╠════════════════════════════════════════════════════════╣
║ Constructores:                                         ║
║ + CircleList()                                         ║
║ + ~CircleList()                                        ║
╠════════════════════════════════════════════════════════╣
║ Métodos:                                               ║
║ + (implementa todos los métodos de CList<E>)           ║
╚════════════════════════════════════════════════════════╝

╔════════════════════════════════════════════════════════╗
║ DCIRCLELIST<E>                        (extends CList<E>)║
╠════════════════════════════════════════════════════════╣
║ Atributos:                                             ║
║ - current: DNode<E>*  (nodo ANTERIOR al frente)        ║
║ - size: int                                            ║
╠════════════════════════════════════════════════════════╣
║ Constructores:                                         ║
║ + DCircleList()                                        ║
║ + ~DCircleList()                                       ║
╠════════════════════════════════════════════════════════╣
║ Métodos:                                               ║
║ + (implementa todos los métodos de CList<E>)           ║
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
║ DNODE<E>                                               ║
╠════════════════════════════════════════════════════════╣
║ Atributos:                                             ║
║ + element: E                                           ║
║ + next: DNode<E>*                                      ║
║ + previous: DNode<E>*                                  ║
╠════════════════════════════════════════════════════════╣
║ Constructores:                                         ║
║ + DNode(element: E, next: DNode<E>*,                   ║
║   previous: DNode<E>*)                                 ║
║ + DNode(next: DNode<E>*, previous: DNode<E>*)          ║
║   (centinela)                                          ║
╚════════════════════════════════════════════════════════╝

╔════════════════════════════════════════════════════════╗
║ PERSON                                                 ║
╠════════════════════════════════════════════════════════╣
║ Atributos:                                             ║
║ + name: string                                         ║
║ + leftFoot: bool  (false = derecho, true = izquierdo)  ║
╠════════════════════════════════════════════════════════╣
║ Constructores:                                         ║
║ + Person()                                             ║
║ + Person(name: string)                                 ║
╠════════════════════════════════════════════════════════╣
║ Funciones asociadas:                                   ║
║ + operator<<(out: ostream&, person: const Person&):    ║
║   ostream&   (función inline, no es friend)            ║
╚════════════════════════════════════════════════════════╝

╔════════════════════════════════════════════════════════╗
║ MAIN (programa principal)                              ║
╠════════════════════════════════════════════════════════╣
║ Constantes y variables globales:                       ║
║ JUMPS: int = 8                                         ║
║ LEFT: int = 1                                          ║
║ RIGHT: int = 2                                         ║
║ DEFAULT_NAMES_COUNT: int = 50                          ║
║ defaultNames: string[50]                               ║
╠════════════════════════════════════════════════════════╣
║ Funciones:                                             ║
║ clearInput(): void                                     ║
║ getValidInput(minValue: int, maxValue: int): int       ║
║ askDirection(): int                                    ║
║ fillList(list: CList<Person>*, amount: int,            ║
║   nameMode: int): void                                 ║
║ main(): int                                            ║
╚════════════════════════════════════════════════════════╝
```

## Asociaciones y multiplicidades

```
main ────────────────────────────── CList<Person>
1                                   1
(main crea la lista y la libera con delete al terminar)

CList<Person> ───────────────────── Person
1                                   0..*

CircleList ──────────────────────── Node
1                                   0..*  (sin nodo centinela)

DCircleList ─────────────────────── DNode
1                                   0..*  (sin nodos centinela)
```

---

## Características implementadas

### Polimorfismo
- `main` solo conoce la interfaz `CList<Person>`: el código del juego (`insert`, `remove`, `next`, `previous`, `print`) es el mismo para las dos implementaciones
- Para cambiar de lista basta con cambiar el objeto que se crea según la opción del usuario

### Lista circular con un solo puntero
- Con solo `current` (apuntando al último nodo) se accede al frente y al final en O(1)
- `insert` e `insertBack` comparten código: `insertBack` inserta al frente y luego avanza `current` para que el nuevo nodo pase a ser el final

### Memoria dinámica
- Cada lista libera sus nodos en el destructor mediante `clear()`
- `main` libera la lista al terminar el juego y también cuando ocurre un error fatal

### Validación y manejo de errores
- Lectura segura de enteros con rango (`cin.clear()` y `cin.ignore()`)
- Los errores de las listas se capturan con `try/catch` en `main`

### Salida por consola
- Cada conteo muestra su número, la cantidad de personas, la dirección, dónde inicia, el círculo completo antes del conteo y el resultado después de él
- Las personas se muestran con su pie actual, por ejemplo `Mario (pie izquierdo)`

## Notas importantes
- Los mensajes del programa están en español y sin tildes; los separadores usan el carácter `—`, por lo que la consola debe soportar UTF-8 para verlos bien.
- Los nombres predeterminados se asignan en orden; si la cantidad de personas fuera mayor que 50 se usaría `Persona N`, pero el programa limita la cantidad a 50.
- Las listas circulares no usan nodos centinela, por lo que los constructores sin elemento de `Node` y `DNode` están disponibles pero no se utilizan en esta tarea.
- `removeBack()` y `previous()` de `CircleList` recorren la lista completa en el peor caso; en `DCircleList` son inmediatos gracias al puntero `previous` de cada nodo. El juego solo usa `next()`, `previous()`, `insert()` y `remove()`, y `remove()` e `insert()` son O(1) en ambas.
- Cuando el círculo tiene `n` personas se hacen `8 % n` saltos; si `n` divide a 8 (n = 2, 4 u 8) el resultado es 0 saltos y la última sílaba cae en la persona donde inicia el conteo, lo cual es equivalente a dar vueltas completas al círculo.
- `list->remove()` y `list->insert()` se usan juntos para cambiar el pie de una persona: se saca, se modifica la copia y se vuelve a insertar al frente.
- Los datos no se guardan en disco: al cerrar el programa se pierde el estado del juego.
- Se siguieron las convenciones de nomenclatura de C++ y se incluyó el encabezado con los datos del autor en todos los archivos.

## Autor
Owel Jafet Gutiérrez Ortiz

## Carnet
2026800869

## Profesor
Mauricio Avilés Cisneros

## Fecha de entrega
29/09/2026

## Institución
Instituto Tecnológico de Costa Rica
Escuela de Computación
Bachillerato en Ingeniería en Computación
