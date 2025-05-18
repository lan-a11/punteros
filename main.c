#include <stdio.h>
#include <string.h>
#include "funciones.h"

int main() {
    char nombres[5][30];
    float tiempos[5];
    int cantidades[5];
    int recursosNecesarios[5][5];
    int stockRecursos[5];
    int total = 0, opcion;
    float tiempoDisponible, tiempoTotal;
    int recursosTotales[5];
    int recursosDisponibles = 1;

    do {
        printf("\n==== MENU PRODUCCION ====\n");
        printf("1. Ingresar stock disponible de recursos\n");
        printf("2. Ingresar productos\n");
        printf("3. Mostrar productos\n");
        printf("4. Editar producto\n");
        printf("5. Eliminar producto\n");
        printf("6. Calcular tiempo y recursos necesarios\n");
        printf("7. Verificar si se puede cumplir con la demanda\n");
        printf("8. Salir\n");
        printf("Seleccione una opcion: ");
        
        if (scanf("%d", &opcion) != 1) {
            printf("Entrada invalida. Debe ingresar un numero.\n");
            while (getchar() != '\n');
            continue;
        }
        getchar();

        switch(opcion) {
            case 1:
                ingresarStockRecursos(stockRecursos);
                recursosDisponibles = 1;
                break;
            case 2:
                total = ingresarProductos(nombres, tiempos, cantidades, recursosNecesarios, total);
                break;
            case 3:
                mostrarProductos(nombres, tiempos, cantidades, recursosNecesarios, total);
                break;
            case 4:
                editarProducto(nombres, tiempos, cantidades, recursosNecesarios, total);
                break;
            case 5:
                total = eliminarProducto(nombres, tiempos, cantidades, recursosNecesarios, total);
                break;
            case 6:
                calcularTotales(tiempos, cantidades, recursosNecesarios, total, &tiempoTotal, recursosTotales);
                printf("Tiempo total requerido: %.2f horas\n", tiempoTotal);
                mostrarTotalesRecursos(recursosTotales);
                break;
            case 7:
                printf("Ingrese tiempo disponible (en horas): ");
                if (scanf("%f", &tiempoDisponible) != 1 || tiempoDisponible <= 0) {
                    printf("Tiempo invalido.\n");
                    while (getchar() != '\n');
                    break;
                }
                calcularTotales(tiempos, cantidades, recursosNecesarios, total, &tiempoTotal, recursosTotales);
                verificarCumplimiento(tiempoDisponible, stockRecursos, tiempoTotal, recursosTotales, recursosDisponibles);
                break;
            case 8:
                printf("Gracias por usar el sistema.\n");
                break;
            default:
                printf("Opcion no valida.\n");
        }

    } while (opcion != 8);

    return 0;
}
