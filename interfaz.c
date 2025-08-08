#include <stdio.h>
#include <stdlib.h>
#include "interfaz.h"

void asignarMemoriaDinamica(char* elemento, int tamano){
    elemento = (char*) calloc(tamano, sizeof(char));
}

void liberarMemoriaDinamica(char* elemento){
    free(elemento);
}

void liberarMemoriaDinamicaPersona(Persona* persona) {
    free(persona->nombres);
    free(persona->apellidos);
    free(persona->fechaNacimiento);
    free(persona->ciudadResidencia);
    free(persona->cedula);
    free(persona->profesion);
    free(persona->estadoCivil);
    free(persona->rol);
    free(persona->clave); 
}

/*
int validarRepeticionCedula(Persona* personas, int tamano, char* cedula){
    for(int i = 0; i < tamano; i++){
        if(personas->cedula == cedula){
            return -1;
        }
        personas++;
    }
    return 0;
} */

int validarRepeticionCedula(Persona* personas, int tamanoActual, const char* cedula) {
    for (int i = 0; i < tamanoActual; i++) {
        // El operador '==' solo compara las direcciones de memoria.
        if (strcmp(personas[i].cedula, cedula) == 0) {
            return -1; // repetida
        }
    }
    return 0; // no repetida

void mostarDatosPersona(Persona persona){
    printf("Nombres: %s", persona.nombres);
    printf("Apellidos: %s", persona.apellidos);
    printf("Fecha nacimiento: %s", persona.fechaNacimiento);
    printf("Ciudad de residendcia: %s", persona.ciudadResidencia);
    printf("Cedula: %s", persona.profesion);
    printf("Profesion: %s", persona.profesion);
    printf("Estado Civil: %s", persona.estadoCivil);
    printf("Rol: %s", persona.rol);
    printf("Código: %d", persona.codigo);
}

// Registro de usuarios

char* leerString(const char *indicacion) {
    char buffer[256];
    printf(">>> %s: ", indicacion);
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';

    char* result = malloc(strlen(buffer) + 1);
    if (result == NULL) {
        printf("Fallo al reservar memoria.\n");
        exit(1);
    }
    strcpy(result, result);
    return result;
}

void leerEntero(int *numero, const char *indicacion, int minVal, int maxVal) {
    int c;
    do {
        printf(">>> %s [%d-%d]: ", indicacion, minVal, maxVal);
        if (scanf("%d", numero) != 1) {
            printf("  [!] Entrada inválida. Debe ser un número. Intenta de nuevo.\n");
            while ((c = getchar()) != '\n' && c != EOF); // Limpiar buffer de entrada
            *numero = minVal - 1; // Forzar a que el bucle continúe
            continue;
        }
        if (*numero < minVal || *numero > maxVal) {
            printf("  [!] El número debe estar entre %d y %d. Intenta de nuevo.\n", minVal, maxVal);
        }
        while ((c = getchar()) != '\n' && c != EOF); // Limpiar buffer de entrada para el siguiente fgets
    } while (*numero < minVal || *numero > maxVal);
}

Persona* buscarUsuarioPorCedula(Persona* listaPersonas, int totalUsuarios, const char* cedula) {
    for (int i = 0; i < totalUsuarios; i++) {
        if (strcmp(listaPersonas[i].cedula, cedula) == 0) {
            return &listaPersonas[i]; // Puntero 
        }
    }
    return NULL; // No se encontró el usuario
}

