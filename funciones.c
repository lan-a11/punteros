#include <stdio.h>
#include <string.h>

const char* nombresRecursos[5] = {"Diodos", "Transistores", "Resistencias", "Capacitores", "Bobinas"};

void limpiarBuffer() {
    while (getchar() != '\n');
}

void ingresarStockRecursos(int *stock) {
    printf("\n--- Ingreso de stock de recursos ---\n");
    for (int i = 0; i < 5; i++) {
        int cantidad;
        do {
            printf("Ingrese stock disponible de %s: ", nombresRecursos[i]);
            if (scanf("%d", &cantidad) != 1 || cantidad < 0) {
                printf("Entrada invalida.\n");
                limpiarBuffer();
            } else {
                stock[i] = cantidad;
                break;
            }
        } while (1);
    }
    limpiarBuffer();
    printf("Stock registrado con exito.\n");
}

int ingresarProductos(char (*nombres)[30], float *tiempos, int *cantidades, int recursosNecesarios[5][5], int total) {
    if (total >= 5) {
        printf("Ya se ingresaron los 5 productos permitidos.\n");
        return total;
    }

    printf("Nombre del producto: ");
    fgets(nombres[total], 30, stdin);
    nombres[total][strcspn(nombres[total], "\n")] = 0;

    printf("Tiempo de fabricacion (horas): ");
    while (scanf("%f", &tiempos[total]) != 1 || tiempos[total] <= 0) {
        printf("Entrada invalida. Ingrese un numero positivo: ");
        limpiarBuffer();
    }

    printf("Cantidad a fabricar: ");
    while (scanf("%d", &cantidades[total]) != 1 || cantidades[total] <= 0) {
        printf("Entrada invalida. Ingrese un numero entero positivo: ");
        limpiarBuffer();
    }

    for (int i = 0; i < 5; i++) {
        printf("Cantidad de %s por unidad: ", nombresRecursos[i]);
        while (scanf("%d", &recursosNecesarios[total][i]) != 1 || recursosNecesarios[total][i] < 0) {
            printf("Entrada invalida. Ingrese un numero entero positivo: ");
            limpiarBuffer();
        }
    }

    limpiarBuffer();
    printf("Producto ingresado con exito.\n");
    return total + 1;
}

void mostrarProductos(char (*nombres)[30], float *tiempos, int *cantidades, int recursosNecesarios[5][5], int total) {
    if (total == 0) {
        printf("No hay productos registrados.\n");
        return;
    }

    for (int i = 0; i < total; i++) {
        printf("%d. %s | Tiempo: %.2f h | Cantidad: %d\n", i + 1, nombres[i], tiempos[i], cantidades[i]);
        for (int j = 0; j < 5; j++) {
            printf("   - %s: %d\n", nombresRecursos[j], recursosNecesarios[i][j]);
        }
    }
}

void editarProducto(char (*nombres)[30], float *tiempos, int *cantidades, int recursosNecesarios[5][5], int total) {
    char nombreBuscado[30];
    printf("Nombre del producto a editar: ");
    fgets(nombreBuscado, 30, stdin);
    nombreBuscado[strcspn(nombreBuscado, "\n")] = 0;

    for (int i = 0; i < total; i++) {
        if (strcmp(nombres[i], nombreBuscado) == 0) {
            printf("Nuevo nombre: ");
            fgets(nombres[i], 30, stdin);
            nombres[i][strcspn(nombres[i], "\n")] = 0;

            printf("Nuevo tiempo de fabricacion (horas): ");
            while (scanf("%f", &tiempos[i]) != 1 || tiempos[i] <= 0) {
                printf("Entrada invalida. Ingrese un numero: ");
                limpiarBuffer();
            }

            printf("Nueva cantidad a fabricar: ");
            while (scanf("%d", &cantidades[i]) != 1 || cantidades[i] <= 0) {
                printf("Entrada invalida. Ingrese un numero: ");
                limpiarBuffer();
            }

            for (int j = 0; j < 5; j++) {
                printf("Cantidad de %s por unidad: ", nombresRecursos[j]);
                while (scanf("%d", &recursosNecesarios[i][j]) != 1 || recursosNecesarios[i][j] < 0) {
                    printf("Entrada invalida. Ingrese un numero: ");
                    limpiarBuffer();
                }
            }

            limpiarBuffer();
            printf("Producto actualizado.\n");
            return;
        }
    }
    printf("Producto no encontrado.\n");
}

int eliminarProducto(char (*nombres)[30], float *tiempos, int *cantidades, int recursosNecesarios[5][5], int total) {
    char nombreBuscado[30];
    printf("Nombre del producto a eliminar: ");
    fgets(nombreBuscado, 30, stdin);
    nombreBuscado[strcspn(nombreBuscado, "\n")] = 0;

    for (int i = 0; i < total; i++) {
        if (strcmp(nombres[i], nombreBuscado) == 0) {
            for (int j = i; j < total - 1; j++) {
                strcpy(nombres[j], nombres[j + 1]);
                tiempos[j] = tiempos[j + 1];
                cantidades[j] = cantidades[j + 1];
                for (int k = 0; k < 5; k++) {
                    recursosNecesarios[j][k] = recursosNecesarios[j + 1][k];
                }
            }
            printf("Producto eliminado.\n");
            return total - 1;
        }
    }
    printf("Producto no encontrado.\n");
    return total;
}

void calcularTotales(float *tiempos, int *cantidades, int recursosNecesarios[5][5], int total, float *tiempoTotal, int *recursosTotales) {
    *tiempoTotal = 0;
    for (int i = 0; i < 5; i++) recursosTotales[i] = 0;

    for (int i = 0; i < total; i++) {
        *tiempoTotal += tiempos[i] * cantidades[i];
        for (int j = 0; j < 5; j++) {
            recursosTotales[j] += recursosNecesarios[i][j] * cantidades[i];
        }
    }
}

void verificarCumplimiento(float tiempoDisponible, int *stock, float tiempoTotal, int *recursosTotales, int recursosDisponibles) {
    int cumple = 1;
    if (!recursosDisponibles) {
        printf("Primero debe ingresar el stock de recursos disponibles.\n");
        return;
    }

    if (tiempoTotal > tiempoDisponible) {
        printf("Tiempo insuficiente. Requiere %.2f h, tiene %.2f h\n", tiempoTotal, tiempoDisponible);
        cumple = 0;
    }

    for (int i = 0; i < 5; i++) {
        if (recursosTotales[i] > stock[i]) {
            printf("Faltan %s: necesita %d, tiene %d\n", nombresRecursos[i], recursosTotales[i], stock[i]);
            cumple = 0;
        }
    }

    if (cumple)
        printf("Se puede cumplir con la demanda.\n");
}

void mostrarTotalesRecursos(int *recursosTotales) {
    printf("\n--- Recursos Totales Requeridos ---\n");
    for (int i = 0; i < 5; i++) {
        printf("%s: %d\n", nombresRecursos[i], recursosTotales[i]);
    }
}
