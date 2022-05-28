# Readme para ejecutar la Tarea 02

### Paso 1

Ejecutar los siguientes comandos en el root de la tarea (pablo-madrigal-concurrente-2022-I./Entregables/Tareas/Tarea02/tetris_solver_pthreads)
make clean
make

![1](1.PNG)

![1-1](1-1.PNG)

Puede utilizar make con alguno de los siguientes sanitazers asan, msan, tsan, ubsan. Por ejemplo: make msan

![2](2.PNG)

![1-2](1-2.PNG)

Ejecutar el siguiente comando en la carpeta bin de la tarea (pablo-madrigal-concurrente-2022-I./Entregables/Tareas/Tarea02/tetris_solver_pthreads/bin)
Puede utilizar el comando *cd bin* para llegar a la carpeta correspondiente desde el root de la tarea

![3](3.PNG)

Comando en la carpeta bin: ./tetris_solver_pthreads

![4](4.PNG)

Si no pone ningún parámetro al comando ./tetris_solver_pthreads, la tarea utilizará por defecto el siguiente archivo -> "../test/test01.txt"

![5](5.PNG)

Si requieres utilizar hilos, puedes utilizar el siguiente comando ./tetris_solver_pthreads "../test/test01.txt" {Cantidad de hilos}

Si no pone ningún parámetro al comando relacionado a hilos ./tetris_solver_pthreads, la tarea utilizará por defecto el valor sysconf(_SC_NPROCESSORS_ONLN);

![2-2-2](2-2-2.PNG.PNG)

Resultados

![6](6.PNG)

![7](7.PNG)

