#include <stdio.h>
#include "funciones.h"

#define MAX_SOLICITUDES 100

static Solicitud solicitudes[MAX_SOLICITUDES];
static int cantidadSolicitudes = 0;
static int rutaEnCurso = 0;

int registrarSolicitud(const char *tipoResiduo, float cantidad,
                       const char *descripcion, const char *direccion) {
    Solicitud *solicitud;

    if (cantidadSolicitudes >= MAX_SOLICITUDES || tipoResiduo == NULL ||
        descripcion == NULL || direccion == NULL || cantidad <= 0.0f) {
        return 0;
    }

    solicitud = &solicitudes[cantidadSolicitudes];
    solicitud->id = cantidadSolicitudes + 1;
    solicitud->cantidad = cantidad;
    solicitud->estado = PENDIENTE;
    snprintf(solicitud->tipoResiduo, sizeof(solicitud->tipoResiduo), "%s", tipoResiduo);
    snprintf(solicitud->descripcion, sizeof(solicitud->descripcion), "%s", descripcion);
    snprintf(solicitud->direccion, sizeof(solicitud->direccion), "%s", direccion);
    cantidadSolicitudes++;
    return solicitud->id;
}

int obtenerCantidadSolicitudes(void) {
    return cantidadSolicitudes;
}

int obtenerSolicitud(int indice, Solicitud *solicitud) {
    if (solicitud == NULL || indice < 0 || indice >= cantidadSolicitudes) {
        return 0;
    }
    *solicitud = solicitudes[indice];
    return 1;
}

const char *nombreEstadoSolicitud(EstadoSolicitud estado) {
    switch (estado) {
        case PENDIENTE:
            return "Pendiente";
        case EN_RUTA:
            return "En ruta";
        case RECOLECTADA:
            return "Recolectada";
        default:
            return "Desconocido";
    }
}

int iniciarRutaRecoleccion(void) {
    int asignadas = 0;

    if (rutaEnCurso) {
        return -1;
    }

    for (int i = 0; i < cantidadSolicitudes; i++) {
        if (solicitudes[i].estado == PENDIENTE) {
            solicitudes[i].estado = EN_RUTA;
            asignadas++;
        }
    }

    if (asignadas > 0) {
        rutaEnCurso = 1;
    }
    return asignadas;
}

int rutaActiva(void) {
    return rutaEnCurso;
}

int marcarSolicitudRecolectada(int id) {
    if (!rutaEnCurso) {
        return 0;
    }

    for (int i = 0; i < cantidadSolicitudes; i++) {
        if (solicitudes[i].id == id && solicitudes[i].estado == EN_RUTA) {
            solicitudes[i].estado = RECOLECTADA;
            return 1;
        }
    }
    return 0;
}

int finalizarRutaRecoleccion(void) {
    int pendientes = 0;

    if (!rutaEnCurso) {
        return -1;
    }

    for (int i = 0; i < cantidadSolicitudes; i++) {
        if (solicitudes[i].estado == EN_RUTA) {
            solicitudes[i].estado = PENDIENTE;
            pendientes++;
        }
    }
    rutaEnCurso = 0;
    return pendientes;
}
