# Proyecto 0 - Juegos de Solitario

## Descripción
Este proyecto consiste en un sistema de consola en C++ con dos juegos de solitario con cartas, **Golf** y **Spider**, construido con las estructuras de datos del curso (listas, pilas y mazos propios, sin usar la biblioteca estándar de contenedores). Los dos juegos heredan de una misma clase abstracta (`Game`) que administra las **columnas de cartas** (listas enlazadas), el **mazo** (`stock`) y los historiales de **deshacer y rehacer**, que guardan objetos `Action`. El programa principal crea el juego elegido como un `Game*` y repite sus rondas mientras el jugador quiera continuar. El programa permite:
- Elegir entre **Golf**, **Spider** o salir
- Jugar rondas seguidas del mismo juego (`init`, `play` y `end`) sin volver a abrir el programa
- En Spider, mover secuencias de cartas entre columnas, repartir cartas del mazo, **deshacer** y **rehacer** jugadas
- Ver el tablero, las secuencias completadas y el puntaje después de cada jugada
- Validar las entradas del usuario e informar los errores sin que el programa se cierre inesperadamente

> Los mensajes que muestra el programa están en español.

## Requisitos del problema

### Card
- Representa una carta con un **rango** de 1 a 13 (1 = A, 11 = J, 12 = Q, 13 = K) y un estado **boca arriba o boca abajo**; no tiene palo
- Constructor por defecto: As boca arriba; el constructor con rango lanza error si el rango no está entre 1 y 13
- **Comparar**: `sameRank(other)` (mismo rango), `isAdjacentRank(other)` (rangos que difieren en 1; la K y el A también cuentan como adyacentes) e `isBiggerAdjacentRank(other)` (la otra carta es exactamente un rango mayor)
- **Estado**: `isFaceUp()`, `setFaceUp(v)` y `flip()`
- `operator<<` imprime la carta como `A`, `2` a `10`, `J`, `Q`, `K`, o `?` si está boca abajo

### Deck
- Mazo formado por una o más barajas de 52 cartas (4 veces cada rango, por baraja), guardadas en un `ArrayList<Card>`
- **shuffle()**: Mezcla con el algoritmo de Fisher-Yates
- **draw()**: Saca y retorna la carta del final del mazo; error si está vacío
- **putBack(c)**: Devuelve una carta al final del mazo (se usa al deshacer jugadas)
- **reset()**: Vuelve a llenar el mazo en orden para una nueva ronda
- **isEmpty()** y **getSize()**
- El constructor lanza error si la cantidad de barajas no es mayor que cero

### Action (clase abstracta)
- Base de las acciones que se pueden deshacer y rehacer: define `doAction(Game&)` y `undoAction(Game&)`
- Constructor de copia y operador de asignación eliminados (cada acción es única); destructor virtual
- Cada acción concreta guarda lo necesario para poder revertirse (qué cartas se voltearon, qué secuencias se retiraron)

### Game (clase abstracta)
- Guarda las columnas (`LinkedList<Card>*`, un arreglo dinámico con una lista por columna), el `stock` (un `Deck`) y los historiales de deshacer (`ArrayList<Action*>`) y rehacer (`ArrayStack<Action*>`)
- **Métodos abstractos**: `init()` (prepara una ronda), `play()` (ciclo de juego), `end()` (mensaje final) y `drawFromStock()`
- **executeAction(action)**: borra el historial de rehacer, ejecuta la acción con `doAction` y la guarda en el historial de deshacer; si el historial está lleno, elimina la acción más antigua
- **undo()** y **redo()**: Revierten o repiten la última acción y la pasan de un historial al otro; si no hay nada, lo informan
- **clearUndoHistory()** y **clearRedoHistory()**: Liberan la memoria de las acciones guardadas
- **printColumns()**: Imprime las columnas como una cuadrícula (`C1`, `C2`, ...), una fila de cartas por línea
- **printGameState()**: Método virtual que imprime el tablero; cada juego lo redefine
- Destructor virtual que libera los historiales y las columnas

### SpiderGame
- Spider de **un solo palo** con **2 mazos (104 cartas)** y **10 columnas**; historial de deshacer de **50** acciones
- Implementa `init`, `play`, `end`, `drawFromStock` y `printGameState`; además `moveSequence(from, pos, to)` e `isWon()`
- Contiene los contadores de la partida: número de ronda (`numRound`), secuencias completadas (`completed`) y movimientos (`moves`)
- Métodos auxiliares públicos que usan las acciones: `colSize`, `takeFromStock`, `returnToStock`, `takeFromColumn`, `returnToColumn`, `topIsFaceDown`, `flipTop`, `hasCompleteSequence`, `removeSequence`, `restoreSequence` y `addMoves`
- Métodos privados: `cardAt(col, idx)` e `isMovableSequence(col, idx)`

### SpiderMoveAction
- Acción que mueve una secuencia de cartas de una columna a otra
- Al ejecutarse: traslada las cartas (con una pila auxiliar para mantener el orden), voltea la carta que queda descubierta en la columna origen, retira la secuencia K..A si se completa en el destino (y voltea la carta que ese retiro descubre) y suma un movimiento
- Al deshacerse: restaura la secuencia retirada, vuelve a ocultar las cartas que se habían volteado, regresa las cartas a la columna origen y resta un movimiento

