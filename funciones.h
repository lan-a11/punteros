int ingresarProductos(char (*nombres)[30], float *tiempos, int *cantidades, int recursosNecesarios[5][5], int total);
void mostrarProductos(char (*nombres)[30], float *tiempos, int *cantidades, int recursosNecesarios[5][5], int total);
void editarProducto(char (*nombres)[30], float *tiempos, int *cantidades, int recursosNecesarios[5][5], int total);
int eliminarProducto(char (*nombres)[30], float *tiempos, int *cantidades, int recursosNecesarios[5][5], int total);
void ingresarStockRecursos(int *stock);
void calcularTotales(float *tiempos, int *cantidades, int recursosNecesarios[5][5], int total, float *tiempoTotal, int *recursosTotales);
void verificarCumplimiento(float tiempoDisponible, int *stock, float tiempoTotal, int *recursosTotales, int recursosDisponibles);
void mostrarTotalesRecursos(int *recursosTotales);
