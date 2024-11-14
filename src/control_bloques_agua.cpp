#include "declaraciones.h"

// Funcion interrupcion señal caudalimetro
void incrementoBloqueAgua()
{
  bloqueAgua++;
  return;
}

void solicitudClorado(void)
{
  metros3volumenAcumulado += (cicloAgua * FACTOR_CAUDALIMETRO); // actualiza m3 acumulados
  EEPROM.update(4, metros3volumenAcumulado);
  volumenAClorar = cicloAgua;
  cicloAgua = 0;
}

// control de los ciclos de llenado de agua y peticion de clorado
void controlCicloAgua(void)
{
  // constantes y variables para controlar un cese en el caudal de llenado
  const bool HAY_CAUDAL = true;
  const bool SIN_CAUDAL = false;
  const bool ESPERANDO_BLOQUE_CON_CAUDAL = true;
  const bool ESPERANDO_BLOQUE_SIN_CAUDAL = false;
  
  static bool estadoLlenado = SIN_CAUDAL;
  static bool estadoDeControl = ESPERANDO_BLOQUE_CON_CAUDAL;

  // desactivacion momentanea de la interrupcion para poder salvar y resetear bloque de agua
  detachInterrupt(digitalPinToInterrupt(SENSOR_FLUJO));
  bloqueAguaCopia = bloqueAgua;
  bloqueAgua = 0;
  attachInterrupt(digitalPinToInterrupt(SENSOR_FLUJO), incrementoBloqueAgua, RISING);

  // incrementa ciclo de agua
  cicloAgua += bloqueAguaCopia;

  // comprueba que exista caudal minimo con la bomba en funcionamiento y con un tirmpo para estabilizar el flujo
  // si el caudal es insuficientegenera error1 que detendra la bomba
  if ((bloqueAguaCopia < MINIMO_BLOQUE_AGUA) && (estadoBombaAgua == HIGH) && (tiempoFuncionamientoBombaAgua > 30))
  {
    error1 = true;
  }

  // comprueba si se ha alcanzado el volumen a clorar, peticion de clorado
  if (cicloAgua > FIN_CICLO_AGUA)
  {
    solicitudClorado();
  }

  // detecta si hay una detencion en el caudal y si es superior al minimo solicita clorado

  if (bloqueAguaCopia == 0) // comprueba si hay caudal o no
  {
    estadoLlenado = HAY_CAUDAL;
  }
  else
  {
    estadoLlenado = SIN_CAUDAL;
  }

  if ((estadoLlenado == HAY_CAUDAL) && (estadoDeControl == ESPERANDO_BLOQUE_CON_CAUDAL))
  {
    estadoDeControl = ESPERANDO_BLOQUE_SIN_CAUDAL;
  }

  if (estadoLlenado == SIN_CAUDAL && estadoDeControl == ESPERANDO_BLOQUE_SIN_CAUDAL)
  {
    estadoDeControl = ESPERANDO_BLOQUE_CON_CAUDAL;
    if (cicloAgua > MINIMO_VOLUMEN_A_CLORAR)
    {
      solicitudClorado();
    }
  }
}