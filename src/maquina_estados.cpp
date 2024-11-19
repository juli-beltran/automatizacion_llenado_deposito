//maquina de estados
#include"declaraciones.h"



void maquinaEstado(void) {

    static uint8_t estadoMaquina = 0;
    static bool anteriorTic = 0;
    Pulsador pulsadorAdelante (PULSADOR_ADELANTE);
    Pulsador pulsadorAtras (PULSADOR_ATRAS);
   

    enum estadosMaquina {

        PANTALLA_1,
        PANTALLA_2,
        PANTALLA_3,
        PANTALLA_4
    };


  switch (estadoMaquina) {
      //pantalla 1///////////////////////////////////////////////////////////////////////////
    case PANTALLA_1:
      if (pulsadorAdelante.lee() == PULSACION_CORTA) {  // codigo que se ejecuta en la transicion al estado PANTALLA_2
        estadoMaquina = PANTALLA_2;
        dibujaPantalla2();
        break;
        }
      if(tic1 != anteriorTic){ //
        anteriorTic = tic1;     
        actualizaPantalla1();
        break;     
        }
      
    
    //pantalla 2//////////////////////////////////////////////////////////////////////////
    case PANTALLA_2:
     if (pulsadorAdelante.lee() == PULSACION_CORTA) {  // codigo que se ejecuta en la transicion al nuevo estado PANTALLA_3
        estadoMaquina = PANTALLA_3;
        dibujaPantalla3();
        break;
      }
      if (pulsadorAtras.lee() == PULSACION_CORTA) {  // codigo que se ejecuta en la transicion al nuevo estado PANTALLA_1
        estadoMaquina = PANTALLA_1;
        dibujaPantalla1();
        break;
      }      
      if(tic1 != anteriorTic){ //si NO_PULSADO
        anteriorTic = tic1;     
        actualizaPantalla2();
        break;     
        }
    //pantalla3//////////////////////////////////////////////////////////////////////////////
    case PANTALLA_3:
    if (pulsadorAtras.lee() == PULSACION_CORTA) {  // codigo que se ejecuta en la transicion al nuevo estado PANTALLA_3
        estadoMaquina = PANTALLA_2;
        dibujaPantalla2();
        break;
      }
    if(tic1 != anteriorTic){ //si NO_PULSADO
        anteriorTic = tic1;     
        actualizaPantalla2();
        break;     
        }
      ////////////////////////////////////////////////////////////////////////////////


  }
  
  
}


void lcdPrintEstadoBomba(void){

if (errorCaudalAguaInsuficiente){ 
  Lcd.print("ErrCaudal");
  return;
}
if (errorTiempoFuncionamientoBombaExcedido){ 
  Lcd.print("ErrTiempo");
  return;
}
Lcd.print  ("SinError ");
  return;
}
//PANTALLA1----------------------------------------------------
void dibujaPantalla1(void) {
  Lcd.clear();
  Lcd.setCursor(1,0);
  Lcd.print("BombaAgua=");
  Lcd.setCursor(1,1);
  Lcd.print("Caudal[l/m]=");
  Lcd.setCursor(1,2);
  Lcd.print("VolNoClor[l]=");
  Lcd.setCursor(1,3);
  Lcd.print("NivelCloro[%]=");
}
void actualizaPantalla1(void) {

  Lcd.setCursor(11, 0);
  lcdPrintEstadoBomba();
  Lcd.setCursor(12, 1);
  Lcd.print(caudal);
  Lcd.setCursor(14, 2);
  Lcd.print(tiempoFuncionamientoBombaAgua);
  Lcd.setCursor(14, 3);
  Lcd.print(nivelCloroPorcentaje);
   }    


//PANTALLA2------------------------------------------------
void dibujaPantalla2(void) {
   Lcd.clear();
  Lcd.setCursor(1,0);
  Lcd.print("BombaTiempo[m]=");
  Lcd.setCursor(1,1);
  Lcd.print("VolCicloAgua[l]=");
  Lcd.setCursor(1,3);
  Lcd.print("VolAguaAc[m3]"); 
  }
void actualizaPantalla2(void) {

  Lcd.setCursor(16, 0);
  Lcd.print(tiempoFuncionamientoBombaAgua);
  Lcd.setCursor(17, 1);
  Lcd.print(cicloLlenadoAgua);
  
  Lcd.setCursor(15, 3);
  //lcd.print(metros3volumenAcumulado);
   
  }
//PANTALLA_3-----------------------------------------------
void dibujaPantalla3(void){
  Lcd.clear();
  Lcd.setCursor(0,0);
  Lcd.print(">BorraErroresBomba");
  Lcd.setCursor(0,1);
  Lcd.print(">BorraErroresCloro");

}


void actualizaPantalla3(void){

}
//PANTALLA4---------------------------------------------------------
void dibujaPantalla4(void) {
  Lcd.clear();
  Lcd.setCursor(1,0);
  Lcd.print("UltCicloCloroErr=");
  Lcd.setCursor(1,1);
  Lcd.print("PesoCloTeor=");
  Lcd.setCursor(1,2);
  Lcd.print("PesoCloReal=");
  Lcd.setCursor(1,3);
  Lcd.print("VolAClorar[l]=");
}