### SpiderDealAction
- Acción que reparte **una carta del mazo en cada una de las 10 columnas** y retira las secuencias completas que resulten
- Guarda en cuáles columnas se completó una secuencia para poder deshacer el reparto: restaura las secuencias y devuelve las cartas al mazo en el orden inverso

### GolfGame
- Implementación del solitario Golf; hereda de `Game` e implementa sus cuatro métodos abstractos (`src/golf/GolfGame.h`)
<!-- PENDIENTE: completar con las reglas, atributos y métodos propios de GolfGame (no se recibieron sus archivos) -->

### List, ArrayList, LinkedList y Node
- `List<E>`: clase abstracta con el TDA lista, con una **posición actual** (cursor): `insert`, `append`, `setElement`, `remove`, `clear`, `getElement`, `goToStart`, `goToEnd`, `goToPos`, `next`, `previous`, `atEnd`, `atStart`, `getPos`, `getSize` y `print`
- `ArrayList<E>`: arreglo dinámico de **tamaño máximo fijo**; `pos == size` significa que no hay elemento actual; además tiene `swapElements(i, j)` (lo usa el mezclado del mazo)
- `LinkedList<E>`: lista enlazada simple con **nodo cabecera**, puntero al último nodo (`tail`) y un puntero `current` al nodo **anterior** al elemento actual
- `Node<E>`: nodo de lista simple (`elem` y `next`), con constructor sin elemento para la cabecera

### Stack y ArrayStack
- `Stack<E>`: clase abstracta del TDA pila: `push`, `pop`, `topValue`, `clear`, `isEmpty`, `getSize` y `print`
- `ArrayStack<E>`: pila con arreglo dinámico que **duplica su capacidad** cuando se llena; `pop` y `topValue` lanzan error si la pila está vacía

### main (programa principal)
- Muestra el menú principal, valida la opción, crea el juego (`GolfGame` o `SpiderGame`) como un `Game*` y ejecuta `init()`, `play()` y `end()` mientras el jugador quiera jugar de nuevo
- Inicializa la semilla de los números aleatorios una sola vez con `srand(time(nullptr))`
- Captura cualquier excepción (`exception`) que lancen las clases del juego, la muestra y termina con código 1

## Menú principal

| Opción | Acción |
|--------|--------|
| 1 | Jugar Golf |
| 2 | Jugar Spider |
| 3 | Salir |

Al terminar cada ronda se pregunta `¿Jugar de nuevo? (s/n)`; con `s` o `S` se vuelve a ejecutar `init()` y se juega otra ronda del mismo juego, con cualquier otra tecla se vuelve al menú principal.

## Solitario Spider

### Tablero y objetivo
- Se usan 2 mazos (104 cartas) de un solo palo y hay **10 columnas** (`C1` a `C10`)
- Al iniciar se reparten **54 cartas**: 4 columnas de 6 cartas y 6 columnas de 5 cartas. En cada columna **solo la última carta está boca arriba**
- Las 50 cartas restantes quedan en el mazo (`stock`) y se reparten de a 10: **5 repartos**
- El objetivo es formar y retirar **8 secuencias completas de la K a la A** (13 cartas consecutivas, boca arriba); la partida se gana al completar las 8

### Reglas de las jugadas
- Se puede mover un bloque de cartas del final de una columna si todas están **boca arriba** y forman una **secuencia descendente consecutiva** (por ejemplo, 7, 6, 5)
- El bloque se puede poner sobre una columna cuya última carta tenga un rango **exactamente uno mayor** que la primera carta del bloque (el 6 va sobre el 7)
- En una **columna vacía** se puede mover cualquier bloque válido
- Si al mover queda boca abajo la última carta de la columna origen, se **voltea** automáticamente
- Si al mover (o al repartir) se completa una secuencia K..A al final de una columna, esas 13 cartas se **retiran**
- **Repartir**: pone una carta del mazo en cada columna; solo se puede si quedan al menos 10 cartas en el mazo y **ninguna columna está vacía**
- La K y el A no son adyacentes para mover cartas: solo cuentan como secuencia las cartas que bajan de uno en uno

### Puntaje
`puntos = 500 - movimientos + 100 × secuencias completadas`

Cada movimiento de cartas y cada reparto suma un movimiento; deshacer resta uno.

### Comandos

| Comando | Acción |
|---------|--------|
| `m <origen> <fila> <destino>` | Mueve las cartas desde la fila `<fila>` (1 = la de arriba) de la columna `<origen>` hasta el final, a la columna `<destino>` |
| `d` | Reparte una carta en cada columna |
| `u` | Deshace la última jugada |
| `r` | Rehace la última jugada deshecha |
| `q` | Termina la partida actual |

## Solitario Golf

El solitario Golf es una clase `GolfGame` que hereda de `Game` y reutiliza las mismas piezas del sistema: columnas con `LinkedList<Card>`, el mazo `Deck`, el historial de acciones para deshacer y rehacer, y la impresión de columnas de `Game::printColumns()`. Se carga y se juega desde el mismo menú principal.
<!-- PENDIENTE: agregar las reglas de Golf, sus comandos y el puntaje -->

## Deshacer y rehacer

Cada jugada de Spider es un objeto `Action` que se ejecuta con `Game::executeAction`:

