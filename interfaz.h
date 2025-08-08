#ifndef INTERFAZ_H
#define INTERFAZ_H

// Estructuras

typedef struct {
    char* nombres;
    char* apellidos;
    char* fechaNacimiento; // Revisar
    char* ciudadResidencia;
    char* cedula;
    char* profesion;
    char* estadoCivil;
    char* rol; // Revisar
} Persona;

// Gestión de memoria

void asignarMemoriaDinamica(char* elemento, int tamano);
void liberarMemoriaDinamica(char* elemento);
void liberarMemoriaDinamicaPersona(Persona* persona);

// Gestion de usuario

int validarRepeticionCedula(Persona* personas, int tamano, char* cedula);
void mostarDatosPersona(Persona persona);

#endif