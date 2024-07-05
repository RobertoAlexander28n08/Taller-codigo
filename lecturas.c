#include <stdio.h>
#include "lecturas.h"

FILE* archivo; // Declaración global de archivo

int leerEnteroPositivo(const char* mensaje) {
    int valor;
    do {
        printf("%s", mensaje);
        scanf("%d", &valor);
    } while (valor <= 0);
    return valor;
}

float leerFlotantePositivo(const char* mensaje) {
    float valor;
    do {
        printf("%s", mensaje);
        scanf("%f", &valor);
    } while (valor < 0);
    return valor;
}

int leerEntero(const char* mensaje) {
    int valor;
    printf("%s", mensaje);
    scanf("%d", &valor);
    return valor;
}

float leerFlotante(const char* mensaje) {
    float valor;
    printf("%s", mensaje);
    scanf("%f", &valor);
    return valor;
}

float leerFlotanteEntre(const char* mensaje, float minimo, float maximo) {
    float valor;
    do {
        printf("%s (entre %.2f y %.2f): ", mensaje, minimo, maximo);
        scanf("%f", &valor);
    } while (valor < minimo || valor > maximo);
    return valor;
}

char leerCaracter(const char* mensaje) {
    char valor;
    printf("%s", mensaje);
    scanf(" %c", &valor); 
    return valor;
}

int leerEnteroEntre(const char* mensaje, int minimo, int maximo) {
    int valor;
    do {
        printf("%s (entre %d y %d): ", mensaje, minimo, maximo);
        scanf("%d", &valor);
    } while (valor < minimo || valor > maximo);
    return valor;
}
