#include "declaraciones.h"

// Funcion interrupcion señal caudalimetro
void incrementoBloqueAgua()
{
  bloqueAgua++;
  return;
}
// funcion actualiza total acumulado de agua y activa volumen a clorar
void solicitudClorado(void)
{
  float metros3volumenAcumulado; //volumen total acumulado, guardada en eeprom
  float K1 = 1000.0; //conversion metros cubicos -> litro
  EEPROM.get(4, metros3volumenAcumulado); 
  metros3volumenAcumulado += (cicloAgua / K1); // actualiza m3 acumulados
  EEPROM.update(4, metros3volumenAcumulado); //se salvan en eeprom
  volumenAClorar = cicloAgua;
  cicloAgua = 0;
}

// control de los ciclos de llenado de agua y peticion de clorado
void controlCicloAgua(void)
{
  //constantes de calculo
  const float K1 = FACTOR_CAUDALIMETRO * 60 / PERIODO_TIC0 / ESCALADO_TIC1; //  conversion tics/ ciclo a litros min. escalado tic2 porque la funcion se ejecuta cada tic2
  const float K2 = FACTOR_CAUDALIMETRO / 1000; //conversion tics / litros
  const unsigned int K3 = 20; //ciclos de tiempo de funcionamiento de la bomba para estabilizar caudal
  //variables
  unsigned int bloqueAguaCopia;// salva bloqueAgua para poder reiniciar rapidamente la interrupcion
  float litrosBloque; // convierte en litros bloqueAguaCopia
  // constantes y variables para controlar un cese en el caudal de llenado
  const bool HAY_CAUDAL = true;
  const bool SIN_CAUDAL = false;
  const bool ESPERANDO_BLOQUE_CON_CAUDAL = true;
  const bool ESPERANDO_BLOQUE_SIN_CAUDAL = false;

  static bool estadoLlenado = SIN_CAUDAL;
  static bool estadoDeControl = ESPERANDO_BLOQUE_CON_CAUDAL;


  // desactivacion momentanea de la interrupcion para poder salvar y resetear bloque de agua
  detachInterrupt(digitalPinToInterrupt(SENSOR_FLUJO));
  bloqueAguaCopia = bloqueAgua; // variables ussigned int que contabilizan pulsos del medidor durante el valor de tic2
  bloqueAgua = 0;
  attachInterrupt(digitalPinToInterrupt(SENSOR_FLUJO), incrementoBloqueAgua, RISING);
  //calcula caudalmedio  y litros del bloque
  caudal = bloqueAguaCopia * FACTOR_CAUDALIMETRO * K1;
  litrosBloque = bloqueAguaCopia * K2;

  // incrementa ciclo de agua
  cicloAgua += litrosBloque;

  // comprueba que exista caudal minimo con la bomba en funcionamiento y con un tirmpo para estabilizar el flujo
  // si el caudal es insuficientegenera error1 que detendra la bomba
  if ((caudal < MINIMO_CAUDAL) && (estadoBombaAgua == HIGH) && (tiempoFuncionamientoBombaAgua > K3))
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