#include "../include/app.h"




int main(){

	CreateFolders();


	// Posicionar Barcos

	int i, jugador;
	char columna[2];
	char fila[2];
	printf("Bienvenidos a Battleship, posicionen sus barcos \n");
	for (jugador = 1; jugador <= 2; ++jugador) {
		printf("Jugador %d es su turno\n", jugador);
		for (i = 1; i <= 5; ++i) {
			printf("Jugador %d, Indique Columna Barco %d : ", jugador, i);

			scanf("%s",columna);

			while(strcmp(columna, "A") != 0 && strcmp(columna, "B") && strcmp(columna, "C") && strcmp(columna, "D") && strcmp(columna, "E") ){
				printf(ANSI_COLOR_RED "Coordenada invalida" ANSI_COLOR_RESET "\n");
				printf("Jugador %d, Indique Columna Barco %d : ", jugador, i);
				scanf("%s",columna);
			}

			printf("Jugador %d, Indique Fila Barco %d : ", jugador, i);
			scanf("%s",fila);
			while(strcmp(fila, "1") != 0 && strcmp(fila, "2") && strcmp(fila, "3") && strcmp(fila, "4") && strcmp(fila, "5") ){
				printf(ANSI_COLOR_RED "Coordenada invalida" ANSI_COLOR_RESET "\n");
				printf("Jugador %d, Indique Fila Barco %d : ", jugador, i);
				scanf("%s",fila);
			}

			printf("Ingresa la posicion %s %s \n", columna, fila);
			if( createShip(jugador, columna, fila) == -1){
				printf(ANSI_COLOR_RED "Error, la posición ya tiene un barco" ANSI_COLOR_RESET "\n");
				--i;
			}

		}
	}


	int pipe1[2], pipe2[2];
	int pid, flag;
	char mensaje[20];
	char accion[2];
	pipe(pipe1);
	pipe(pipe2);
	flag = 1;
	// Iniciar Turnos

	printf("Comienza la batalla! \n");
	pid=fork();
	while(strcmp(mensaje, "END") != 0){
		if(pid==0){

			if(flag == 0){
				// Procesar Ataque
				read(pipe2[0], mensaje, sizeof(mensaje));		
				strncpy(accion, mensaje, 1);
				if(strcmp(accion, "A") == 0){
					atacar(mensaje+2, 2);
					notificarResultados(mensaje+2, 2, pipe1);
				}
				else if(strcmp(accion, "R") == 0){
					mostrarResultados(mensaje+2);
					fflush(stdout);
					generarGraficos(2);
					write(pipe1[1], "P", strlen("P")+1);
				}
				else if(strcmp(accion, "P") == 0){
					solicitarCoordenadas(1, 2, pipe1);
				}

			}
			else{
				close(pipe1[0]);
				close(pipe2[1]);
				flag = 0;
				solicitarCoordenadas(1, 2, pipe1);
			}
			
		}
		else{
			if(flag == 1){
				close(pipe1[1]);
				close(pipe2[0]);
			}
			
			// Procesar Ataque	
			read(pipe1[0], mensaje, sizeof(mensaje));		
			strncpy(accion, mensaje, 1);
			if(strcmp(accion, "A") == 0){
				atacar(mensaje+2, 1);
				notificarResultados(mensaje+2, 1, pipe2);
			}
			else if(strcmp(accion, "R") == 0){
				mostrarResultados(mensaje+2);
				fflush(stdout);
				generarGraficos(1);
				write(pipe2[1], "P", strlen("P")+1);
			}
			else if(strcmp(accion, "P") == 0){
				solicitarCoordenadas(2, 1, pipe2);
			}
			flag = 0;
			
		}
		
	}
		

	
	wait(NULL);
	printf("Finish Padre \n"); //Esto es ejecutable por ambos procesos
}
