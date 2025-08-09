#include <stdio.h>
#include <stdlib.h>
#include "interfaz.h"

void mostrarMenu();

int main() {
    Persona *lista_usuarios = NULL; 
    int total_usuarios = 0;
    int opcion;

    do {
        mostrarMenu();
        leerEntero(&opcion, "Seleccione una opción", 0, 3);

        switch (opcion) {
            case 1: { 
                total_usuarios++;
                
                // Se usa realloc para reservar memoria dinámica en tiempo de ejecución 
                // No hay necesidad de definir la cantidad de usuarios a ingresar
                Persona* temp = realloc(lista_usuarios, total_usuarios * sizeof(Persona));
                
                // Validar que realloc funcionó
                if (temp == NULL) {
                    printf("Error fatal: No se pudo redimensionar la memoria.\n");
                    // Liberar si hubo error
                    for(int i = 0; i < total_usuarios - 1; i++) {
                        liberarMemoriaDinamicaPersona(&lista_usuarios[i]);
                    }
                    free(lista_usuarios);
                    exit(1); 
                }
                
                // Si funcionó actualiza el puntero principal
                lista_usuarios = temp;
                
                // Función de registro
                // Se le pasa la dirección del nuevo espacio disponible
                registrarUsuario(&lista_usuarios[total_usuarios - 1], lista_usuarios, total_usuarios - 1);
                break;
            }
            case 2: 
                modificarUsuario(lista_usuarios, total_usuarios);
                break;
            case 3: 
                listarTodosLosUsuarios(lista_usuarios, total_usuarios);
                break;
            case 0: 
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("[!] Opción no válida.\n");
                break;
        }

    } while (opcion != 0);

    // Liberación de Memoria
    printf("Liberando toda la memoria asignada...\n");

    for (int i = 0; i < total_usuarios; i++) {
        liberarMemoriaDinamicaPersona(&lista_usuarios[i]);
    }

    free(lista_usuarios);
    printf("Memoria liberada. \n");

    return 0;
}


void mostrarMenu() {
    printf("\n===== MENÚ PRINCIPAL =====\n");
    printf("1. Registrar nuevo usuario\n");
    printf("2. Modificar usuario existente\n");
    printf("3. Listar todos los usuarios\n");
    printf("0. Salir\n");
    printf("==========================\n");
}



