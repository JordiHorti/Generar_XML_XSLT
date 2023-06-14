#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "funciones.h"
#include <stdlib.h>





int main() {

    char ruta_archivo[300];
    char adaptador[150];
  
    listarAdaptadores();

    printf("\n////////////////////////////////////////////////////////////////////////////////////////////\n");
    printf("Indica el nombre del adaptador que quieres modificar:\n");
    scanf_s("%50s", adaptador, sizeof(adaptador));

    mostrarAdaptadoresRed(adaptador);

    recogerDatosAdaptador(adaptador);

    

    return 0;

}