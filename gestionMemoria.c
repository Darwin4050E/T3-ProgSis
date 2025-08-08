#include <stdlib.h>
#include "interfaz.h";

void asignarMemoriaDinamica(char* elemento, int tamano){
    elemento = (char*) calloc(tamano, sizeof(char));
}

void liberarMemoriaDinamica(char* elemento){
    free(elemento);
}

void liberarMemoriaDinamicaPersona(Persona* persona){
    free(persona->nombres);
    free(persona->apellidos);
    free(persona->fechaNacimiento);
    free(persona->ciudadResidencia);
    free(persona->cedula);
    free(persona->profesion);
    free(persona->estadoCivil);
    free(persona->rol);
}