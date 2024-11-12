
#include <Arduino.h>
#include "declaraciones.h"

void configurarGpio (){ 
 pinMode(LED_AGUA_ROJO,OUTPUT);
 pinMode(LED_AGUA_VERDE,OUTPUT);
 pinMode(LED_CLORO_ROJO,OUTPUT);
 pinMode(LED_CLORO_VERDE,OUTPUT);
 pinMode(LED_BOMBA_ROJO,OUTPUT);
 pinMode(LED_BOMBA_VERDE,OUTPUT);
 //reles
 pinMode(RELE_CLORO,OUTPUT);
 pinMode(RELE_AGUA,OUTPUT);
 //sensores nivel
 pinMode(SENSOR_NIVEL_MAX,INPUT_PULLUP);
 pinMode(SENSOR_NIVEL_ALTO,INPUT_PULLUP);
 pinMode(SENSOR_NIVEL_MEDIO,INPUT_PULLUP);
 //sensor flujo
 pinMode(SENSOR_FLUJO,INPUT_PULLUP);
 //comunicacion sensor peso . se configuran al instanciar el objeto balanza
 //pinMode(SENSOR_PESO_CLK,INPUT);
 //pinMode(SENSOR_PESO_DAT,INPUT); 
 //pulsador reset
 pinMode(PULSADOR_ADELANTE,INPUT_PULLUP);
 pinMode(PULSADOR_ATRAS , INPUT_PULLUP);
 }
