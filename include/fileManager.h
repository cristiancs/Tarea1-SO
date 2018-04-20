#ifndef fileManager
#define fileManager
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <unistd.h>


int numeroToLetra(int numero, char *place);
int CreateFolders();

int accessPosition(int jugador, char columna[2], char fila[2],char action[2],char letter[2], int tablero[][5]);

int createShip(int jugador, char columna[2], char fila[2], int tablero[][5]);
int checkShip(int jugador, char columna[2], char fila[2], int tablero[][5]);
int destroyShip(int jugador, char columna[2], char fila[2], int tablero[][5]);
int checkDestroyedShip(int jugador, char columna[2], char fila[2], int tablero[][5]);

int createAttack(int jugador, char columna[2], char fila[2], int tablero[][5]);
int checkAttack(int jugador, char columna[2], char fila[2], int tablero[][5]);

#endif