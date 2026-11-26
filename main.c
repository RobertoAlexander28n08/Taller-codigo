#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"

static int leerLinea(const char *mensaje, char *destino, size_t capacidad) {
    size_t longitud;

    printf("%s", mensaje);
    if (fgets(destino, capacidad, stdin) == NULL) {
        putchar('\n');
        exit(EXIT_SUCCESS);
    }

    longitud = strlen(destino);
    if (longitud > 0 && destino[longitud - 1] == '\n') {
        destino[--longitud] = '\0';
    } else {
        int caracter;
        while ((caracter = getchar()) != '\n' && caracter != EOF) {
        }
        return 0;
    }

    return longitud > 0;
}

static int leerEntero(const char *mensaje, int minimo, int maximo) {
    char entrada[64];
    char *fin;
    long valor;

    for (;;) {
        if (!leerLinea(mensaje, entrada, sizeof(entrada))) {
            printf("Ingrese un valor válido.\n");
            continue;
        }

        valor = strtol(entrada, &fin, 10);
        if (fin != entrada && *fin == '\0' && valor >= minimo && valor <= maximo) {
            return (int)valor;
        }
        printf("Seleccione una opción entre %d y %d.\n", minimo, maximo);
    }
}

static float leerCantidad(void) {
    char entrada[64];
    char *fin;
    float cantidad;

    for (;;) {
        if (!leerLinea("Cantidad aproximada en kg: ", entrada, sizeof(entrada))) {
            printf("Ingrese una cantidad válida.\n");
            continue;
        }

        cantidad = strtof(entrada, &fin);
        if (fin != entrada && *fin == '\0' && cantidad > 0.0f && cantidad < 100000.0f) {
            return cantidad;
        }
        printf("La cantidad debe ser un número mayor que cero.\n");
    }
}

static void leerTexto(const char *mensaje, char *destino, size_t capacidad) {
    while (!leerLinea(mensaje, destino, capacidad)) {
        printf("El texto no puede estar vacío ni superar %zu caracteres.\n", capacidad - 1);
    }
}

static void registrar(void) {
    static const char *tiposResiduo[] = {
        "Plástico", "Papel y cartón", "Vidrio", "Metal", "Electrónicos", "Otros"
    };
    char descripcion[120];
    char direccion[160];
    float cantidad;
    int tipo;
    int id;

    printf("\nTipos de residuo:\n");
    for (size_t i = 0; i < sizeof(tiposResiduo) / sizeof(tiposResiduo[0]); i++) {
        printf("%zu. %s\n", i + 1, tiposResiduo[i]);
    }
    tipo = leerEntero("Seleccione el tipo: ", 1, 6);
    cantidad = leerCantidad();
    leerTexto("Descripción del residuo: ", descripcion, sizeof(descripcion));
    leerTexto("Dirección de recolección: ", direccion, sizeof(direccion));

    id = registrarSolicitud(tiposResiduo[tipo - 1], cantidad, descripcion, direccion);
    if (id == 0) {
        printf("No se pudo registrar la solicitud. Se alcanzó el límite disponible.\n");
        return;
    }
    printf("Solicitud #%d registrada correctamente. Puede consultar su estado desde el menú.\n", id);
}

static void mostrarSolicitudes(void) {
    Solicitud solicitud;
    int cantidad = obtenerCantidadSolicitudes();

    if (cantidad == 0) {
        printf("\nTodavía no hay solicitudes registradas.\n");
        return;
    }

    printf("\n--- Solicitudes de recolección ---\n");
    for (int i = 0; i < cantidad; i++) {
        if (obtenerSolicitud(i, &solicitud)) {
            printf("\nSolicitud #%d | %s | %.2f kg\n",
                   solicitud.id, solicitud.tipoResiduo, solicitud.cantidad);
            printf("Descripción: %s\nDirección: %s\nEstado: %s\n",
                   solicitud.descripcion, solicitud.direccion,
                   nombreEstadoSolicitud(solicitud.estado));
        }
    }
}

static void iniciarRuta(void) {
    int asignadas = iniciarRutaRecoleccion();

    if (asignadas == -1) {
        printf("\nYa hay una ruta en curso.\n");
    } else if (asignadas == 0) {
        printf("\nNo hay solicitudes pendientes para asignar a una ruta.\n");
    } else {
        printf("\nRuta iniciada con %d parada(s). Consulte las solicitudes para ver las direcciones.\n",
               asignadas);
    }
}

static void registrarRecoleccion(void) {
    int id;
    if (!rutaActiva()) {
        printf("\nPrimero debe iniciar una ruta de recolección.\n");
        return;
    }

    id = leerEntero("Número de solicitud recolectada (0 para cancelar): ",
                    0, obtenerCantidadSolicitudes());
    if (id == 0) {
        return;
    }
    if (marcarSolicitudRecolectada(id)) {
        printf("La solicitud #%d se marcó como recolectada.\n", id);
    } else {
        printf("La solicitud no está asignada a la ruta activa.\n");
    }
}

static void finalizarRuta(void) {
    int pendientes = finalizarRutaRecoleccion();
    if (pendientes < 0) {
        printf("\nNo hay una ruta activa para finalizar.\n");
        return;
    }

    printf("\nRuta finalizada. %d solicitud(es) no atendida(s) vuelven a quedar pendientes.\n",
           pendientes);
}

int main(void) {
    int opcion;

    printf("\n========== EcoTrack ==========\n");
    printf("Gestión y seguimiento de residuos reciclables\n");

    do {
        printf("\n1. Registrar solicitud ciudadana\n");
        printf("2. Consultar solicitudes y estados\n");
        printf("3. Iniciar ruta del reciclador\n");
        printf("4. Registrar recolección\n");
        printf("5. Finalizar ruta\n");
        printf("0. Salir\n");

        opcion = leerEntero("Seleccione una opción: ", 0, 5);
        switch (opcion) {
            case 1:
                registrar();
                break;
            case 2:
                mostrarSolicitudes();
                break;
            case 3:
                iniciarRuta();
                break;
            case 4:
                registrarRecoleccion();
                break;
            case 5:
                finalizarRuta();
                break;
            case 0:
                printf("\nGracias por utilizar EcoTrack.\n");
                break;
        }
    } while (opcion != 0);

    return 0;
}
