
#include "declaraciones.h"

bool tic0 = LOW;
bool tic1 = LOW;
bool tic2 = LOW;

void generacionTics(){
 static byte contadorTic1 = 1; 
 static byte contadorTic2 = 1; 
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

    if (contadorTic2 == 1) {
      tic2 =! tic2;
      contadorTic2 = ESCALADO_TIC2;
    }
    else 
    contadorTic2 --;
  }
  return;
}