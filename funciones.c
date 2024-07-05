#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"

#define ARCHIVO_PRODUCTOS "productos.txt"

FILE* archivo; // Declaración global de archivo

// Arreglos para productos, colores, tallas y precios
const char *productos[] = {"Camisetas", "Chompas", "Pantalones", "Zapatos", "Gorras"};
const char *colores[] = {"Blanco", "Negro", "Azul", "Rojo", "Verde", "Rosa"};
const char *tallas[] = {"Small", "Medium", "Large"};
const float precios[5][6] = {
    {19.99, 14.99, 24.99, 29.99, 0.0, 0.0}, // Camisetas
    {39.99, 44.99, 59.99, 29.99, 0.0, 0.0}, // Chompas
    {29.99, 35.99, 49.99, 59.99, 0.0, 0.0}, // Pantalones
    {35.99, 49.99, 59.99, 29.99, 0.0, 0.0}, // Zapatos
    {20.00, 15.00, 0.0, 0.0, 0.0, 0.0} // Gorras
};

void guardarProductosEnArchivo() {
    archivo = fopen(ARCHIVO_PRODUCTOS, "w");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo %s.\n", ARCHIVO_PRODUCTOS);
        return;
    }

    for (int i = 0; i < 5; i++) {
        fprintf(archivo, "%s\n", productos[i]);
        for (int j = 0; j < 6; j++) {
            if (precios[i][j] == 0.0) continue;
            fprintf(archivo, "Color: %s\n", colores[j]);
            for (int k = 0; k < 3; k++) {
                fprintf(archivo, "Talla: %s\n", tallas[k]);
                fprintf(archivo, "Precio: %.2f\n", precios[i][j]);
                fprintf(archivo, "\n");
            }
        }

    }

    fclose(archivo);
}

#include <stdio.h>
void mostrarProducto() {
    printf("Seleccione el producto:\n");
    for (int i = 0; i < 5; i++) {
        printf("%d. %s\n", i + 1, productos[i]);
    }
    printf("0. Salir\n");
}

void mostrarColores(int productoSeleccionado) {
    printf("Seleccione el color:\n");
    for (int i = 0; i < 4; i++) {
        if (precios[productoSeleccionado][i] > 0) {
            printf("%d. %s\n", i + 1, colores[i]);
        }
    }
}

void mostrarTallas() {
    printf("Seleccione la talla:\n");
    for (int i = 0; i < 3; i++) {
        printf("%d. %s\n", i + 1, tallas[i]);
    }
}

void mostrarPrecio(int productoSeleccionado, int colorSeleccionado) {
    printf("Precio: %.2f\n", precios[productoSeleccionado][colorSeleccionado]);
}

void mostrarDisponibilidad(int producto, int color, int talla) {
    int disponibilidad = 100;
    float precio = precios[producto - 1][color - 1];
    float iva = 0.15; // 15% de IVA

    if (precio > 0.0) {
        float precioConIVA = precio * (1 + iva);
        printf("\nDisponibilidad: %d unidades\n", disponibilidad);
        printf("Precio sin IVA: $%.2f\n", precio);
        printf("Precio con IVA (15%%): $%.2f\n", precioConIVA);
    } else {
        printf("\nProducto no disponible en ese color.\n");
    }
}

void ingresarProducto(const char *producto, const char *color, const char *talla, float precio) {
    archivo = fopen(ARCHIVO_PRODUCTOS, "a");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo %s.\n", ARCHIVO_PRODUCTOS);
        return;
    }

    fprintf(archivo, "%s %s %s %.2f\n", producto, color, talla, precio);
    fclose(archivo);
}

void leerProductosDesdeArchivo() {
    archivo = fopen(ARCHIVO_PRODUCTOS, "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo %s.\n", ARCHIVO_PRODUCTOS);
        return;
    }

    char producto[50];
    printf("\nProductos en el archivo:\n");
    while (fgets(producto, sizeof(producto), archivo)) {
        printf("%s", producto);
    }

    fclose(archivo);
}
