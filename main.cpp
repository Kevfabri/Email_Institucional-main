/*
 * Universidad de las Fuerzas Armadas "ESPE"
 * Enunciado: Creacion de Correo a partir de Nombres y Apellidos
 * Autor: Kevin Jacho
 * Fecha de Creación: 20 de Noviembre del 2024
 * Fecha de Modificación: 21 de Noviembre del 2024
 * NRC: 1972
 * Curso: Estructura de Datos
 * Docente: Edgar Solis
 */

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "EmailList.h"

char* ingresar(const char* mensaje) {
    printf("%s", mensaje);
    char* texto = (char*)malloc(1);
    if (texto == NULL) {
        printf("Error: no se pudo asignar memoria.\n");
        exit(1);
    }
    *texto = '\0'; // Inicializamos la cadena como vacía
    char c;
    int length = 0;

    while ((c = getch()) != 13) { // 13 es Enter
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == ' ') {
            // Añadir carácter válido
            printf("%c", c);
            length++;
            texto = (char*)realloc(texto, length + 1);
            if (texto == NULL) {
                printf("\nError: no se pudo reasignar memoria.\n");
                exit(1);
            }
            *(texto + length - 1) = c; // Usamos puntero en lugar de texto[length - 1]
            *(texto + length) = '\0';
        } else if (c == 8 && length > 0) { // 8 es Backspace
            // Eliminar último carácter
            printf("\b \b");
            length--;
            *(texto + length) = '\0'; // Terminamos la cadena correctamente
            texto = (char*)realloc(texto, length + 1);
            if (texto == NULL) {
                printf("\nError: no se pudo reasignar memoria.\n");
                exit(1);
            }
        }
    }
    printf("\n");
    return texto;
}

char* obtenerPrimeraPalabra(const char* texto) {
    const char* inicio = texto;
    while (*inicio == ' ') inicio++; // Ignorar espacios iniciales

    const char* fin = inicio;
    while (*fin && *fin != ' ') fin++; // Avanzar hasta el primer espacio o final

    int longitud = fin - inicio;
    char* resultado = (char*)malloc(longitud + 1);
    if (resultado == NULL) {
        printf("Error: no se pudo asignar memoria.\n");
        exit(1);
    }
    strncpy(resultado, inicio, longitud);
    *(resultado + longitud) = '\0';
    return resultado;
}

char* obtenerUltimaPalabra(const char* texto) {
    const char* fin = texto + strlen(texto) - 1;
    while (fin > texto && *fin == ' ') fin--; // Ignorar espacios finales

    const char* inicio = fin;
    while (inicio > texto && *(inicio - 1) != ' ') inicio--; // Retroceder hasta el inicio de la última palabra

    int longitud = fin - inicio + 1;
    char* resultado = (char*)malloc(longitud + 1);
    if (resultado == NULL) {
        printf("Error: no se pudo asignar memoria.\n");
        exit(1);
    }
    strncpy(resultado, inicio, longitud);
    *(resultado + longitud) = '\0';
    return resultado;
}

int main() {
    EmailList<char> emailList;
    initEmailList(&emailList);

    char *nombreCompleto, *apellidoCompleto;
    char *nombre1, *nombre2, *apellido1, *apellido2;
    char opcion;

    do {
        nombreCompleto = ingresar("Ingrese los nombres: ");
        apellidoCompleto = ingresar("Ingrese los apellidos: ");

        nombre1 = obtenerPrimeraPalabra(nombreCompleto);
        nombre2 = obtenerUltimaPalabra(nombreCompleto);
        apellido1 = obtenerPrimeraPalabra(apellidoCompleto);
        apellido2 = obtenerUltimaPalabra(apellidoCompleto);

        addEmail(&emailList, nombre1, nombre2, apellido1);

        free(nombreCompleto);
        free(apellidoCompleto);
        free(nombre1);
        free(nombre2);
        free(apellido1);
        free(apellido2);

        printf("¿Desea ingresar otro nombre? (s/n): ");
        opcion = getchar();
        while (getchar() != '\n'); // Limpiar el buffer
    } while (opcion == 's' || opcion == 'S');

    printf("\nLista de Correos:\n");
    showEmails(&emailList);

    destroyEmailList(&emailList);

    return 0;
}
