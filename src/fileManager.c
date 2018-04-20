#include "../include/fileManager.h"

int numeroToLetra(int numero, char *place){
	if(numero == 1){
		strcpy(place, "A");
	}
	else if(numero == 2){
		strcpy(place, "B");
	}
	else if(numero == 3){
		strcpy(place, "C");
	}
	else if(numero == 4){
		strcpy(place, "D");
	}
	else if(numero == 5){
		strcpy(place, "E");
	}
	return 1;
}

int CreateFolders(){

	// Creación de Archivos

	int i = 0;
	int i2 = 0;
	mkdir("data", 0777);
	mkdir("data/player1", 0777);
	mkdir("data/player2", 0777);
	for (i = 1; i <= 5; ++i) {
		for (i2 = 1; i2 <= 5; ++i2) {
			char name1[100] = "data/player1/";
			char name2[100] = "data/player2/";
			char letra[2];
			char numero[2];
			sprintf(numero,"%d",i2);

			numeroToLetra(i, letra);
			
			strcat(name1, letra);
			strcat(name1, "_");
			strcat(name1, numero);

			strcat(name2, letra);
			strcat(name2, "_");
			strcat(name2, numero);

			mkdir(name1, 0777);
			mkdir(name2, 0777);
		}
		
	}
	return 0;
};

int accessPosition(int jugador, char columna[2], char fila[2],char action[2],char letter[2]){
	char name[100];
	// Armar Ruta
	if(jugador == 1){
		strcpy(name, "data/player1/");
	}
	else{
		strcpy(name, "data/player2/");
	}

	strcat(name, columna);
	strcat(name, "_");
	strcat(name, fila);
	strcat(name, "/");
	strcat(name, letter);

	DIR* dir = opendir(name);
	if (dir){
		if(strcmp(action, "D")){
			rmdir(name);
		}
		//printf("Archivo existe \n");
	    closedir(dir);
	    return -1;
	}
	else if (ENOENT == errno){
		//printf("Archivo NO existe \n");
		if(strcmp(action, "W") == 0){
			mkdir(name, 0777);
		}
	    
	    return 1;
	}
	return 0;
}
// 1 => No Existe, -1 => Existe
int createShip(int jugador, char columna[2], char fila[2]){
	return accessPosition(jugador, columna, fila, "W", "B");
}
int checkShip(int jugador, char columna[2], char fila[2]){
	return accessPosition(jugador, columna, fila, "R", "B");
}
int destroyShip(int jugador, char columna[2], char fila[2]){
	return accessPosition(jugador, columna, fila, "W", "D");
	return accessPosition(jugador, columna, fila, "D", "B");
}
int checkDestroyedShip(int jugador, char columna[2], char fila[2]){
	return accessPosition(jugador, columna, fila, "R", "D");
}
// 1 => No Existe, -1 => Existe
int checkAttack(int jugador, char columna[2], char fila[2]){
	return accessPosition(jugador, columna, fila, "R", "A");
}

int createAttack(int jugador, char columna[2], char fila[2]){
	return accessPosition(jugador, columna, fila, "W", "A");
}
