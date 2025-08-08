#include <stdio.h>
#include "interfaz.h"


int validarRepeticionCedula(Persona* personas, int tamano, char* cedula){
    for(int i = 0; i < tamano; i++){
        if(personas->cedula == cedula){
            return -1;
        }
        personas++;
    }
    return 0;
}

void mostarDatosPersona(Persona persona){
    printf("Nombres: %s", persona.nombres);
    printf("Apellidos: %s", persona.apellidos);
    printf("Fecha nacimiento: %s", persona.fechaNacimiento);
    printf("Ciudad de residendcia: %s", persona.ciudadResidencia);
    printf("Cedula: %s", persona.profesion);
    printf("Profesion: %s", persona.profesion);
    printf("Estado Civil: %s", persona.estadoCivil);
    printf("Rol: %s", persona.rol);
}