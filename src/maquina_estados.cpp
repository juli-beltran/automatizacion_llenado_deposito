//maquina de estados
#include"declaraciones.h"



void maquinaEstado(void) {

    static uint8_t estadoMaquina = 0;
    static bool anteriorTic = 0;
    Pulsador pulsadorAdelante (PULSADOR_ADELANTE);
    Pulsador pulsadorAtras (PULSADOR_ATRAS);
   

    enum estadosMaquina {

        PANTALLA_0,//ajuste iluminacion pantalla
        PANTALLA_1,//solo lectura, estado general de funcionamiento
        PANTALLA_2,// solo lectura, estado llenado 
        PANTALLA_3,// solo lectura, datos del ultimo ciclo clorado
        PANTALLA_4_1,//borrado errores bomba agua
        PANTALLA_4_2,//borrado errores bomba cloro
        PANTALLA_4_3,//accionamiento manual bomba de cloro
        PANTALLA_4_4 //calibrado balanza
    };

  switch (estadoMaquina)
  {

      // pantalla 0///////////////////////////////////////////////////////////////////////////
    case PANTALLA_0:
      if (pulsadorAdelante.lee() == PULSACION_CORTA)// trsnsicion a pantalla 1
      { 
        estadoMaquina = PANTALLA_1;
        dibujaPantalla1();
        break;
      }
      if (tic1 != anteriorTic)
      { //
        anteriorTic = tic1;
        actualizaPantalla0();
        break;
      }
      // pantalla 1///////////////////////////////////////////////////////////////////////////
    case PANTALLA_1:
      if (pulsadorAdelante.lee() == PULSACION_CORTA) // transicion a pantalla 2
      {
        estadoMaquina = PANTALLA_2;
        dibujaPantalla2();
        break;
      }
      if (pulsadorAtras.lee() == PULSACION_CORTA) //transicion al pantalla 0
      { 
        estadoMaquina = PANTALLA_0;
        dibujaPantalla0();
        break;
      }
      if (tic1 != anteriorTic)
      { //
        anteriorTic = tic1;
        actualizaPantalla1();
        break;
      }
    // pantalla 2//////////////////////////////////////////////////////////////////////////
    case PANTALLA_2:
      if (pulsadorAdelante.lee() == PULSACION_CORTA)//tansicion a pantalla 3
      { 
        estadoMaquina = PANTALLA_3;
        dibujaPantalla3();
        break;
      }
      if (pulsadorAtras.lee() == PULSACION_CORTA) //tansicion a pantalla 1
      { 
        estadoMaquina = PANTALLA_1;
        dibujaPantalla1();
        break;
      }
      if (tic1 != anteriorTic)
      { // si NO_PULSADO
        anteriorTic = tic1;
        actualizaPantalla2();
        break;
      }
    // pantalla 3//////////////////////////////////////////////////////////////////////////////
    case PANTALLA_3:  
      if (pulsadorAdelante.lee() == PULSACION_CORTA)// tansicion a pantalla 4_1
      { 
        estadoMaquina = PANTALLA_4_1;
        dibujaPantalla4_1();
        break;
      }  
      if (pulsadorAtras.lee() == PULSACION_CORTA)// tansicion a pantalla 2
      { 
        estadoMaquina = PANTALLA_2;
        dibujaPantalla2();
        break;
      } 
      if (tic1 != anteriorTic)
      { // si NO_PULSADO
        anteriorTic = tic1;
        actualizaPantalla3();
        break;
      }
      // pantalla 4_1//////////////////////////////////////////////////////////////////////////////////////
    case PANTALLA_4_1:
      if (pulsadorAdelante.lee() == PULSACION_CORTA)//transicion a pantalla 4_2
      { 
        estadoMaquina = PANTALLA_4_2;
        dibujaPantalla4_2();
        break;
      }
      if (pulsadorAtras.lee() == PULSACION_CORTA)// tansicion a pantalla 3
      { 
        estadoMaquina = PANTALLA_3;
        dibujaPantalla3();
        break;
      }
      if (tic1 != anteriorTic)
      { // si NO_PULSADO
        anteriorTic = tic1;
        actualizaPantalla4_1();
        break;
      }
      //pantalla 4_2///////////////////////////////////////////////////////////////////////////////////////
    case PANTALLA_4_2:
      if (pulsadorAdelante.lee() == PULSACION_CORTA)//transicion a pantalla 4_3
      { 
        estadoMaquina = PANTALLA_4_3;
        dibujaPantalla4_3();
        break;
      }
      if (pulsadorAtras.lee() == PULSACION_CORTA)// tansicion a pantalla 4_1
      { 
        estadoMaquina = PANTALLA_4_1;
        dibujaPantalla4_1();
        break;
      }
      if (tic1 != anteriorTic)
      { // si NO_PULSADO
        anteriorTic = tic1;
        actualizaPantalla4_2();
        break;
      }  
      //pantalla 4_3///////////////////////////////////////////////////////////////////////////////////////
    case PANTALLA_4_3:
      if (pulsadorAdelante.lee() == PULSACION_CORTA)//transicion a pantalla 4_4
      { 
        estadoMaquina = PANTALLA_4_4;
        dibujaPantalla4_4();
        break;
      }
      if (pulsadorAtras.lee() == PULSACION_CORTA)// tansicion a pantalla 4_2
      { 
        estadoMaquina = PANTALLA_4_2;
        dibujaPantalla4_2();
        break;
      }
      if (tic1 != anteriorTic) // si NO_PULSADO
      {
        anteriorTic = tic1;
        actualizaPantalla4_3();
        break;
      }
      // pantalla 4_4//////////////////////////////////////////////////////////////////////////////////////
    case PANTALLA_4_4:
      if (pulsadorAtras.lee() == PULSACION_CORTA)//tansicion a pantalla 4_3
      {
        estadoMaquina = PANTALLA_4_3;
        dibujaPantalla4_3();
        break;
      }
      if (tic1 != anteriorTic)
      { // si NO_PULSADO
        anteriorTic = tic1;
        actualizaPantalla4_4();
        break;
      }
  

  }  
  
}