```
executeAction(accion):
    redoHistory  ← se vacía (ya no se puede rehacer lo anterior)
    accion.doAction()
    undoHistory  ← accion   (si está lleno, se elimina la más antigua)

undo():   undoHistory ──(última acción)──▶ undoAction() ──▶ redoHistory
redo():   redoHistory ──(última acción)──▶ doAction()   ──▶ undoHistory

   undoHistory (ArrayList)                 redoHistory (ArrayStack)
   [ a1, a2, a3, a4 ]  ◀── última          [ a6, a5 ]  ◀── tope
```

- El historial de deshacer es una lista con **límite fijo** (50 en Spider): cuando se llena, se elimina la acción más antigua y se libera su memoria
- El de rehacer es una **pila**: la última acción deshecha es la primera en rehacerse
- Las acciones guardan lo que cambiaron (cartas volteadas, secuencias retiradas), por lo que `undoAction` deja el tablero exactamente como estaba

## Complejidad de las operaciones

Con `n` cartas en una columna y `k` cartas en el bloque que se mueve:

| Operación | Complejidad |
|-----------|-------------|
| `Deck::draw` / `putBack` | O(1) |
| `Deck::shuffle` / `reset` | O(total de cartas) |
| `Game::executeAction` / `undo` / `redo` | O(costo de la acción) (más O(historial) si hay que descartar la acción más antigua) |
| `takeFromColumn` / `flipTop` / `topIsFaceDown` | O(n) (en `LinkedList`, `previous` y `goToPos` recorren la lista) |
| `cardAt` | O(n) |
| `isMovableSequence` | O(n²) |
| `hasCompleteSequence` | O(13 · n) |
| `moveSequence` (validación y movimiento) | O(n² + k · n) |
| `printColumns` | O(filas · n) por columna |

| Operación | ArrayList | LinkedList |
|-----------|-----------|------------|
| `append` | O(1) | O(1) |
| `insert` / `remove` (en la posición actual) | O(n) | O(1) |
| `getElement` / `setElement` | O(1) | O(1) |
| `next` | O(1) | O(1) |
| `previous` | O(1) | O(n) |
| `goToStart` / `goToEnd` | O(1) | O(1) |
| `goToPos` / `getPos` | O(1) | O(n) |
| `clear` | O(1) (borrado lógico) | O(n) |

`ArrayStack`: `push` es O(1) amortizado (duplica la capacidad cuando se llena), y `pop`, `topValue`, `isEmpty`, `getSize` y `clear` son O(1).

## Reglas del negocio
- El mazo se arma con barajas completas de 52 cartas y se mezcla con Fisher-Yates al iniciar cada ronda.
- Spider usa 2 barajas (104 cartas), 10 columnas y un historial de 50 acciones.
- Solo se pueden mover cartas boca arriba que formen una secuencia descendente consecutiva.
- Para poner un bloque sobre una carta, esta debe tener un rango exactamente uno mayor que la primera del bloque.
- No se puede repartir si quedan menos de 10 cartas en el mazo ni si hay columnas vacías.
- Al repartir o mover, las secuencias K..A completas se retiran y suman 100 puntos.
- La partida se gana al completar 8 secuencias.
- Hacer una jugada nueva borra el historial de rehacer.
- Al iniciar una ronda se vacían las columnas y los historiales, y se reinician las secuencias y los movimientos.

## Reglas de validación
- La opción del menú principal debe ser 1, 2 o 3; si se escribe otra cosa (incluso letras) se muestra `Error, opción incorrecta (1, 2 o 3).` y se vuelve a mostrar el menú.
- Los comandos de Spider se leen como un carácter; si no es uno de los comandos válidos se muestra `Comando desconocido.`
- Si el comando `m` no recibe tres números se muestra el uso correcto: `Uso: m <origen> <fila> <destino>`.
- Las jugadas inválidas de Spider no cambian el tablero y muestran el motivo:

| Situación | Mensaje |
|-----------|---------|
| Columna fuera de 1 a 10 | `Error, Columna invalida (1-10).` |
| Origen y destino iguales | `Error, Origen y destino son la misma columna.` |
| Fila fuera de la columna | `Error, Posicion invalida en la columna N.` |
| Las cartas no forman una secuencia | `Error, Esas cartas no forman una secuencia descendente boca arriba.` |
| El destino no tiene rango uno mayor | `Error, Jugada ilegal: el destino debe tener una carta con rango uno mayor.` |
| Reparto con menos de 10 cartas | `Error, El stock esta vacio.` |
| Reparto con una columna vacía | `Error, No puedes repartir con columnas vacias.` |
| Deshacer sin jugadas | `Nada que deshacer.` |
| Rehacer sin jugadas deshechas | `Nada que rehacer.` |

- Los errores de las estructuras lanzan excepciones, que se capturan en `main`:

| Clase | Condición del error | Tipo |
|-------|---------------------|------|
| `Card` | Rango fuera de 1 a 13 | `runtime_error` |
| `Deck` | Cantidad de barajas menor o igual a 0; sacar de un mazo vacío | `runtime_error` |
| `Game` | Imprimir sin columnas | `runtime_error` |
| `ArrayList` | Tamaño máximo menor que 1; lista llena, vacía o sin elemento actual; posición o índice inválido | `length_error`, `overflow_error`, `underflow_error`, `range_error`, `runtime_error` |
| `ArrayStack` | Tamaño máximo menor que 1; `pop` o `topValue` con la pila vacía | `runtime_error`, `underflow_error` |
| `LinkedList` | Lista vacía o sin elemento actual; posición inválida | `underflow_error`, `runtime_error`, `out_of_range` |

