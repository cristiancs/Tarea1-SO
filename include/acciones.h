#ifndef ACCIONES
#define ACCIONES
#include "fileManager.h"
#include <sys/wait.h>


#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"




int atacar(char* mensaje, int jugador);
int solicitarCoordenadas(int jugador, int jugador_enemigo, int* pipe);
int generarGraficos(int jugador);
int notificarResultados(char *mensaje, int jugador, int* pipe);
int mostrarResultados(char *mensaje);
#endif