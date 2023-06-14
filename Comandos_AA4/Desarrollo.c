#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS 

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <winsock2.h>
#include <iphlpapi.h>
#include "funciones.h"

#define MAX_LINE_LENGTH 100
#define MAX_IP_ADDRESSES 100

#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib") 

//Función que utilizamos para saber si lo que analizamos cumple con el formato de una IP.
int isIPAddress(const char* str) {
	// Verificar si una cadena tiene el formato de una dirección IP
	int a, b, c, d;
	return sscanf(str, "%d.%d.%d.%d", &a, &b, &c, &d) == 4 ||
		(sscanf(str, "[%d.%d.%d.%d]", &a, &b, &c, &d) == 4);
}
//Función que utilizamos para eliminar lo que viene después de la IP (En este caso el (Preferido) ) para quedarnos solo con la IP. 
void eliminarParentesis(char* cadena) {
	char* pos = strstr(cadena, "(");
	if (pos != NULL) {
		*pos = '\0'; // Reemplaza el primer carácter de '(' con el carácter nulo
	}
}

//Metodo para listar los adaptadores de red que tenemos 
void listarAdaptadores() {

	system("ipconfig /all > informacionAdaptadores.txt");

}
//Metodo para mostrar los DNS del adaptador seleccionado
void mostrarAdaptadoresRed(char p_adaptador[]) {

	char numero;
	char* ip_dns;
	bool encontrado = false;

	FILE* file;

	file = fopen("informacionAdaptadores.txt", "r");
	if (file == NULL) {
		printf("Error al abrir el archivo informacionAdaptadores.txt\n");
		return;
	}
	char linea[150];


	//Si no estamos al final del archivo accedemos al bucle
	while (!feof(file)) {

		fgets(linea, 150, file);
		linea[strcspn(linea, "\n")] = '\0'; // elimina el carácter de nueva línea



		if (strstr(linea, p_adaptador) != NULL) { //Si la linea contiene el nombre del adaptador...

			fgets(linea, 150, file);

			while (strstr(linea, "Adaptador") == NULL) {// Mientras no volvamos a encontrarnos la palabra Adaptador avanzamos hasta encontrar los DNS

				fgets(linea, 150, file);

				while (fgets(linea, sizeof(linea), file) != NULL) {
					if (strstr(linea, "Servidores DNS") != NULL) {
						// Extraer la dirección IP de la línea
						ip_dns = strstr(linea, ":") + 2;
						printf("Su Servidir DNS primario es: %s\n", ip_dns);
						encontrado = true;
						break;
					}
				}
				break;
			}

		}
		if (encontrado) {
			break;
		}

	}

}

