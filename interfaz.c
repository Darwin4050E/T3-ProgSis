#include <stdio.h>
#include <stdlib.h>
#include "interfaz.h"
#include <string.h>   // para strcmp, strcpy, strlen, strcspn
#include <ctype.h>    // para toupper
#include <time.h>     // para time

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
}

void mostrarDatosPersona(Persona persona) { 
    printf("  Nombres: %s\n", persona.nombres);
    printf("  Apellidos: %s\n", persona.apellidos);
    printf("  Cédula: %s\n", persona.cedula);
    printf("  Fecha nacimiento: %s\n", persona.fechaNacimiento);
    printf("  Ciudad de residencia: %s\n", persona.ciudadResidencia);
    printf("  Profesión: %s\n", persona.profesion);
    printf("  Estado Civil: %s\n", persona.estadoCivil);
    printf("  Rol: %s\n", persona.rol);
    printf("  Código: %d\n", persona.codigo);
    printf("  Clave: %s\n", persona.clave);
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
    strcpy(result, buffer);
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

void registrarUsuario(Persona *nuevoUsuario, Persona* listaCompleta, int totalUsuarios) {
    printf("\n--- Registro de Nuevo Usuario ---\n");
    
    nuevoUsuario->nombres = leerString("Nombres");
    nuevoUsuario->apellidos = leerString("Apellidos");
    
    do {
        nuevoUsuario->cedula = leerString("Cédula (no se podrá cambiar)");
        if (validarRepeticionCedula(listaCompleta, totalUsuarios, nuevoUsuario->cedula) != 0) {
            printf("  [!] La cédula '%s' ya existe. Intente con otra.\n", nuevoUsuario->cedula);
            free(nuevoUsuario->cedula); // Liberar memoria de la cédula inválida 
            nuevoUsuario->cedula = NULL;
        }
    } while (nuevoUsuario->cedula == NULL);

    nuevoUsuario->fechaNacimiento = leerString("Fecha de Nacimiento (DD/MM/AAAA)");
    nuevoUsuario->ciudadResidencia = leerString("Ciudad de Residencia");
    nuevoUsuario->profesion = leerString("Profesión");
    nuevoUsuario->estadoCivil = leerString("Estado Civil");
    nuevoUsuario->rol = leerString("Rol (Administrador / Usuario Final)");
    leerEntero(&nuevoUsuario->codigo, "Código numérico", 10, 99);

    // Generar y asignar la clave
    nuevoUsuario->clave = generarClave(nuevoUsuario);
    printf("\n-- Usuario registrado exitosamente --\n");
    printf("===========================================\n");
    printf("  Usuario de Acceso: %s\n", nuevoUsuario->cedula);
    printf("  CLAVE GENERADA: %s\n", nuevoUsuario->clave);
    printf("===========================================\n");
}

void modificarUsuario(Persona* listaPersonas, int totalUsuarios) {
    if (totalUsuarios <= 0) {
        printf("\n[!] No hay usuarios registrados para modificar.\n");
        return;
    }

    printf("\n--- Modificación de Usuario ---\n");
    char* cedulaBusqueda = leerString("Ingrese la cédula del usuario a modificar");

    Persona* usuarioAModificar = buscarUsuarioPorCedula(listaPersonas, totalUsuarios, cedulaBusqueda);
    free(cedulaBusqueda); 

    if (usuarioAModificar == NULL) {
        printf("\n[!] Usuario no encontrado.\n");
        return;
    }

    char* claveIngresada = leerString("Ingrese su clave actual");
    
    // Validar clave - implementar función
    if (validarClave(usuarioAModificar, claveIngresada) == 0) {
        printf("\n[!] Clave incorrecta. Acceso denegado.\n");
        free(claveIngresada);
        return;
    }
    free(claveIngresada);

    printf("\n[✓] Acceso concedido. Puede modificar los datos.\n");

    int opcion;
    do {
        printf("\n¿Qué dato desea cambiar?\n");
        printf("1. Nombres\n2. Apellidos\n3. Fecha de Nacimiento\n");
        printf("4. Ciudad de Residencia\n5. Profesión\n6. Estado Civil\n");
        printf("7. Rol\n8. Código\n0. Guardar cambios y Salir\n");
        leerEntero(&opcion, "Opción", 0, 8);

        switch (opcion) {
            case 1: free(usuarioAModificar->nombres); usuarioAModificar->nombres = leerString("Nuevos nombres"); break;
            case 2: free(usuarioAModificar->apellidos); usuarioAModificar->apellidos = leerString("Nuevos apellidos"); break;
            case 3: free(usuarioAModificar->fechaNacimiento); usuarioAModificar->fechaNacimiento = leerString("Nueva Fecha de Nacimiento"); break;
            case 4: free(usuarioAModificar->ciudadResidencia); usuarioAModificar->ciudadResidencia = leerString("Nueva Ciudad de Residencia"); break;
            case 5: free(usuarioAModificar->profesion); usuarioAModificar->profesion = leerString("Nueva Profesión"); break;
            case 6: free(usuarioAModificar->estadoCivil); usuarioAModificar->estadoCivil = leerString("Nuevo Estado Civil"); break;
            case 7: free(usuarioAModificar->rol); usuarioAModificar->rol = leerString("Nuevo Rol"); break;
            case 8: leerEntero(&usuarioAModificar->codigo, "Nuevo Código", 10, 99); break;
        }
        if(opcion != 0) printf("  [✓] Dato actualizado.\n");

    } while (opcion != 0);
    
    // Regenerar 
    free(usuarioAModificar->clave); // Clave antigua
    usuarioAModificar->clave = generarClave(usuarioAModificar);
    
    printf("\n[✓] Datos guardados exitosamente.\n");
    printf("===========================================\n");
    printf("  SE HA GENERADO UNA NUEVA CLAVE:\n");
    printf("  NUEVA CLAVE: %s\n", usuarioAModificar->clave);
    printf("===========================================\n");
}

void listarTodosLosUsuarios(Persona* lista, int total) {
    printf("\n--- Lista de Usuarios Registrados (%d) ---\n", total);
    if (total == 0) {
        printf("No hay usuarios para mostrar.\n");
        return;
    }
    for (int i = 0; i < total; i++) {
        printf("\n----- Usuario %d -----\n", i + 1);
        mostrarDatosPersona(lista[i]);
        printf("-----------------------\n");
    }
}


char* generarClave(Persona* persona) {
    char base[16];
    int pos = 0;

    if (persona->nombres && strlen(persona->nombres) > 0)
        base[pos++] = toupper(persona->nombres[0]);
    if (persona->apellidos && strlen(persona->apellidos) > 0)
        base[pos++] = toupper(persona->apellidos[0]);
    if (persona->ciudadResidencia && strlen(persona->ciudadResidencia) > 0)
        base[pos++] = toupper(persona->ciudadResidencia[0]);
    if (persona->profesion && strlen(persona->profesion) > 0)
        base[pos++] = toupper(persona->profesion[0]);
    if (persona->estadoCivil && strlen(persona->estadoCivil) > 0)
        base[pos++] = toupper(persona->estadoCivil[0]);
    if (persona->rol && strlen(persona->rol) > 0)
        base[pos++] = toupper(persona->rol[0]);

    base[pos] = '\0';

    for (int i = 0; i < pos; i++) {
        base[i] = (char)((base[i] + persona->codigo) % 126);
        if (base[i] < 33) base[i] += 33;
    }

    char* clave = malloc(pos + 1);
    strcpy(clave, base);
    return clave;
}


int validarClave(Persona* persona, const char* claveIngresada) {
    // Generar clave esperada
    char* claveEsperada = generarClave(persona);

    int esValida = (strcmp(claveEsperada, claveIngresada) == 0);

    free(claveEsperada);
    return esValida;
}
