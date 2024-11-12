
#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <HX711.h>
#include <EEPROM.h>
#include <stdint.h>
#include <Pulsador.h>
#ifndef DECLARACIONES_H
#define DECLARACIONES_H

 
extern LiquidCrystal_I2C lcd;
extern HX711 balanza;
extern Pulsador Pulsador1;


/////////////////constantes
  const unsigned long PERIODO_TIC0 = 250; //tic 0 cambio de nivel 250 ms
  const unsigned long ESCALADO_TIC1 = 4; //escalado para tic 1 cambio de nivel cada 1 sg
  const unsigned long  ESCALADO_TIC2 = 20;  //escalado para tic2 cambio de nivel cada 5 sg


  //pines leds-----------------------------------------------
    const uint8_t  LED_AGUA_ROJO=13;
    const uint8_t  LED_AGUA_VERDE=12;
    const uint8_t  LED_CLORO_ROJO=11;
    const uint8_t  LED_CLORO_VERDE=10;
    const uint8_t  LED_BOMBA_ROJO=9;
    const uint8_t  LED_BOMBA_VERDE=8;
  //pines reles-----------------------------------------------
    const uint8_t  RELE_CLORO=7;
    const uint8_t  RELE_AGUA=6;
  //pines sensores nivel---------------------------------------
    const uint8_t  SENSOR_NIVEL_MAX=14;//pin arduino A0
    const uint8_t  SENSOR_NIVEL_ALTO=15;//pin arduino A1
    const uint8_t  SENSOR_NIVEL_MEDIO=16;//pin arduino A2
  //pines sensor flujo ----------------------------------------
    const uint8_t  SENSOR_FLUJO=2;
  //comunicacion sensor peso-----------------------------------
    const uint8_t  SENSOR_PESO_SCK=3;
    const uint8_t  SENSOR_PESO_DOUT=4;
  //pines pulsadores----------------------------------------
    const uint8_t  PULSADOR_ADELANTE=5;
    const uint8_t PULSADOR_ATRAS = 17; //pin arduino A3

//nombres de los niveles posibles de agua en el tanque--------------------------------
    const uint8_t  MAX = 3; // Niveles del deposito. Maximo, detencion de bomba 850lt
    const uint8_t  ALTO = 2;//  750 lt , se activa la bomba para el llenado
    const uint8_t  MEDIO = 1;//500
    const uint8_t  BAJO = 0;// < 500 lt. Aviso nivel muy bajo, led rojo

//nombres estado llenado-------------------------------------

  const bool HAY_CAUDAL = true;
  const bool SIN_CAUDAL = false;
  const bool ESPERANDO_BLOQUE_CON_CAUDAL = true;
  const bool ESPERANDO_BLOQUE_SIN_CAUDAL = false; 

  //factores caudalimetro, bomba cloro y balanza----------------------------------------
  const float FACTOR_CAUDALIMETRO = 3.5; // en ml / imp  //
  const float FACTOR_BOMBA_CLORO = 1.42; //en ml / sg
  const float FACTOR_BALANZA = 416.4;
  // cinstantes ciclo agua---------------------------------------------------
  const unsigned int MAXIMO_TIEMPO_TICS_BOMBA = 60.0 * 60 * 1000 / PERIODO_TIC0 / ESCALADO_TIC1 ; //en tics. calculo: tiempo en minutos / PERIODO_TIC0 / ESCALADO_TIC asociado a la funcion *60*1000
   const unsigned long  FIN_CICLO_AGUA =  100.0 * 1000.0 / FACTOR_CAUDALIMETRO   ; // en impusos. calculo: cantidad de agua (litro)* 1000 /factor del sensor(2.25 ml/imp)
   const unsigned int MINIMO_BLOQUE_AGUA = 1 *PERIODO_TIC0 * ESCALADO_TIC2 /60 / FACTOR_CAUDALIMETRO;// en tics en el tiempo de la funcion. calculo:litros por minuto *PERIODO_TIC0 (ms) * ESCALADO_TIC_asignado a la funcion/60/factor del sensor de flujo (mml/imp)
  //comprueba un flujo minimo en impulsos del sensor, se mide en el tiempo de tic2 y si no es alcanzado genera el error1
  // constantes coclo clorado
  const uint8_t NUMERO_MUESTRAS_PESO = 5;
  const unsigned int MINIMO_PESO_CLORO = 500; //gr
  const unsigned int DOSIS_CLORO = 20;   // en gr por  tic /  con concentracion de 3% hipoclorito 20 gr/ 100 lt
  const unsigned int MINIMO_VOLUMEN_A_CLORAR = 20.0 *1000/ FACTOR_CAUDALIMETRO ;// en impulsos. litros *1000/ FACTOR_CAUDALIMETRO
 
//////////////////////declaracion variables 

//tics---------------------------------------------------
extern bool tic0; //timer  SEMIPERIODO_TIC0
extern bool tic1;// timer  tic0 x ESCALADO_TIC1 
extern bool tic2;// timmer tic0 x ESCALADO_TIC2

extern uint8_t nivelAgua ; // almacena nivel actual del deposito de agua (BAJO,MEDIO,ALTO,MAX)

extern bool error1; // flujo insuficiente se pone a cero al reiniciar o desde pulador reset 
extern bool error2; // tiempo  bomba en funcionamiento excedido se pone a cero al reiniciar o desde el pulsador reset
 extern bool errorClorado;
extern bool errorNivelCloro;
extern bool ledsApagados;//en HIGH mantiene todos los leds apagados, utilizada en el proceso de reset
extern uint8_t ciclosNoClorados; //se actualiza desde eeprom y se pone a cero desde pulsador  reset
extern volatile unsigned int bloqueAgua; // acumula la cantidad de pulsos del caudalimetro durante tic2
 extern unsigned int bloqueAguaCopia; // copia de bloque de agua para los calculos fuera la funcion de lectura de la interrupcion se actualiza cada 10 sg y registra si hay flujo
extern float caudal;
extern unsigned int cicloAgua; //acumula la cantidad total del ciclo, desde la variable bloqueAguaCopia
extern float litrosCicloAgua;
extern float litrosNoClorados;
extern bool estadoBombaAgua; // HIGH funciona bomba, LOW detenida
extern bool estadoBombaCloro; // HIGH funciona bomba, LOW detenida
extern unsigned int tiempoFuncionamientoBombaAgua;//declaracion contador interno de tiempo de funcionamiento de la bomba
extern unsigned int pesoInicialCloro;
extern unsigned int pesoFinalCloro;
extern unsigned int pesoCicloClorado;
extern unsigned long volumenNoClorado;
extern unsigned int volumenAClorar;
extern unsigned int tiempoClorado;



/////////////////////declaracion funciones  
void configurarGpio(void);
void generacionTics(void);
void testLeds (void);
void apagaLeds (void);
void confirmacionReset(unsigned char);
void actualizaLedNivel(void);
void actualizaLedBomba(void);
void actualizaLedCloro(void);
void actualizaLeds(bool);
void controlBombaAgua(void);
void solicitudClorado (void);
void controlCicloAgua(void);
void controlNivel(void);
void incrementoBloqueAgua(void);
void controlCicloClorado(void);
void controlPeso(void);
void calculos(void);
void actualizaPantalla1(void);
void dibujaPantalla1(void);
void dibujaPantalla2(void);
void actualizaPantalla2(void);
void dibujaPantalla3(void);
void actualizaPantalla3(void);
void lcdPrintEstadoBomba(void);
#endif
