# EcoTrack — prototipo interactivo

Prototipo frontend para presentar el flujo de recolección de residuos reciclables: creación de solicitudes, seguimiento y recorrido del reciclador.

## Cómo abrirlo

Abre `index.html` en un navegador moderno. No requiere instalación, conexión a internet ni servidor.

## Recorrido de demostración

1. En **Nueva solicitud**, selecciona el material, ingresa una cantidad y dirección y crea una solicitud.
2. En **Seguimiento**, revisa las solicitudes de ejemplo y la que acabas de crear.
3. En **Ruta reciclador**, inicia el recorrido, registra una o más paradas y finaliza la ruta.

Las solicitudes y el avance de las paradas se guardan en `localStorage` del navegador. **Limpiar demo** elimina las solicitudes; para reiniciar las paradas, borra los datos locales de EcoTrack en el navegador.

Este es solo un prototipo de frontend: no hay backend, base de datos, asignación real de recicladores ni direcciones operativas. Las paradas son ejemplos. No se incluye un dashboard. Una arquitectura futura podría usar React, ASP.NET Core Web API y PostgreSQL con PostGIS.
