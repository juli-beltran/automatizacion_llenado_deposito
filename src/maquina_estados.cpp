// maquina de estados
#include "declaraciones.h"

void maquinaEstado(void)
{

  static uint8_t estadoMaquina = PANTALLA_1;
  static bool anteriorTic = 0;
  int accionUsuario = accionesUsusario();

  switch (estadoMaquina)
  {

    // pantalla 0///////////////////////////////////////////////////////////////////////////
  case PANTALLA_0:
    switch (accionUsuario)
    {
    case PULSADOR_1_CLICK:
      estadoMaquina = PANTALLA_1;
      dibujaPantalla1();
      break;
    default:
      if (tic0 != anteriorTic)
      {
        anteriorTic = tic1;
        actualizaPantalla0();
        break;
      }
    }
    break;
    // pantalla 1///////////////////////////////////////////////////////////////////////////
  case PANTALLA_1:
    switch (accionUsuario)
    {
    case PULSADOR_1_CLICK:
      estadoMaquina = PANTALLA_2;
      dibujaPantalla2();
      break;
    case PULSADOR_2_CLICK:
      estadoMaquina = PANTALLA_0;
      dibujaPantalla0();
      break;
    default:
      if (tic0 != anteriorTic)
      {
        anteriorTic = tic0;
        actualizaPantalla1();
        break;
      }
    }
    break;
    // pantalla 2//////////////////////////////////////////////////////////////////////////
  case PANTALLA_2:
    switch (accionUsuario)
    {
    case PULSADOR_1_CLICK:
      estadoMaquina = PANTALLA_3;
      dibujaPantalla3();
      break;
    case PULSADOR_2_CLICK:
      estadoMaquina = PANTALLA_1;
      dibujaPantalla1();
      break;
    default:
      if (tic0 != anteriorTic)
      {
        anteriorTic = tic0;
        actualizaPantalla2();
        break;
      }
    }
    break;
  // pantalla 3//////////////////////////////////////////////////////////////////////////////
  case PANTALLA_3:
    switch (accionUsuario)
    {
    case PULSADOR_1_CLICK:
      estadoMaquina = PANTALLA_4_1;
      dibujaPantalla4_1();
      break;
    case PULSADOR_2_CLICK:
      estadoMaquina = PANTALLA_2;
      dibujaPantalla2();
      break;
    default:
      if (tic0 != anteriorTic)
      {
        anteriorTic = tic1;
        actualizaPantalla3();
        break;
      }
    }
    break;
    // pantalla 4_1//////////////////////////////////////////////////////////////////////////////////////
  case PANTALLA_4_1:
    switch (accionUsuario)
    {
    case PULSADOR_1_CLICK:
      estadoMaquina = PANTALLA_4_2;
      dibujaPantalla4_2();
      banderaBorradoError = false;
      break;
    case PULSADOR_2_CLICK:
      estadoMaquina = PANTALLA_3;
      dibujaPantalla3();
      banderaBorradoError = false;
      contadorPresentacionBorradoDisplay = 0;
      break;
    case PULSADOR_1_PULSACION_LARGA:
      errorCaudalAguaInsuficiente = false;
      errorTiempoFuncionamientoBombaExcedido = false;
      banderaBorradoError = true;
      contadorPresentacionBorradoDisplay = 0;

    default:
      if (tic0 != anteriorTic)
      { // si NO_PULSADO
        anteriorTic = tic1;
        actualizaPantalla4_1();
        break;
      }
    }
    break;
    // pantalla 4_2///////////////////////////////////////////////////////////////////////////////////////
  case PANTALLA_4_2:
    switch (accionUsuario)
    {
    case PULSADOR_1_CLICK:
      estadoMaquina = PANTALLA_4_3;
      dibujaPantalla4_3();
      banderaBorradoError = false;
      contadorPresentacionBorradoDisplay = 0;
      break;
    case PULSADOR_2_CLICK:
      estadoMaquina = PANTALLA_4_1;
      dibujaPantalla4_1();
      banderaBorradoError = false;
      contadorPresentacionBorradoDisplay = 0;
      break;
    case PULSADOR_1_PULSACION_LARGA:
      errorClorado = false;
      updateEEPPOM(VOLUMEN_AGUA_NO_CLORADO_ACUMULADO, 0.0F);
      banderaBorradoError = true;
      contadorPresentacionBorradoDisplay = 0;
    default:
      if (tic0 != anteriorTic)
      {
        anteriorTic = tic1;
        actualizaPantalla4_2();
        break;
      }
    }
    break;
    // pantalla 4_3///////////////////////////////////////////////////////////////////////////////////////
  case PANTALLA_4_3:
    switch (accionUsuario)
    {
    case PULSADOR_1_CLICK:
      estadoMaquina = PANTALLA_4_4;
      dibujaPantalla4_4();
      break;
    case PULSADOR_2_CLICK:
      estadoMaquina = PANTALLA_4_2;
      dibujaPantalla4_2();
      break;
    case PULSADOR_1_PULSACION_LARGA:
      if (volumenAClorar == 0) // asegura que no este activo un ciclo de clorado automatico
      {
        bloqueoPorCloradoManual = true; // para bloquear clorado automatico
        pesoCloro = Balanza.get_units(NUMERO_MUESTRAS_PESO);
        estadoMaquina = PANTALLA_4_3_1;
        dibujaPantalla4_3_1();
      }
      break;
    default:
      if (tic0 != anteriorTic) // si NO_PULSADO
      {
        anteriorTic = tic1;
        actualizaPantalla4_3();
        break;
      }
    }
    break;
    // pantalla 4_3_1//////////////////////////////////
  case PANTALLA_4_3_1:
    static bool banderaPrimeraEntrada = true;
    static int contadorTiempoInactivo = 0;
    // controlar que ususario suelte el boton al entrar en el estado antes de iniciar nada
    if (banderaPrimeraEntrada == true)
    {
      if ((accionUsuario) != NULA)
      {
        break;
      }
      else
      {
        banderaPrimeraEntrada = false;
      }
    }
    // inicio del estado
    switch (accionUsuario)
    {
    case PULSADOR_2_CLICK:
      activacionCloradoManual=false;
      salidaDeCloradoManual();
      estadoMaquina = PANTALLA_4_3;
      dibujaPantalla4_3();
      break;

    case PULSADOR_1_PULSACION_LARGA:
      if(activacionCloradoManual==false)
      {
        activacionCloradoManual=true;
      }
      if(contadorTiempoInactivo!= 0)
      {
        contadorTiempoInactivo=0;
      }

      break;

    default:

      if (estadoBombaCloro == HIGH)
      {
        digitalWrite(RELE_CLORO, LOW);
        estadoBombaCloro = LOW;
      }
    //control tiempo inactivo
      if (tic0 != anteriorTic)
      {
        anteriorTic = tic1;
        actualizaPantalla4_3_1();
        if (accionUsuario == PULSADOR_1_PULSADO)
        {
          contadorTiempoInactivo = 0;
          break;
        }

        if (contadorTiempoInactivo > 20)
        { // cambio a estado4_3
          activacionCloradoManual=false;
          salidaDeCloradoManual();
          estadoMaquina = PANTALLA_4_3;
          dibujaPantalla4_3();
          break;
        }
        contadorTiempoInactivo++;
      }
      break;
    }
    break;
  // pantalla 4_4//////////////////////////////////////////////////////////////////////////////////////
  case PANTALLA_4_4:
    switch (accionUsuario)
    {
    case PULSADOR_2_CLICK:
      estadoMaquina = PANTALLA_4_3;
      dibujaPantalla4_3();
      break;

    default:
      if (tic0 != anteriorTic)
      { // si NO_PULSADO
        anteriorTic = tic1;
        actualizaPantalla4_4();
        break;
      }
    }
    break;
  
  default:
  break;
  }
}