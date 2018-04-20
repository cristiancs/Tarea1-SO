
## Ejecución
make
make run

## Ejecuciones Consecutivas

Se debe ejecutar el siguiente comando para limpiar la carpeta de data antes de ejecutarlo nuevamente. 

* make cf

Comando Recomendado:
* make cf && make run

## Método de Comunicación

Para esta tarea se ha decidido utilizar pipes tanto para la comunicación de ataques como de los resultados de los ataques.


# Estructura

* data: carpeta creada en la ejecución del programa en la cual se guarda un registro de los barcos y ataques durante el juego

* include: cabeceras para los archivos .c
* src: archivos .c que dan vida a la aplicación
	* acciones.c : Funciones que permiten el funcionamiento general del programa
	* fileManager.c : Funciones que tienen relación con la lectura / escritura desde la carpeta data
	* app.c : Core del programa.

# Comentarios
Se ha creado una estructura de soporte para los datos almacenados en la carpeta data por que al parecer la lectura desde el disco no siempre es consistente, esta estructura se almacena en memoria compartida