## Conceptos implementados

- **Herencia y polimorfismo**: `main` usa un `Game*` y llama `init`, `play` y `end` sin saber si es Golf o Spider; las acciones se manejan como `Action*`
- **Patrón Command (acciones deshacer/rehacer)**: Cada jugada es un objeto con `doAction` y `undoAction`
- **Clases abstractas y destructores virtuales**: `Game`, `Action`, `List` y `Stack`
- **Plantillas (templates)**: `List<E>`, `ArrayList<E>`, `LinkedList<E>`, `Node<E>`, `Stack<E>` y `ArrayStack<E>`
- **Estructuras de datos propias**: Listas enlazadas para las columnas, `ArrayList` para el mazo y el historial de deshacer, `ArrayStack` para rehacer y para mover cartas conservando el orden
- **Pilas**: Historial de rehacer y pila auxiliar de `transfer` (invierte dos veces el bloque de cartas para dejarlo en el orden original)
- **Composición**: `Game` contiene el mazo, las columnas y los historiales; `Deck` contiene un `ArrayList<Card>`
- **Memoria dinámica**: Columnas, acciones y juegos creados con `new` y liberados con `delete` / `delete[]`
- **Algoritmo de Fisher-Yates**: Mezclado uniforme del mazo
- **Sobrecarga de operadores**: `operator<<` de `Card` como función amiga (`friend`)
- **Manejo de excepciones**: Jerarquía de excepciones estándar (`runtime_error`, `underflow_error`, `range_error`, ...) y `try/catch` en `main`
- **Dependencias circulares resueltas**: `Action.h` declara `class Game;` por adelantado, y `SpiderGame.h` incluye `SpiderActions.h` al final
- **Encapsulamiento**: Atributos privados o protegidos en `Card`, `Deck`, `Game`, `SpiderGame` y las estructuras

## Requisitos técnicos
- Compilador de C++ con soporte para C++11 o superior
- IDE: Visual Studio, Code::Blocks, CLion o Visual Studio Code, o `g++` por terminal
- Una consola que soporte secuencias ANSI (el menú principal usa `\033[F` para reescribir la línea de la opción)

## Estructura del proyecto

```
Solitario/
├── main/
│   └── main.cpp           - Programa principal (menú y rondas)
└── src/
    ├── core/
    │   ├── Action.h       - Clase abstracta de las acciones (deshacer/rehacer)
    │   ├── Card.h         - Carta (rango y cara)
    │   ├── Deck.h         - Mazo de una o más barajas
    │   └── Game.h         - Clase abstracta de los juegos
    ├── structures/
    │   ├── List.h         - Clase abstracta de las listas
    │   ├── ArrayList.h    - Lista con arreglo dinámico
    │   ├── LinkedList.h   - Lista enlazada simple
    │   ├── Node.h         - Nodo de lista simple
    │   ├── Stack.h        - Clase abstracta de las pilas
    │   └── ArrayStack.h   - Pila con arreglo dinámico
    ├── spider/
    │   ├── SpiderGame.h   - Juego Spider
    │   └── SpiderActions.h - Acciones de Spider (mover y repartir)
    └── golf/
        └── GolfGame.h     - Juego Golf
```

Las carpetas siguen las rutas de los `#include` del código (`../core/`, `../structures/`, `../src/spider/`). Como todas las clases son plantillas o están definidas en los `.h`, el único archivo `.cpp` es `main.cpp`.

## Compilación y ejecución

### Por terminal (g++):
```bash
g++ -std=c++11 -o solitario main/main.cpp
./solitario
```

### En Visual Studio:
1. Crear un proyecto de aplicación de consola vacío.
2. Agregar `main.cpp` a los archivos de código fuente y mantener la estructura de carpetas de `src` para los `.h`.
3. Ejecutar con `Ctrl + F5`.

## Ejemplo de ejecución

Una ronda de Spider (las cartas son aleatorias, por lo que cambian en cada ejecución; los comandos están en la línea que empieza con `>`):

```
*********************
*     SOLITARIO     *
*********************
* 1. Golf           *
* 2. Spider         *
* 3. Salir          *
*********************
* Opcion: 2         *
*********************
Comandos: m <col origen> <fila> <col destino> | d (repartir) | u | r | q
  <fila> es la fila (1 = arriba) de la primera carta a mover.

*     Spider - Ronda 1    |
C1  C2  C3  C4  C5  C6  C7  C8  C9  C10
?   ?   ?   ?   ?   ?   ?   ?   ?   ?
?   ?   ?   ?   ?   ?   ?   ?   ?   ?
?   ?   ?   ?   ?   ?   ?   ?   ?   ?
?   ?   ?   ?   ?   ?   ?   ?   ?   ?
?   ?   ?   ?   8   Q   4   J   2   6
7   3   K   9

Reparticiones restantes: 5    Secuencias: 0/8    Puntos: 500
> m 5 5 4

*     Spider - Ronda 1    |
C1  C2  C3  C4  C5  C6  C7  C8  C9  C10
?   ?   ?   ?   ?   ?   ?   ?   ?   ?
?   ?   ?   ?   ?   ?   ?   ?   ?   ?
?   ?   ?   ?   ?   ?   ?   ?   ?   ?
?   ?   ?   ?   5   ?   ?   ?   ?   ?
?   ?   ?   ?       Q   4   J   2   6
7   3   K   9
                8

Reparticiones restantes: 5    Secuencias: 0/8    Puntos: 499
> m 2 6 3
Error, Jugada ilegal: el destino debe tener una carta con rango uno mayor.

...

> q

Partida terminada. Secuencias: 0/8 * Puntos: 499
¿Jugar de nuevo? (s/n): n
*********************
*     SOLITARIO     *
*********************
* 1. Golf           *
* 2. Spider         *
* 3. Salir          *
*********************
* Opcion: 3         *
*********************
Cerrando juego...
¡Hasta pronto!
```

