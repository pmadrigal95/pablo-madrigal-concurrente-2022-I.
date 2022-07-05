# Design

## Idea General del Proceso

Lluvia de ideas, de como se podria abarcar el problema y como se podria resolver de manera serial

![Idea General del Proceso](ideas.PNG)

Lluvia de ideas, de como se podria abarcar el problema y como se podria resolver con pthreads

![Idea General del Proceso2](newIdeas.PNG)

## Diagrama UML

Structs utilizados en la tarea

![Diagrama UML](UML.jpeg)

![Diagrama UML2](newStructures.jpeg)

## Diagrama de Flujo

### Diagrama Principal

Flujo del archivo main

![Diagrama Principal](main.jpeg)

### Diagrama de File Utility

Flujo del archivo file_utility, este archivo contiene toda la logica relacionada con el manejo de ficheros y setear los valores 

![Diagrama de File Utility](file_utility.jpeg)

### Diagrama Game Logic

Flujo del archivo game_logic, este archivo contiene toda la logica relacionada con el manejo del juego (colocar la pieza, realizar intentos, etc..) de manera serial

![Diagrama Game Logic](game_logic.jpeg)

Flujo del archivo game_logic, este archivo contiene toda la logica relacionada con el manejo del juego (colocar la pieza, realizar intentos, etc..)  con Pthreads

![Diagrama Game Logic2](newDiagrama.jpeg)


Cabe mencionar que también se realizaron pruebas en otros lenguajes de programación por ejemplo C#, adjunto la lógica referente al colocar una figura en el tablero de juego.