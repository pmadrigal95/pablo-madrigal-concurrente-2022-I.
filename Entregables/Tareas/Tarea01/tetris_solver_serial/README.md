# Análisis

## Descripción del problema

Tetris es un video juego tradicional en el cual se tiene un área de juego que cosiste en una cuadrícula de tamaño NxM (comúnmente se utiliza 20x10). Hay siete figuras geométricas diferentes, conocidas como *tetriminós* que están compuestas por cuatro bloques cuadrados unidos entre sí. Durante una partida de tetris, se van generando figuras de forma aleatoria, una por una, desde la parte superior del área de juego y éstas van cayendo hacia la parte inferior. La siguiente figura no se genera hasta que la actual figura no haya caido completamente.

Los jugadores pueden decidir la rotación de la pieza (0°, 90°, 180°, 270°) y en qué lugar debe caer. Cuando una línea horizontal se completa, esa línea desaparece y todas las piezas que están por encima descienden una posición, liberando espacio de juego y por tanto facilitando la tarea de situar nuevas piezas. Cada línea completa le da cierta cantidad de puntos al jugador, dependiendo del nivel y cuántas líneas se completaron en *combo*. El jugador también puede ver cuáles serán las siguientes K figuras (comúnmente seis figuras) y planear la posición basándose en las mismas.

Cuando las piezas se amontonan y colisionan con la parte superior del tablero, el juego se termina.

En esta tarea se creará un solucionador de tetris utilizando el lenguage de programación C que determinará la mejor posición y la rotación de una figura de tetris en un momento dado. El programa recibe un estado de juego de tetris en un archivo con el siguiente formato:

- La línea 1 contiene un número que representa un identificador del estado del juego.
- La línea 2 contiene un número entero que representa la **profundidad** a calcular (explicación más adelante).
- La línea 3 contiene un número entero N que representa la cantidad de filas del área de juego.
- La línea 4 contiene un número entero M que representa la cantidad de columnas del área de juego.
- Las siguientes N líneas contienen cadenas de M caracteres que representan el área de juego. En el área de juego, un '0' significa un cuadro vacío, mientras que cualquier otro dígito representa un bloque ocupado.
- La siguiente línea contiene un número entero K que representa la cantidad de figuras "siguientes".
- Las últimas K líneas contienen un caracter representando alguno de las siete figuras diferentes. El primer caracter corresponde a la figura que cayendo en ese momento y a la cual se debe calcular la posición.

Ejemplo de entrada:

```
1650259796944
0
20
10
0000000000
0000000000
0000000000
0000000000
0000000000
0000000000
0000000000
0000000000
0000000000
0000000000
0000000000
0001111000
0000040000
0004440000
0000700000
0007770000
0002200000
0020220000
0220066000
0777742240
7
I
Z
I
J
S
L
S
```

Con respecto a la **profundidad**, ésta determina la cantidad de piezas a considerar para la jugada. Por ejemplo, si la profundidad es 0 entonces solo se toma en cuenta la primera figura. Si la profundidad es 1, entonces se toman en cuenta la primera y segunda figura, y así sucesivamente.

**Observaciones:** No debe implementar jugadas "inteligentes" donde una figura se gira a último momento para que quepa en un determinado espacio, sino que se asume que la figura se rota desde el inicio. Tampoco  es necesario calcular ni *limpiar* las líneas que se completan. El objetivo de esta tarea es principalmente colocar las figuras.

Cada vez que se coloque una pieza, se debe calcular un puntaje que nos diga "qué tan bueno" es el estado del juego en ese momento.

Una vez que su solución haya recorrido todas las combinaciones posibles y calculado un puntaje para cada una, se debe guardar la mejor posición y rotación para cada figura.