En el ejemplo, `m 5 5 4` mueve el 8 (fila 5 de la columna 5) sobre el 9 de la columna 4, y la carta que queda descubierta en la columna 5 se voltea. Después se muestra el tablero otra vez, aunque la jugada sea ilegal (en ese caso no cambia).

Ejemplos de otros mensajes:

```
Nada que deshacer.
Nada que rehacer.
Uso: m <origen> <fila> <destino>
Comando desconocido.
Error, opción incorrecta (1, 2 o 3).
Error: Error, Deck is empty.
```

---

# DIAGRAMAS

## Jerarquía de clases

```
Game <<abstract>>                 Action <<abstract>>
 ├── GolfGame                      ├── SpiderMoveAction
 └── SpiderGame                    └── SpiderDealAction

List<E> <<abstract>>              Stack<E> <<abstract>>
 ├── ArrayList<E>                  └── ArrayStack<E>
 └── LinkedList<E>
       └── usa Node<E>

Clases independientes: Card, Deck (usa ArrayList<Card>)
```

## Asociaciones

```
main (1) ──── game (1) ──── Game*
        Apunta a un GolfGame o a un SpiderGame, según la opción elegida

Game (1) ──── columns (columnAmount) ──── LinkedList<Card>
Game (1) ──── stock (1) ──── Deck
Game (1) ──── undoHistory (1) ──── ArrayList<Action*>
Game (1) ──── redoHistory (1) ──── ArrayStack<Action*>

Deck (1) ──── cards (1) ──── ArrayList<Card>
ArrayList<Card> (1) ──── elementos (0..*) ──── Card

SpiderMoveAction (1) ──── game (1) ──── SpiderGame*
SpiderDealAction (1) ──── game (1) ──── SpiderGame*
SpiderMoveAction ──── usa (en transfer) ──── ArrayStack<Card>

LinkedList<E> (1) ──── head, current, tail ──── Node<E>
```

---

# DIAGRAMA DE CLASES COMPLETO

