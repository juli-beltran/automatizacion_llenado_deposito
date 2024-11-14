#include "declaraciones.h"


/* la funcion lee el nivel de agua y 
modifica la variable global nivelAgua 
cuando se alcanza el nivel Max se detiene la bomba
la bomba vuelve a conectar al descender el nivel por 
debajo de alto*/


void controlNivel() {
  if (digitalRead(SENSOR_NIVEL_MAX) == LOW) {
    nivelAgua = MAX;
    return;
  }
  if (digitalRead(SENSOR_NIVEL_ALTO) == LOW) {
    nivelAgua = ALTO;
    return;
  }
  if (digitalRead(SENSOR_NIVEL_MEDIO) == LOW) {
    nivelAgua = MEDIO;
    return;
  } else {
    nivelAgua = BAJO;
    return;
  }
}