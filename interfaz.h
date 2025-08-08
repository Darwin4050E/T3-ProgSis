#ifndef INTERFAZ_H
#define INTERFAZ_H

// Estructuras

typedef struct {
    char* nombres;
    char* apellidos;
    char* fechaNacimiento;
    char* ciudadResidencia;
    char* cedula;
    char* profesion;
    char* estadoCivil;
    char* rol;
    char* clave; // Añadido para guardar la clave generada
    int codigo;
} Persona;

// ===== Gestión de Memoria  =====
void liberarMemoriaDinamicaPersona(Persona* persona);
void asignarMemoriaDinamica(char* elemento, int tamano);
void liberarMemoriaDinamica(char* elemento);


// ===== Validación y Búsqueda =====
int validarRepeticionCedula(Persona* personas, int tamanoActual, const char* cedula);
Persona* buscarUsuarioPorCedula(Persona* listaPersonas, int totalUsuarios, const char* cedula);

// ===== Módulo de Registro y Modificación =====
void registrarUsuario(Persona *nuevoUsuario, Persona* listaCompleta, int totalUsuarios);
void modificarUsuario(Persona* listaPersonas, int totalUsuarios);
char* leerString(const char *indicacion);
void leerEntero(int *numero, const char *indicacion, int minVal, int maxVal);

// ===== Módulo de Claves =====
char* generarClave(Persona* persona);
int validarClave(Persona* persona, const char* claveIngresada);

#endif