```
╔════════════════════════════════════════════════════════╗
║ <<abstract>> GAME                                      ║
╠════════════════════════════════════════════════════════╣
║ Atributos (protegidos):                                ║
║ # limitHistory: static const int = 10                  ║
║ # columns: LinkedList<Card>*  (arreglo dinámico)       ║
║ # columnAmount: int                                    ║
║ # stock: Deck                                          ║
║ # maxHistory: int                                      ║
║ # undoHistory: ArrayList<Action*>                      ║
║ # redoHistory: ArrayStack<Action*>                     ║
╠════════════════════════════════════════════════════════╣
║ Constructores:                                         ║
║ # Game(amount: int, columnAmount: int,                 ║
║   maxHistory: int = limitHistory)                      ║
║ + ~Game() (virtual)                                    ║
╠════════════════════════════════════════════════════════╣
║ Métodos protegidos:                                    ║
║ # pushUndo(a: Action*): void                           ║
║ # popUndo(): Action*                                   ║
╠════════════════════════════════════════════════════════╣
║ Métodos (virtuales puros):                             ║
║ + init(): void                                         ║
║ + play(): void                                         ║
║ + end(): void                                          ║
║ + drawFromStock(): void                                ║
╠════════════════════════════════════════════════════════╣
║ Métodos:                                               ║
║ + executeAction(action: Action*): void                 ║
║ + undo(): void                                         ║
║ + redo(): void                                         ║
║ + clearUndoHistory(): void                             ║
║ + clearRedoHistory(): void                             ║
║ + printColumns(): void                                 ║
║ + printGameState(): void  (virtual)                    ║
╚════════════════════════════════════════════════════════╝

╔════════════════════════════════════════════════════════╗
║ <<abstract>> ACTION                                    ║
╠════════════════════════════════════════════════════════╣
║ Constructores:                                         ║
║ + Action()                                             ║
║ + Action(const Action&) = delete                       ║
║ + ~Action() (virtual)                                  ║
╠════════════════════════════════════════════════════════╣
║ Operadores:                                            ║
║ + operator=(const Action&) = delete                    ║
╠════════════════════════════════════════════════════════╣
║ Métodos (virtuales puros):                             ║
║ + doAction(g: Game&): void                             ║
║ + undoAction(g: Game&): void                           ║
╚════════════════════════════════════════════════════════╝

╔════════════════════════════════════════════════════════╗
║ CARD                                                   ║
╠════════════════════════════════════════════════════════╣
║ Atributos:                                             ║
║ - rank: int                                            ║
║ - faceUp: bool                                         ║
║ + maxRank: static const int = 13                       ║
╠════════════════════════════════════════════════════════╣
║ Constructores:                                         ║
║ + Card()                                               ║
║ + Card(rank: int, faceUp: bool = true)                 ║
╠════════════════════════════════════════════════════════╣
║ Métodos:                                               ║
║ + sameRank(other: const Card&): bool                   ║
║ + isAdjacentRank(other: const Card&): bool             ║
║ + isBiggerAdjacentRank(other: const Card&): bool       ║
║ + isFaceUp(): bool                                     ║
║ + setFaceUp(v: bool): void                             ║
║ + flip(): void                                         ║
║ + friend operator<<(os: ostream&, c: const Card&):     ║
║   ostream&                                             ║
╚════════════════════════════════════════════════════════╝

╔════════════════════════════════════════════════════════╗
║ DECK                                                   ║
╠════════════════════════════════════════════════════════╣
║ Atributos:                                             ║
║ - cardsInADeck: static const int = 52                  ║
║ - cards: ArrayList<Card>                               ║
║ - amount: int                                          ║
╠════════════════════════════════════════════════════════╣
║ Constructores:                                         ║
║ + Deck(amount: int)                                    ║
╠════════════════════════════════════════════════════════╣
║ Métodos privados:                                      ║
║ - validatedSize(amount: int): int  (static)            ║
║ - fill(): void                                         ║
╠════════════════════════════════════════════════════════╣
║ Métodos públicos:                                      ║
║ + reset(): void                                        ║
║ + shuffle(): void                                      ║
║ + draw(): Card                                         ║
║ + putBack(c: Card): void                               ║
║ + isEmpty(): bool                                      ║
║ + getSize(): int                                       ║
╚════════════════════════════════════════════════════════╝

╔════════════════════════════════════════════════════════╗
║ SPIDERGAME                              (extends Game) ║
╠════════════════════════════════════════════════════════╣
║ Atributos:                                             ║
║ - numColumns: static const int = 10                    ║
║ - totalSequences: static const int = 8                 ║
║ - sequenceLength: static const int = 13                ║
║ - numRound: int                                        ║
║ - completed: int                                       ║
║ - moves: int                                           ║
╠════════════════════════════════════════════════════════╣
║ Constructores:                                         ║
║ + SpiderGame()                                         ║
╠════════════════════════════════════════════════════════╣
║ Métodos privados:                                      ║
║ - cardAt(col: int, idx: int): Card                     ║
║ - isMovableSequence(col: int, idx: int): bool          ║
╠════════════════════════════════════════════════════════╣
║ Métodos (implementan los de Game):                     ║
║ + init(): void                                         ║
║ + play(): void                                         ║
║ + end(): void                                          ║
║ + drawFromStock(): void                                ║
║ + printGameState(): void                               ║
╠════════════════════════════════════════════════════════╣
║ Métodos públicos:                                      ║
║ + moveSequence(from: int, pos: int, to: int): void     ║
║ + isWon(): bool                                        ║
╠════════════════════════════════════════════════════════╣
║ Métodos auxiliares para las acciones:                  ║
║ + colSize(col: int): int                               ║
║ + takeFromStock(): Card                                ║
║ + returnToStock(c: Card): void                         ║
║ + takeFromColumn(col: int): Card                       ║
║ + returnToColumn(col: int, c: Card): void              ║
║ + topIsFaceDown(col: int): bool                        ║
║ + flipTop(col: int): void                              ║
║ + hasCompleteSequence(col: int): bool                  ║
║ + removeSequence(col: int): void                       ║
║ + restoreSequence(col: int): void                      ║
║ + addMoves(n: int): void                               ║
╚════════════════════════════════════════════════════════╝

╔════════════════════════════════════════════════════════╗
║ SPIDERMOVEACTION                      (extends Action) ║
╠════════════════════════════════════════════════════════╣
║ Atributos:                                             ║
║ - game: SpiderGame*                                    ║
║ - from: int                                            ║
║ - to: int                                              ║
║ - count: int                                           ║
║ - flipped: bool                                        ║
║ - completedSeq: bool                                   ║
║ - flippedDestination: bool                             ║
╠════════════════════════════════════════════════════════╣
║ Constructores:                                         ║
║ + SpiderMoveAction(game: SpiderGame*, from: int,       ║
║   to: int, count: int)                                 ║
╠════════════════════════════════════════════════════════╣
║ Métodos privados:                                      ║
║ - transfer(src: int, dst: int, n: int): void           ║
╠════════════════════════════════════════════════════════╣
║ Métodos:                                               ║
║ + doAction(g: Game&): void                             ║
║ + undoAction(g: Game&): void                           ║
╚════════════════════════════════════════════════════════╝

╔════════════════════════════════════════════════════════╗
║ SPIDERDEALACTION                      (extends Action) ║
╠════════════════════════════════════════════════════════╣
║ Atributos:                                             ║
║ - game: SpiderGame*                                    ║
║ - completedCol: bool[10]                               ║
╠════════════════════════════════════════════════════════╣
║ Constructores:                                         ║
║ + SpiderDealAction(game: SpiderGame*)                  ║
╠════════════════════════════════════════════════════════╣
║ Métodos:                                               ║
║ + doAction(g: Game&): void                             ║
║ + undoAction(g: Game&): void                           ║
╚════════════════════════════════════════════════════════╝

╔════════════════════════════════════════════════════════╗
║ GOLFGAME                                (extends Game) ║
╠════════════════════════════════════════════════════════╣
║ Métodos (implementan los de Game):                     ║
║ + init(): void                                         ║
║ + play(): void                                         ║
║ + end(): void                                          ║
║ + drawFromStock(): void                                ║
╚════════════════════════════════════════════════════════╝

╔════════════════════════════════════════════════════════╗
║ <<abstract>> LIST<E>                                   ║
╠════════════════════════════════════════════════════════╣
║ Constructores:                                         ║
║ + List()                                               ║
║ + List(const List<E>&) = delete                        ║
║ + ~List() (virtual)                                    ║
╠════════════════════════════════════════════════════════╣
║ Operadores:                                            ║
║ + operator=(const List<E>&) = delete                   ║
╠════════════════════════════════════════════════════════╣
║ Métodos (virtuales puros):                             ║
║ + insert(elem: E): void                                ║
║ + append(elem: E): void                                ║
║ + setElement(elem: E): void                            ║
║ + remove(): E                                          ║
║ + clear(): void                                        ║
║ + getElement(): E                                      ║
║ + goToStart(): void                                    ║
║ + goToEnd(): void                                      ║
║ + goToPos(pos: int): void                              ║
║ + next(): void                                         ║
║ + previous(): void                                     ║
║ + atEnd(): bool                                        ║
║ + atStart(): bool                                      ║
║ + getPos(): int                                        ║
║ + getSize(): int                                       ║
║ + print(): void                                        ║
╚════════════════════════════════════════════════════════╝

╔════════════════════════════════════════════════════════╗
║ ARRAYLIST<E>                        (extends List<E>)  ║
╠════════════════════════════════════════════════════════╣
║ Atributos:                                             ║
║ - elements: E*                                         ║
║ - max: int                                             ║
║ - size: int                                            ║
║ - pos: int                                             ║
╠════════════════════════════════════════════════════════╣
║ Constructores:                                         ║
║ + ArrayList(max: int)                                  ║
║ + ~ArrayList()                                         ║
╠════════════════════════════════════════════════════════╣
║ Métodos privados:                                      ║
║ - ValidatePos(): void                                  ║
║ - ValidateIdx(idx: int): void                          ║
╠════════════════════════════════════════════════════════╣
║ Métodos:                                               ║
║ + (implementa todos los métodos de List<E>)            ║
║ + swapElements(i: int, j: int): void                   ║
╚════════════════════════════════════════════════════════╝

╔════════════════════════════════════════════════════════╗
║ LINKEDLIST<E>                       (extends List<E>)  ║
╠════════════════════════════════════════════════════════╣
║ Atributos:                                             ║
║ - head: Node<E>*  (cabecera)                           ║
║ - current: Node<E>*                                    ║
║ - tail: Node<E>*                                       ║
║ - size: int                                            ║
╠════════════════════════════════════════════════════════╣
║ Constructores:                                         ║
║ + LinkedList()                                         ║
║ + ~LinkedList()                                        ║
╠════════════════════════════════════════════════════════╣
║ Métodos privados:                                      ║
║ - ActualFront(): Node<E>*&                             ║
║ - ActualCurrent(): Node<E>*&                           ║
║ - ValidateList(): void                                 ║
╠════════════════════════════════════════════════════════╣
║ Métodos:                                               ║
║ + (implementa todos los métodos de List<E>)            ║
╚════════════════════════════════════════════════════════╝

╔════════════════════════════════════════════════════════╗
║ NODE<E>                                                ║
╠════════════════════════════════════════════════════════╣
║ Atributos:                                             ║
║ + elem: E                                              ║
║ + next: Node<E>*                                       ║
╠════════════════════════════════════════════════════════╣
║ Constructores:                                         ║
║ + Node()                                               ║
║ + Node(elem: E, next: Node<E>* = nullptr)              ║
╚════════════════════════════════════════════════════════╝

╔════════════════════════════════════════════════════════╗
║ <<abstract>> STACK<E>                                  ║
╠════════════════════════════════════════════════════════╣
║ Constructores:                                         ║
║ + Stack()                                              ║
║ + Stack(const Stack<E>&) = delete                      ║
║ + ~Stack() (virtual)                                   ║
╠════════════════════════════════════════════════════════╣
║ Operadores:                                            ║
║ + operator=(const Stack<E>&) = delete                  ║
╠════════════════════════════════════════════════════════╣
║ Métodos (virtuales puros):                             ║
║ + push(newElement: E): void                            ║
║ + pop(): E                                             ║
║ + topValue(): E                                        ║
║ + clear(): void                                        ║
║ + isEmpty(): bool                                      ║
║ + getSize(): int                                       ║
║ + print(): void                                        ║
╚════════════════════════════════════════════════════════╝

╔════════════════════════════════════════════════════════╗
║ ARRAYSTACK<E>                       (extends Stack<E>) ║
╠════════════════════════════════════════════════════════╣
║ Atributos:                                             ║
║ - elements: E*                                         ║
║ - max: int                                             ║
║ - size: int                                            ║
╠════════════════════════════════════════════════════════╣
║ Constructores:                                         ║
║ + ArrayStack(max: int)                                 ║
║ + ~ArrayStack()                                        ║
╠════════════════════════════════════════════════════════╣
║ Métodos:                                               ║
║ + (implementa todos los métodos de Stack<E>)           ║
╚════════════════════════════════════════════════════════╝

╔════════════════════════════════════════════════════════╗
║ MAIN (programa principal)                              ║
╠════════════════════════════════════════════════════════╣
║ Variables locales principales:                         ║
║ option: int                                            ║
║ game: Game*                                            ║
║ again: char                                            ║
╠════════════════════════════════════════════════════════╣
║ Funciones:                                             ║
║ clearLine(): void                                      ║
║ main(): int                                            ║
╚════════════════════════════════════════════════════════╝
```
<!-- PENDIENTE: completar el recuadro de GOLFGAME con sus atributos y métodos propios -->