void recogerDatosAdaptador(char p_adaptador[]) {

	char ip_dns[100] = "\0";
	char puerta_enlace[100] = "\0";
	char ip_adaptador[100] = "\0";
	char mascara[100] = "\0";
	char* posicion =  "";


	FILE* file;

	file = fopen("informacionAdaptadores.txt", "r");
	if (file == NULL) {
		printf("Error al abrir el archivo informacionAdaptadores.txt\n");
		return;
	}
	char linea[150];

	//Si no estamos al final del archivo accedemos al bucle
	while (!feof(file)) {

		fgets(linea, 150, file);
		linea[strcspn(linea, "\n")] = '\0'; // elimina el carácter de nueva línea

		fprintf(file, "\n");

		if (strstr(linea, p_adaptador) != NULL) {

			printf("================================================\n");
			printf("El adaptador seleccionado es: %s\n", p_adaptador);
			printf("================================================\n");

			fgets(linea, 150, file);

			while (strstr(linea, "Adaptador") == NULL) {

				fgets(linea, 150, file);

				if (strstr(linea, "IPv4") != NULL) {
					posicion = strstr(linea, ":") + 2;
					strncpy(ip_adaptador, posicion, sizeof(ip_adaptador) - 1);
					ip_adaptador[strcspn(ip_adaptador, "\n")] = '\0'; // Asegurarse de que la cadena termina con el carácter nulo
					eliminarParentesis(ip_adaptador);
					printf("\nIP: %s\n", ip_adaptador);
				}

				if (strstr(linea, "subred") != NULL) {
					posicion = strstr(linea, ":") + 2;
					strncpy(mascara, posicion, sizeof(mascara) - 1);
					mascara[strcspn(mascara, "\n")] = '\0';; // Asegurarse de que la cadena termina con el carácter nulo
					printf("\nMascara de subred: %s\n", mascara);
				}

				if (strstr(linea, "Puerta de enlace") != NULL) {
					posicion = strstr(linea, ":") + 2;
					strncpy(puerta_enlace, posicion, sizeof(puerta_enlace) - 1);
					puerta_enlace[strcspn(puerta_enlace, "\n")] = '\0'; // Asegurarse de que la cadena termina con el carácter nulo
					printf("\nPuerta de enlace: %s\n", puerta_enlace);
				}

				if (strstr(linea, "Servidores DNS") != NULL) {
					posicion = strstr(linea, ":") + 2;
					strncpy(ip_dns, posicion, sizeof(ip_dns));
					ip_dns[strcspn(ip_dns, "\n")] = '\0'; // Asegurarse de que la cadena termina con el carácter nulo
					printf("\nDNS primario: %s\n", ip_dns);
				}
			}
			break;
		}
	}

	fclose(file);

	char comando[150];

	sprintf(comando, "ping %s > datos_adaptadores.txt", ip_dns);
	system(comando);

	int numero = 0;
	int* contador = 0;
	int* media = 0;
	int* punteroContador = &contador; // Puntero a contador
	int* punteroMedia = &media; // Puntero a media
	char comando_3[150] = "tracert ";
	bool encontrado = false;

	strcpy(comando_3, "tracert ");
	strcat(comando_3, ip_dns);
	strcat(comando_3, " >> datos_adaptadores.txt");
	system(comando_3);

	Sleep(5);

	char ip_direcciones[MAX_IP_ADDRESSES][16];// Array para almacenar las direcciones IP (con un tamaño máximo de 15 caracteres + el carácter nulo)
	int i = 0;

	FILE* f2 = fopen("datos_adaptadores.txt", "r");

	
	if (f2 == NULL) {
		printf("El fichero datos_adaptador.txt no se ha podido abrir.");
	}
	else {
		
		while (fgets(linea, sizeof(linea), f2) != NULL) {

			if (strstr(linea, "Media")) {

				*punteroMedia = strstr(linea, ":") + 2;

				printf("\nMedia: (%d ms)\n", *punteroMedia);
				
			}
			if (sscanf(linea, "%d", &numero) == 1 && numero > 0) {

				char* palabra = strtok(linea, " \t\n");
				while (palabra != NULL) {
					if (isIPAddress(palabra)) {
						printf("\nDirección IP encontrada: %s\n", palabra);
						strcpy(ip_direcciones[i], palabra); // Almacena la dirección IP en el array
						(i++);
						encontrado = true;
					}
					
					palabra = strtok(NULL, " \t\n");
					
				}

				if (!encontrado) {

					printf("\nDirección IP encontrada: \n");
					strcpy(ip_direcciones[i], palabra);
				}
			}

			if (strstr(linea, "Traza completa") != 0) {//Si la linea contiene Traza completa paramos de leer
				break;
			}
			

		}
	}

	fprintf(f2, "El numero de saltos es: %d\n ", i+1);

	printf("\nSaltos: %d\n", i+1);

	fclose(f2);

	generarXML(p_adaptador, ip_adaptador, mascara, puerta_enlace, ip_dns, media, i,ip_direcciones);
}
	
void generarXML(char p_adaptador[], char p_ip_adaptador[], char p_mascara[], char p_puerta_enlace[], char p_ip_dns[], int p_media, int p_contador, char p_ip_direcciones[][16]) {

	FILE* file = fopen("archivo.xml", "w");

	if (file == NULL) {
		printf("Error al abrir el archivo archivo.txt\n");
		return;
	}
	if (file != NULL) {
		fprintf(file, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
		fprintf(file, "<datos>\n");
		fprintf(file, "    <IP>%s</IP>\n", p_ip_adaptador);
		fprintf(file, "    <Mascara>%s</Mascara>\n", p_mascara);
		fprintf(file, "    <PuertaDeEnlace>%s</PuertaDeEnlace>\n", p_puerta_enlace);
		fprintf(file, "    <DNSPrimario>%s</DNSPrimario>\n", p_ip_dns);
		fprintf(file, "    <Media>%d ms</Media>\n", p_media);
		fprintf(file, "    <Saltos>\n");
		fprintf(file, "          <NumeroDeSaltos>%d</NumeroDeSaltos>\n", p_contador + 1);
		for (int i = 0; i < p_contador; i++) {
			fprintf(file, "               <ip>%s</ip>\n", p_ip_direcciones[i]);
		}
		fprintf(file, "    </Saltos>\n");				
		fprintf(file, "</datos>\n");
		fclose(file);
		printf("XML creado correctamente.\n");
	}
	else {
		printf("Error al crear el archivo XML.\n");
	}

	fclose(file);

	return 0;
}
		
