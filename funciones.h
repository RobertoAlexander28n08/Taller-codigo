#ifndef FUNCIONES_H
#define FUNCIONES_H

typedef enum {
    PENDIENTE,
    EN_RUTA,
    RECOLECTADA
} EstadoSolicitud;

typedef struct {
    int id;
    char tipoResiduo[40];
    float cantidad;
    char descripcion[120];
    char direccion[160];
    EstadoSolicitud estado;
} Solicitud;

int registrarSolicitud(const char *tipoResiduo, float cantidad,
                       const char *descripcion, const char *direccion);
int obtenerCantidadSolicitudes(void);
int obtenerSolicitud(int indice, Solicitud *solicitud);
const char *nombreEstadoSolicitud(EstadoSolicitud estado);
int iniciarRutaRecoleccion(void);
int rutaActiva(void);
int marcarSolicitudRecolectada(int id);
int finalizarRutaRecoleccion(void);

#endif
