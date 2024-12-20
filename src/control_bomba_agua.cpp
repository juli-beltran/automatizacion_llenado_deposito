#include "declaraciones.h"

//pone en funcionamiento o detiene la bomba de agua
void controlBombaAgua()
{
  if (estadoBombaAgua == LOW) // si la bomba esta parada, comprueba condciones para ponerse en marcha
  {
    if ((nivelAgua < ALTO) && (errorCaudalAguaInsuficiente == LOW) && (errorTiempoFuncionamientoBombaExcedido == LOW))
    {
      estadoBombaAgua = HIGH; // arranca la bomba si deposito inferior a alto y no hay errores
      digitalWrite(RELE_AGUA, HIGH);
      tiempoFuncionamientoBombaAgua = 0; // pone a cero el contador de tiempo de funcionamiento de la bomba
    }
    return;
  }
  else // la bomba esta en funcionamiento
  {
    if (tiempoFuncionamientoBombaAgua >= MAXIMO_TIEMPO_FUNCIONAMIENTO_BOMBA)
    {
      errorTiempoFuncionamientoBombaExcedido = HIGH; // comprueba tiempo de funconamiento, si esta rebasado actualiza error2
    }

    if ((nivelAgua == MAX) || (errorCaudalAguaInsuficiente == HIGH) || (errorTiempoFuncionamientoBombaExcedido == HIGH)) // si se dan las condiciones detiene la bomba
    {
      estadoBombaAgua = LOW;
      digitalWrite(RELE_AGUA, LOW);
    }
    else
    {                                  
      tiempoFuncionamientoBombaAgua ++; // la bomba continua su funcionamiento
    }
    return;
  }
}