## Asociaciones y multiplicidades

```
main ────────────────────────────── Game
1                                   1
(main crea el juego con new y lo libera con delete)

Game ────────────────────────────── LinkedList<Card>
1                                   columnAmount  (Spider: 10)

Game ────────────────────────────── Deck
1                                   1
(Composición: el juego contiene su mazo)

Game ────────────────────────────── Action
1                                   0..*  (undoHistory hasta 50 en Spider, más las de redoHistory)
(El juego libera con delete las acciones que guardan los historiales)

Deck ────────────────────────────── Card
1                                   52 · baraja(s)

SpiderMoveAction / SpiderDealAction ─ SpiderGame
1                                   1

LinkedList ──────────────────────── Node
1                                   0..*  (más el nodo cabecera)
```

---

## Características implementadas

### Polimorfismo
- `main` solo conoce la interfaz `Game`: el ciclo `init`, `play`, `end` es el mismo para Golf y Spider
- `Game` solo conoce la interfaz `Action`: ejecutar, deshacer y rehacer funciona igual para cualquier acción

### Deshacer y rehacer
- Las acciones guardan lo que modificaron, de modo que `undoAction` deja el tablero idéntico: cartas volteadas, secuencias retiradas, cartas devueltas al mazo y contador de movimientos
- El historial de deshacer es limitado y descarta lo más antiguo; el de rehacer se borra al hacer una jugada nueva

