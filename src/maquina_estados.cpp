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
        PANTALLA_3
    };

    dibujaPantalla1();

  switch (estadoMaquina) {
      //pantalla 1///////////////////////////////////////////////////////////////////////////
    case PANTALLA_1:
      if (pulsadorAdelante.lee() == PULSACION_CORTA) {  // codigo que se ejecuta en la transicion al estado PANTALLA_2
        estadoMaquina = PANTALLA_2;
        dibujaPantalla2();
        break;
        }
      if(tic1 != anteriorTic){ //si NO_PULSADO
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
if (estadoBombaAgua == HIGH){ 
  lcd.print("run");
  return;
}
if (error1){ 
  lcd.print("err.flow");
  return;
}
if (error2){ 
  lcd.print("err.time");
  return;
}
lcd.print("stop");
  return;
}
//PANTALLA1////////////////////////////////////////////////////////////////////////////////////////
void dibujaPantalla1(void) {
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("Bomba agua");
  lcd.setCursor(1,1);
  lcd.print("Vol.ciclo=");
  lcd.setCursor(1,2);
  lcd.print("Tie.bomba=");
  lcd.setCursor(1,3);
  lcd.print("Peso clor=");
}
void actualizaPantalla1(void) {

  lcd.setCursor(12, 0);
  lcdPrintEstadoBomba();
  lcd.setCursor(12, 1);
  lcd.print(litrosCicloAgua);
  lcd.setCursor(12, 2);
  lcd.print(tiempoFuncionamientoBombaAgua);
  lcd.setCursor(12, 3);
  lcd.print(pesoInicialCloro);
   }    


//PANTALLA2/////////////////////////////////////////////////////////
void dibujaPantalla2(void) {
  }
void actualizaPantalla2(void) {
  }
//PANTALLA_3/////////////////////////////////////////////////////////
void dibujaPantalla3(void){

}
void actualizaPantalla3(void){

}