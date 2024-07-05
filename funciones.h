void mostrarProducto();
void mostrarColores();
void mostrarTallas();
void mostrarDisponibilidad(int producto, int color, int talla);
void ingresarProducto(const char *producto, const char *color, const char *talla, float precio);
void guardarProductosEnArchivo();
void leerProductosDesdeArchivo();

extern FILE* archivo; // Declaración externa de archivo