### Spider
- Validación completa de las jugadas antes de crear la acción: columnas, posición, secuencia boca arriba y rango del destino
- Volteo automático de la carta descubierta y retiro automático de las secuencias K..A, también al repartir
- Puntaje en tiempo real según movimientos y secuencias completadas

### Memoria dinámica
- Las columnas son un arreglo de `LinkedList<Card>` creado con `new[]` y liberado en el destructor de `Game`
- Cada acción se crea con `new`; `Game` la libera al descartarla del historial, al limpiar los historiales y en el destructor
- `main` libera el juego con `delete` al terminar de jugar

### Validación y manejo de errores
- Lectura segura del menú y de los comandos (`cin.fail()`, `cin.clear()`, `cin.ignore()` y detección de fin de entrada con `cin.eof()`)
- Las jugadas inválidas se informan sin modificar el tablero, y los errores de las estructuras se capturan con `try/catch` en `main`

### Salida por consola
- El tablero se muestra como una cuadrícula de columnas, con `?` para las cartas boca abajo, y debajo las reparticiones restantes, las secuencias y los puntos

## Notas importantes
- Los mensajes del programa están en español; los de las excepciones de las estructuras, en inglés.
- Las cartas no tienen palo: Spider es de un solo palo, y un mazo de 52 cartas tiene 4 cartas de cada rango.
- El número de fila del comando `m` cuenta desde arriba del tablero (la primera carta de la columna es la fila 1), no desde la última carta.
- `SpiderDealAction` retira las secuencias completas que resulten del reparto, pero a diferencia de `SpiderMoveAction` no voltea la carta que queda descubierta después de retirarlas; si esa carta estaba boca abajo, sigue boca abajo hasta que se mueva otro bloque sobre ella y se vuelva a descubrir.
- Los puntos se calculan como `500 - movimientos + 100 × secuencias`, por lo que con más de 500 movimientos pueden ser negativos.
- Las operaciones de `LinkedList` que usan la posición (`goToPos`, `previous`, `getPos`) recorren la lista; con columnas de pocas decenas de cartas no es un problema.
- `ArrayList` tiene capacidad máxima fija: el mazo tiene la capacidad de todas sus cartas y el historial de deshacer la de su límite, por lo que nunca se llenan durante el juego.
- Los métodos de `SpiderGame` que crean las acciones (`drawFromStock`, `moveSequence`) están definidos en `SpiderActions.h`, que `SpiderGame.h` incluye al final para resolver la dependencia circular; como esos métodos no son plantillas, estos archivos solo deben incluirse desde un único `.cpp` (aquí, `main.cpp`).
- El menú principal usa la secuencia `\033[F` y `\r` para reescribir la línea de la opción, por lo que requiere una consola con soporte ANSI.
- Si ocurre una excepción en `main`, el programa termina con código 1 sin liberar el juego que estaba en curso (el sistema operativo libera la memoria al cerrar).
- Los datos no se guardan en disco: al cerrar el programa se pierde la partida.
- Se siguieron las convenciones de nomenclatura de C++ y se incluyó el encabezado con los datos de los integrantes en todos los archivos.

## Integrantes

| Nombre | Carnet |
|--------|--------|
| Owel Jafet Gutiérrez Ortiz | 2026800869 |
| Miranda Jiménez Alvarado | 2026008616 |
| Keishiro Gabriel Cubero Abe | 2026091245 |
| Eduardo Alfonso Moreno Pérez | 2025080891 |

## Profesor
Mauricio Avilés Cisneros

## Fecha de entrega
26/10/2026

## Institución
Instituto Tecnológico de Costa Rica
Escuela de Computación
Bachillerato en Ingeniería en Computación
