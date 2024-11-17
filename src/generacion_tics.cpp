
#include "declaraciones.h"

bool tic0 = LOW;
bool tic1 = LOW;


void generacionTics(){
 static byte contadorTic1 = 1; 
 static unsigned long nuevoTiempoTic0 = 7000; //tiempo de ejecucion en milisegundos donde empieza la generacion de tics
  if (millis() > nuevoTiempoTic0) {
    tic0 = !tic0;
    nuevoTiempoTic0 += PERIODO_TIC0;

    if (contadorTic1 == 1) {
      tic1 =! tic1;
      contadorTic1 = ESCALADO_TIC1;
     }
    else 
      contadorTic1 --;


  }
  return;
}