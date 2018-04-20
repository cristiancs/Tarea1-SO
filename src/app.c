#include "../include/app.h"

void* create_shared_memory(size_t size) {
  int protection = PROT_READ | PROT_WRITE;
  int visibility = MAP_ANONYMOUS | MAP_SHARED;
  return mmap(NULL, size, protection, visibility, 0, 0);
}


int main(){

	CreateFolders();

	int tablero1[5][5] = {  
		{0, 0, 0, 0, 0} ,  
		{0, 0, 0, 0, 0} , 
		{0, 0, 0, 0, 0} ,
		{0, 0, 0, 0, 0} ,
		{0, 0, 0, 0, 0} ,
	};
	int tablero2[5][5] = {  
		{0, 0, 0, 0, 0} ,  
		{0, 0, 0, 0, 0} , 
		{0, 0, 0, 0, 0} ,
		{0, 0, 0, 0, 0} ,
		{0, 0, 0, 0, 0} ,
	};
	void* shared_tablero1 = create_shared_memory(128);
	void* shared_tablero2 = create_shared_memory(128);
	memcpy(shared_tablero1, tablero1, sizeof(tablero1));
	memcpy(shared_tablero2, tablero2, sizeof(tablero2));

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
			if(jugador == 1){
				if( createShip(jugador, columna, fila, shared_tablero1) == -1){
					printf(ANSI_COLOR_RED "Error, la posición ya tiene un barco" ANSI_COLOR_RESET "\n");
					--i;
				}
			}
			else{
				if( createShip(jugador, columna, fila, shared_tablero2) == -1){
					printf(ANSI_COLOR_RED "Error, la posición ya tiene un barco" ANSI_COLOR_RESET "\n");
					--i;
				}
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
	while(strcmp(mensaje, "END:1") != 0 && strcmp(mensaje, "END:2") != 0){
		if(pid==0){

			if(flag == 0){
				// Procesar Ataque
				read(pipe2[0], mensaje, sizeof(mensaje));		
				strncpy(accion, mensaje, 1);
				if(strcmp(accion, "A") == 0){
					atacar(mensaje+2, 1, shared_tablero1);
					notificarResultados(mensaje+2, 1, pipe1, shared_tablero1);
				}
				else if(strcmp(accion, "R") == 0){
					mostrarResultados(mensaje+2);
					write(pipe1[1], "P", strlen("P")+1);
				}
				else if(strcmp(accion, "P") == 0){
					
					
					fflush(stdout);
					
					if(checkFin(1, shared_tablero1) == 2){
						write(pipe1[1], "END:2", strlen("END:2")+1);
						strcpy(mensaje, "END:2");
					}
					else{
						printf("\n\nTurno del Jugador 1\n");
						generarGraficos(2, shared_tablero2);
						solicitarCoordenadas(1, 2, pipe1, shared_tablero2);
					}
					
				}

			}
			else{
				close(pipe1[0]);
				close(pipe2[1]);
				flag = 0;
				printf("\n\nTurno del Jugador 1\n");
				generarGraficos(2, shared_tablero2);
				solicitarCoordenadas(1, 2, pipe1, shared_tablero2);
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
				fflush(stdout);	
				atacar(mensaje+2, 2, shared_tablero2);
				notificarResultados(mensaje+2, 2, pipe2, shared_tablero2);
			}
			else if(strcmp(accion, "R") == 0){
				mostrarResultados(mensaje+2);
				write(pipe2[1], "P", strlen("P")+1);
			}
			else if(strcmp(accion, "P") == 0){
				
				fflush(stdout);
				
				if(checkFin(2, shared_tablero2) == 2){
					write(pipe2[1], "END:1", strlen("END:1")+1);
					strcpy(mensaje, "END:1");

				}
				else{
					printf("\n\nTurno del Jugador 2\n");
					generarGraficos(1, shared_tablero1);
					solicitarCoordenadas(2, 1, pipe2, shared_tablero1);
				}
				
			}
			flag = 0;
			
		}
		
	}
		

	
	wait(NULL);
	if(pid != 0){
		char ganador[2];
		strncpy(ganador, mensaje+4, 1);
		printf("Fin del Juego, el ganador es el Jugador %s \n", ganador);
	}
	
}
