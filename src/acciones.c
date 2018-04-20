#include "../include/acciones.h"

int atacar(char* mensaje, int jugador, int tablero[][5]){
	char columna[2];
	char fila[2];

	strcpy(columna, "");
	strcpy(fila, "");

	// Debemos Atacar

	if(strncpy(columna, mensaje, 1) && strncpy(fila, mensaje+1, 1)){
		if(checkShip(jugador, columna, fila, tablero) == -1){
			destroyShip(jugador, columna, fila, tablero);
		}
		else{
			createAttack(jugador, columna, fila, tablero);
		}
		
	}

	if(strncpy(columna, mensaje+3, 1) && strncpy(fila, mensaje+4, 1)){
		if(checkShip(jugador, columna, fila, tablero) == -1){
			destroyShip(jugador, columna, fila, tablero);
		}
		else{
			createAttack(jugador, columna, fila, tablero);
		}
	}



	return 1;
}

int notificarResultados(char *mensaje, int jugador, int* pipe, int tablero[][5]){
	char columna[2];
	strcpy(columna, "");

	// No se por que, pero si lo hacia como en la de arriba me daba mal el largo
	char fila[] = "1";
	char m[15];
	strcpy(m, "R:");
	strcat(m, mensaje);
	strcat(m, ":");

	
	if(strncpy(columna, mensaje, 1) && strncpy(fila, mensaje+1, 1)){
		if(checkDestroyedShip(jugador, columna, fila, tablero) == -1){
			strcat(m, "1");
		}
		else{
			strcat(m, "0");
		}
	}

	strcat(m, ":");


	if(strncpy(columna, mensaje+3, 1) && strncpy(fila, mensaje+4, 1)){
		if(checkDestroyedShip(jugador, columna, fila, tablero) == -1){
			strcat(m, "1");
		}
		else{
			strcat(m, "0");
		}

	}


	
	write(pipe[1], m, strlen(m)+1);
	return 1;
}
int mostrarResultados(char *mensaje){
	char fc[3];
	char e[2];
	strncpy(fc, mensaje, 2);
	strncpy(e, mensaje+6, 1);
	
	if(mensaje[6]-'0' == 1){
		printf("El ataque %s a alcanzado un barco \n",fc);
		
	}
	else{
		printf("El ataque %s NO a alcanzo un barco \n",fc);
	}

	strncpy(fc, mensaje+3, 2);
	strncpy(e, mensaje+8, 1);
	if(mensaje[8]-'0' == 1){
		printf("El ataque %s a alcanzado un barco \n",fc);
		
	}
	else{
		printf("El ataque %s NO a alcanzo un barco \n",fc);
	}
	return 0;
}
int solicitarCoordenadas(int jugador, int jugador_enemigo, int* pipe, int tablero[][5]){
	

	char m[8];
	strcpy(m, "");
	int i;
	char columna[2];
	char fila[2];
	char columna_O[2];
	char fila_O[2];
	strcpy(columna, "");
	strcpy(fila, "");
	strcpy(columna_O, "");
	strcpy(fila_O, "");


	strcpy(m, "A");
	for (i = 0; i < 2; ++i){
		// Pedir Coordenada & Validar
		printf("Jugador %d, Indique Columna Barco a Atacar : ", jugador);
		scanf("%s",columna);


		while(strcmp(columna, "A") != 0 && strcmp(columna, "B") && strcmp(columna, "C") && strcmp(columna, "D") && strcmp(columna, "E") ){
			printf(ANSI_COLOR_RED "Coordenada invalida" ANSI_COLOR_RESET "\n");
			printf("Jugador %d, Indique Columna Barco a Atacar : ", jugador);
			scanf("%s",columna);
		}

		printf("Jugador %d, Indique Fila Barco a Atacar : ", jugador);
		scanf("%s",fila);
		while(strcmp(fila, "1") != 0 && strcmp(fila, "2") && strcmp(fila, "3") && strcmp(fila, "4") && strcmp(fila, "5") ){
			printf(ANSI_COLOR_RED "Coordenada invalida" ANSI_COLOR_RESET "\n");
			printf("Jugador %d, Indique Fila Barco a Atacar : ", jugador);
			scanf("%s",fila);
		}

		// Verificar si ya fue marcada

		if(i == 0){
			while(checkAttack(jugador_enemigo, columna, fila, tablero) == -1){
				printf(ANSI_COLOR_RED "Posición Ya Utilizada, indique una posición valida" ANSI_COLOR_RESET "\n");

				printf("Jugador %d, Indique Columna Barco a Atacar : ", jugador);
				scanf("%s",columna);

				while(strcmp(columna, "A") != 0 && strcmp(columna, "B") && strcmp(columna, "C") && strcmp(columna, "D") && strcmp(columna, "E") ){
					printf(ANSI_COLOR_RED "Coordenada invalida" ANSI_COLOR_RESET "\n");
					printf("Jugador %d, Indique Columna Barco a Atacar : ", jugador);
					scanf("%s",columna);
				}

				printf("Jugador %d, Indique Fila Barco a Atacar : ", jugador);
				scanf("%s",fila);
				while(strcmp(fila, "1") != 0 && strcmp(fila, "2") && strcmp(fila, "3") && strcmp(fila, "4") && strcmp(fila, "5") ){
					printf(ANSI_COLOR_RED "Coordenada invalida" ANSI_COLOR_RESET "\n");
					printf("Jugador %d, Indique Fila Barco a Atacar : ", jugador);
					scanf("%s",fila);
				}
			}
			strcpy(columna_O, columna);
			strcpy(fila_O, fila);
		}
		else{
			while( (strcmp(columna, columna_O) == 0 &&  strcmp(fila, fila_O) == 0 ) || checkAttack(jugador_enemigo, columna, fila, tablero) == -1){
				printf(ANSI_COLOR_RED "Posición Ya Utilizada, indique una posición valida" ANSI_COLOR_RESET "\n");
				printf("Jugador %d, Indique Columna Barco a Atacar : ", jugador);
				scanf("%s",columna);

				while(strcmp(columna, "A") != 0 && strcmp(columna, "B") && strcmp(columna, "C") && strcmp(columna, "D") && strcmp(columna, "E") ){
					printf("Jugador %d, Indique Columna Barco a Atacar : ", jugador);
					scanf("%s",columna);
				}

				printf("Jugador %d, Indique Fila Barco a Atacar : ", jugador);
				scanf("%s",fila);
				while(strcmp(fila, "1") != 0 && strcmp(fila, "2") && strcmp(fila, "3") && strcmp(fila, "4") && strcmp(fila, "5") ){
					printf("Jugador %d, Indique Fila Barco a Atacar : ", jugador);
					scanf("%s",fila);
				}
			}
			
		}
		
		
		strcat(m, ":");
		strcat(m, columna);
		strcat(m, fila);
		
	}

	write(pipe[1], m, strlen(m)+1);
	return 1;
}

