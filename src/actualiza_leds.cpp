#include <Arduino.h>
#include "declaraciones.h"

void actualizaLeds(bool off){//actualiza todos los leds
  if (off==HIGH ){
    apagaLeds();
    return;
  }
  actualizaLedBomba();
  actualizaLedCloro();
  actualizaLedNivel();
}
///////////////////////////////////////////////////ACTUALIZA LED CLORO////////////////////////////////////////////////////////////////////////////////////////77

void actualizaLedCloro(){//actualiza el led de cloro

  if (errorClorado == HIGH) {
    digitalWrite(LED_CLORO_VERDE, LOW);
    digitalWrite (LED_CLORO_ROJO, HIGH);
  return;
 }
 if (estadoBombaCloro ==HIGH) {
    digitalWrite(LED_CLORO_VERDE, tic1);
    digitalWrite (LED_CLORO_ROJO, LOW);
    return;
 }
  if (errorNivelCloro == HIGH) {
    digitalWrite(LED_CLORO_VERDE, HIGH);
    digitalWrite (LED_CLORO_ROJO, HIGH);
  return;
 }
 
  digitalWrite(LED_CLORO_VERDE, HIGH );
  digitalWrite (LED_CLORO_ROJO, LOW);
 }
///////////////////////////////////////////////////////////ACTUALIZA LED BOMBA//////////////////////////////////////////////////////////////////////////////
void actualizaLedBomba(){//actualiza el led de bomba
  
  if (error1 == true) {
    digitalWrite(LED_BOMBA_VERDE, LOW);
    digitalWrite (LED_BOMBA_ROJO, tic0);
  return;
 }
  if (error2 == true) {
    digitalWrite(LED_BOMBA_VERDE, LOW);
    digitalWrite (LED_BOMBA_ROJO, tic1);
  return;
 }
 if (estadoBombaAgua ==HIGH) {
    digitalWrite(LED_BOMBA_VERDE, HIGH);
    digitalWrite (LED_BOMBA_ROJO, LOW);
 }
 else{
  digitalWrite(LED_BOMBA_VERDE, LOW);
  digitalWrite (LED_BOMBA_ROJO, LOW);
 }
}
////////////////////////////////////////////////////////ACTUALIZA LED NIVEL AGUA///////////////////////////////////////////////////////////////////////7
void actualizaLedNivel(){ //actualiza el led de nivel
  //led nivel agua//////////////////////////////////////////////////////////////////////////////////////////////////7
  if (nivelAgua >= ALTO) {
    digitalWrite(LED_AGUA_ROJO, LOW); // apaga led rojo
    if (bloqueAguaCopia != 0) //si hay flujo
      digitalWrite (LED_AGUA_VERDE,tic1); // led verde parpadea
    else digitalWrite (LED_AGUA_VERDE, HIGH); //led verde fijo
    return;
  }

  if (nivelAgua == MEDIO) {
    if (bloqueAguaCopia != 0){
      digitalWrite (LED_AGUA_VERDE,tic1);
      digitalWrite (LED_AGUA_ROJO, tic1);
    }
    else {
      digitalWrite (LED_AGUA_VERDE, HIGH);
      digitalWrite (LED_AGUA_ROJO, HIGH);
    }
    return;
  }
  if (nivelAgua == BAJO) {
    digitalWrite(LED_AGUA_VERDE, LOW);
    if (bloqueAguaCopia != 0) 
      digitalWrite (LED_AGUA_ROJO,tic1);
    else 
      digitalWrite (LED_AGUA_ROJO, HIGH);
    return;
  }
  
  

  
}

///////////////////////////////////////////////////CONFIRMACION LED DE RESET//////////////////////////////////////////////////////////////////////////////////////

void confirmacionReset( unsigned char led){//ciclo parpadeo rapido confirmacion de reset
  apagaLeds();
  for (unsigned char i = 1; i<4; i++) {
  digitalWrite(led, HIGH);
  delay (50);
  digitalWrite(led,LOW);
  delay (50);
  }
}
////////////////////////////////////////////////////////////////APAGADO DE LEDS///////////////////////////////////////////////////////////////////////
void apagaLeds (){ //apaga todos los leds
  for ( int i = LED_BOMBA_VERDE; i <= LED_AGUA_ROJO; i++){
    digitalWrite(i, LOW);}
}


///////////////////////////////////////////////TEST LEDS//////////////////////////////////////////////////////////////////////////////////////////////////////
void testLeds () {
    digitalWrite(LED_AGUA_ROJO, HIGH);
    digitalWrite(LED_CLORO_ROJO, HIGH);
    digitalWrite(LED_BOMBA_ROJO, HIGH);
    delay(1000);
    digitalWrite(LED_AGUA_VERDE, HIGH);
    digitalWrite(LED_CLORO_VERDE, HIGH);
    digitalWrite(LED_BOMBA_VERDE, HIGH);
    delay(1000);
    digitalWrite(LED_AGUA_ROJO, LOW);//los tres leds en verde
    digitalWrite(LED_CLORO_ROJO, LOW);
    digitalWrite(LED_BOMBA_ROJO, LOW);
    delay(1000);
    digitalWrite(LED_AGUA_VERDE, LOW);//los tres leds apagados
    digitalWrite(LED_CLORO_VERDE, LOW);
    digitalWrite(LED_BOMBA_VERDE, LOW); 
    return;

  }