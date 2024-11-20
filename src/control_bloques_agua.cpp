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
  float volumenAguaTotalAcumulado; //volumen total acumulado, guardada en eeprom
  const float K1 = 1000.0; //conversion metros cubicos -> litro
  EEPROM.get(VOLUMEN_AGUA_TOTAL_ACUMULADO, volumenAguaTotalAcumulado); 
  volumenAguaTotalAcumulado += (cicloLlenadoAgua / K1); // actualiza m3 acumulados
  EEPROM.update(VOLUMEN_AGUA_TOTAL_ACUMULADO, volumenAguaTotalAcumulado); //se salvan en EEPROM
  volumenAClorar = cicloLlenadoAgua; //activa ciclo clorado y resetea ciclo llenado agua
  cicloLlenadoAgua = 0;
}

// control de los ciclos de llenado de agua y peticion de clorado
void controlCicloLlenadoAgua(void)
{
  //constantes de calculo
  const float K1 = FACTOR_CAUDALIMETRO * 60 / PERIODO_TIC0 / ESCALADO_TIC1; //  conversion tics/ ciclo a litros min. escalado tic2 porque la funcion se ejecuta cada tic2
  const float K2 = FACTOR_CAUDALIMETRO / 1000; //conversion tics / litros
  const unsigned int K3 = 20; //ciclos de tiempo de funcionamiento de la bomba de cloro para estabilizar caudal
  //variables
  unsigned int bloqueAguaCopia;// salva bloqueAgua para poder reiniciar rapidamente la interrupcion
  float litrosBloque; // convierte en litros bloqueAguaCopia fuera de la interrupcion
  // constantes y variables para controlar un cese en el caudal de llenado
  enum Caudal 
  {
    SIN_CAUDAL,
    CON_CAUDAL
  };
  
  enum EstadoLlenado
  {
    ESPERANDO_BLOQUE_SIN_CAUDAL,
    ESPERANDO_BLOQUE_CON_CAUDAL
  };


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
  cicloLlenadoAgua += litrosBloque;

  // comprueba que exista caudal minimo con la bomba en funcionamiento y con un tirmpo para estabilizar el flujo
  // si el caudal es insuficientegenera error1 que detendra la bomba
  if ((caudal < MINIMO_CAUDAL) && (estadoBombaAgua == HIGH) && (tiempoFuncionamientoBombaAgua > K3))
  {
    errorCaudalAguaInsuficiente = true;
  }

  // comprueba si se ha alcanzado el volumen a clorar, peticion de clorado
  if (cicloLlenadoAgua > VOLUMEN_FINALIZACION_CICLO_AGUA)
  {
    solicitudClorado();
  }

  // detecta si hay una detencion en el caudal y si es superior al minimo solicita clorado

  if (bloqueAguaCopia == 0) // comprueba si hay caudal o no
  {
    estadoLlenado = CON_CAUDAL;
  }
  else
  {
    estadoLlenado = SIN_CAUDAL;
  }

  if ((estadoLlenado == CON_CAUDAL) && (estadoDeControl == ESPERANDO_BLOQUE_CON_CAUDAL))
  {
    estadoDeControl = ESPERANDO_BLOQUE_SIN_CAUDAL;
  }

  if (estadoLlenado == SIN_CAUDAL && estadoDeControl == ESPERANDO_BLOQUE_SIN_CAUDAL)
  {
    estadoDeControl = ESPERANDO_BLOQUE_CON_CAUDAL;
    if (cicloLlenadoAgua > VOLUMEN_MINIMO_A_CLORAR)
    {
      solicitudClorado();
    }
  }
}