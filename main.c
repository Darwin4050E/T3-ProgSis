#include <stdio.h>
#include <stdlib.h>
#include "interfaz.h"

void mostrarMenu();

int main() {
    Persona *lista_usuarios = NULL; // El puntero inicia en NULL, crucial para realloc
    int total_usuarios = 0;
    int opcion;

    do {
        mostrarMenu();
        leerEntero(&opcion, "Seleccione una opción", 0, 3);

        switch (opcion) {
            case 1: { 
                total_usuarios++;
                
                // Puntero temporal para redimensionar la memoria
                Persona* temp = realloc(lista_usuarios, total_usuarios * sizeof(Persona));
                
                // Validar que realloc funcionó
                if (temp == NULL) {
                    printf("Error fatal: No se pudo redimensionar la memoria.\n");
                    // Liberar todo lo que se tenía antes de salir
                    for(int i = 0; i < total_usuarios - 1; i++) {
                        liberarMemoriaDinamicaPersona(&lista_usuarios[i]);
                    }
                    free(lista_usuarios);
                    exit(1); // Salir del programa por error crítico
                }
                
                // Si funcionó, actualizar el puntero principal
                lista_usuarios = temp;
                
                // 5. Llamar a la función de registro
                // Se le pasa la dirección del nuevo espacio disponible (&lista_usuarios[total_usuarios - 1])
                // y la cantidad de usuarios que había ANTES para la validación de la cédula (total_usuarios - 1)
                registrarUsuario(&lista_usuarios[total_usuarios - 1], lista_usuarios, total_usuarios - 1);
                break;
            }
            case 2: // Modificar usuario
                modificarUsuario(lista_usuarios, total_usuarios);
                break;
            case 3: // Listar todos los usuarios
                listarTodosLosUsuarios(lista_usuarios, total_usuarios);
                break;
            case 0: // Salir
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("[!] Opción no válida.\n");
                break;
        }

    } while (opcion != 0);

    // --- Proceso de Liberación de Memoria ---
    printf("Liberando toda la memoria asignada...\n");
    // 1. Liberar la memoria de los strings dentro de cada struct
    for (int i = 0; i < total_usuarios; i++) {
        liberarMemoriaDinamicaPersona(&lista_usuarios[i]);
    }
    // 2. Liberar la memoria del arreglo principal de structs
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