int checkFin(int jugador, int tablero[][5]){
	int barcos_destruidos = 0;
	int i, i2;
	char columna[2];
	char fila[2];
	for (i = 1; i <= 5; ++i){
		strcpy(fila, "");
		sprintf(fila,"%d",i);

		for (i2 = 1; i2 <= 5; ++i2){
			numeroToLetra(i2, columna);
			if(checkDestroyedShip(jugador, columna, fila, tablero) == -1){
				barcos_destruidos++;
			}
			usleep(1000);
		}
	}

	if(barcos_destruidos == 5){
		return 2;
	}
	return 1;
}

int generarGraficos(int jugador, int tablero[][5]){
	int barcos_destruidos = 0;
	int i, i2;
	char columna[2];
	char fila[2];
	printf("-------------------\n");
	printf("    A  B  C  D  E \n");
	printf("-------------------\n");
	for (i = 1; i <= 5; ++i){
		printf("%d |", i);
		strcpy(fila, "");

		sprintf(fila,"%d",i);

		for (i2 = 1; i2 <= 5; ++i2){
			numeroToLetra(i2, columna);
			if(checkDestroyedShip(jugador, columna, fila, tablero) == -1){
				barcos_destruidos++;
				printf(" D ");
			}
			else if(checkAttack(jugador, columna, fila, tablero) == -1){
				printf(" A ");
			}
			else{
				printf(" O ");
			}
			usleep(1000);
		}
		printf("\n");
	}
	printf("-------------------\n");
	printf("A: Disparo Fallado\nO: Disponible\nD: Barco Destruido\n%d de 5 Barcos Destruidos\n", barcos_destruidos);

	if(barcos_destruidos == 5){
		return 2;
	}
	return 1;
}