#pragma once
#ifndef FUNCIONES_H
#define FUNCIONES_H

void mostrarIps_archivo(char p_ruta_archivo[]);
void listarAdaptadores();
void mostrarAdaptadoresRed(char p_adptador[]);
void dns_accesibles(char p_ruta_archivo[]);
void dns_rapidos(char p_ruta_archivo[], char adaptador[]);
void recogerDatosAdaptador(char p_adaptador[]);
void generarXML(char p_adaptador[], char p_ip_adaptador[], char p_mascara[], char p_puerta_enlace[], char p_ip_dns[], int p_media, int p_contador, char ip_direcciones[][16]);
int isIPAddress(const char* str);
void eliminarParentesis(char* cadena);

#endif

