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

if (error1){ 
  lcd.print("ErrCaudal");
  return;
}
if (error2){ 
  lcd.print("ErrTiempo");
  return;
}
lcd.print  ("SinError ");
  return;
}
//PANTALLA1----------------------------------------------------
void dibujaPantalla1(void) {
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("BombaAgua=");
  lcd.setCursor(1,1);
  lcd.print("Caudal[l/m]=");
  lcd.setCursor(1,2);
  lcd.print("VolNoClor[l]=");
  lcd.setCursor(1,3);
  lcd.print("NivelCloro[%]=");
}
void actualizaPantalla1(void) {

  lcd.setCursor(11, 0);
  lcdPrintEstadoBomba();
  lcd.setCursor(12, 1);
  lcd.print(caudal);
  lcd.setCursor(14, 2);
  lcd.print(tiempoFuncionamientoBombaAgua);
  lcd.setCursor(14, 3);
  lcd.print(nivelCloroPorcentaje);
   }    


//PANTALLA2------------------------------------------------
void dibujaPantalla2(void) {
   lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("BombaTiempo[m]=");
  lcd.setCursor(1,1);
  lcd.print("VolCicloAgua[l]=");
  lcd.setCursor(1,3);
  lcd.print("VolAguaAc[m3]"); 
  }
void actualizaPantalla2(void) {

  lcd.setCursor(16, 0);
  lcd.print(tiempoFuncionamientoBombaAgua);
  lcd.setCursor(17, 1);
  lcd.print(litrosCicloAgua);
  
  lcd.setCursor(15, 3);
  lcd.print(metros3volumenAcumulado);
   
  }
//PANTALLA_3-----------------------------------------------
void dibujaPantalla3(void){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(">BorraErroresBomba");
  lcd.setCursor(0,1);
  lcd.print(">BorraErroresCloro");

}


void actualizaPantalla3(void){

}
//PANTALLA4---------------------------------------------------------
void dibujaPantalla4(void) {
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("UltCicloCloroErr=");
  lcd.setCursor(1,1);
  lcd.print("PesoCloTeor=");
  lcd.setCursor(1,2);
  lcd.print("PesoCloReal=");
  lcd.setCursor(1,3);
  lcd.print("VolAClorar[l]=");
}