Por cada nivel de profundidad, se espera que el programa genere un archivo "tetris_play_{nivel}.txt" que contenga:
- En la primera linea el identificador del estado del juego (el mismo recibido en el archivo de entrada).
- En la segunda línea la letra que representa la figura colocada en dicho nível.
- En la tercera línea el número que representa la rotación aplicada (0, 1, 2, ó 3)
- En la cuarta línea, el número de filas N del área de juego
- En la quinta línea, el número de columnas M del área de juego
- Y en las siguientes N líneas, hileras de M caracteres representando cada una de las filas del área de juego del estado original más las figuras del nivel actual y los anteriores colocadas en la mejor posición encontrada.

Ejemplo de salida esperada (tetris_play_0.txt):

```
1650259796944
I
1
20
10
0000000000
0000000000
0000000000
0000000000
0000000000
0000000000
0000000000
0000000000
0000000000
0000000000
0000000000
0001111000
0000040000
0004440000
0000700000
0007770000
1002200000
1020220000
1220066000
1777742240
```

Si para un estado dado, el programa no puede encontrar del todo una posición valida para colocar la figura correspondiente al nivel, entonces **no** se debe generar ningún archivo de salida para dicho nivel ni para los siguientes. Los archivos de salida deben contener únicamente estados válidos.

## Manual de Usuario

### Compilar Tarea 01

Por favor revisar folder de guide, ya que se encuentran screenshots de los pasos mencionados.

1. Ejecutar los siguientes comandos en el root de la tarea (pablo-madrigal-concurrente-2022-I./Entregables/Tareas/Tarea01/tetris_solver_serial)
    1. make clean
    1. make
        1. Puede utilizar make con alguno de los siguientes sanitazers asan, msan, tsan, ubsan. Por ejemplo: make msan

### Como utilizarla

Por favor revisar folder de guide, ya que se encuentran screenshots de los pasos mencionados.

1. Ejecutar el siguiente comando en la carpeta bin de la tarea (pablo-madrigal-concurrente-2022-I./Entregables/Tareas/Tarea01/tetris_solver_serial/bin)
    1. Puede utilizar el comando *cd bin* para llegar a la carpeta correspondiente desde el root de la tarea
    1.  Comando en la carpeta bin: ./tetris_solver_serial
        1. Puede utilizar make con alguno de los siguientes sanitazers asan, msan, tsan, ubsan. Por ejemplo: make msan
    1. Si no pone ningún parámetro al comando ./tetris_solver_serial, la tarea utilizará por defecto el siguiente archivo -> "../test/test01.txt"
    1. Si requiere utilizar otro archivo de prueba realizar estos pasos:
        1. Coloque su archivo txt en la carpeta test
        1. Ejecute en la consola el comando ./tetris_solver_serial "archivo txt" (recuerde estar en la carpeta bin, ya que el ejecutable se encuentra en esa carpeta)

### Resultado

De acuerdo a la profundidad configurada la tarea generará un archivo .txt por cada nivel, el cual se va a guardar en la carpeta /bin

### Variantes y limitaciones

1. asan : dynamic-stack-buffer-overflow scanf_common
1. tsan : ThreadSanitizer: heap-use-after-free
1. El archivo src/game_logic_alter.txt contiene logica necesaria para realizar todas la combinaciones posibles, pero su limitante es realizar hasta un maximo de profundidad 4 y los archivos txt no son tan precisos.

## Créditos

1. Pablo Madrigal Ramírez
  1. Correo: PABLO.MADRIGALRAMIREZ@ucr.ac.cr
  1. Repositorio: [pmadrigal95](https://github.com/pmadrigal95)

1. Tutoriales y ejemplos
    1. [devdocs](https://devdocs.io/c/)
    1. [learn-c.org](https://www.learn-c.org/)
    1. [3wschool](https://www.w3schools.com/c/index.php)
    1. [Listas enlazadas](https://gist.github.com/miguelpais/388199)
    1. [Ficheros en c](https://www.delftstack.com/es/howto/c/fscanf-line-by-line-in-c/)
    1. [Convertir char en entero](https://www.delftstack.com/es/howto/c/convert-int-to-char/)