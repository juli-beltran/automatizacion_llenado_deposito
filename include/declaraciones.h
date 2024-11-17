
#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <HX711.h>
#include <EEPROM.h>

//#include <stdint.h>
#include <Pulsador.h>


#ifndef DECLARACIONES_H
#define DECLARACIONES_H

 
extern LiquidCrystal_I2C lcd;
extern HX711 balanza;





//ASIGNACION DE PINES ARDUINO UNO
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

//CONSTANTES DE USO EN MAS DE UN FICHERO

//constantes generacion de tics
  const unsigned int PERIODO_TIC0 = 1000; //tic 0 cambio de nivel 1000 ms
  const unsigned int ESCALADO_TIC1 = 5; //escalado para tic 1 cambio de nivel cada 1 sg
  


//nombres de los niveles posibles de agua en el tanque
    const uint8_t  MAX  = 3;  // 850, maximo, detencion de bomba 850lt
    const uint8_t  ALTO = 2;  // 750, se activa la bomba para el llenado, led verde
    const uint8_t  MEDIO= 1;  // 500, aviso nivel, led amarillo
    const uint8_t  BAJO = 0;  // < 500 lt. Aviso nivel muy bajo, led rojo


 //factores caudalimetro, bomba cloro y balanza
  const float FACTOR_CAUDALIMETRO = 3.5F; // en ml / imp  //
  const float FACTOR_BOMBA_CLORO = 1.42F; //en ml / sg
  const float FACTOR_BALANZA = 416.4F;


  // cinstantes ciclo agua---------------------------------------------------
  const unsigned int MAXIMO_TIEMPO_BOMBA = 3600; // tiempo maximo de funcionamiento en sg 
  const float  FIN_CICLO_AGUA =  100 ; //litros finalizacion ciclo llenado, empieza clorado
  const float MINIMO_CAUDAL = 1; //caudal minimo en litros/min
  const float MINIMO_VOLUMEN_A_CLORAR = 20 ; // litros minimos ingresados para iniciar un clorado, genera error1
  // constantes coclo clorado
  const uint8_t NUMERO_MUESTRAS_PESO = 5;
  const unsigned int MINIMO_PESO_CLORO = 500; //gr
  const float  DOSIS_CLORO = 0.20;   // en gr/ lt con concentracion de 3% hipoclorito
  const unsigned int PESO_DEPOSITO_CLORO = 5000; // peso en gramos de cloro



//////////////////////declaracion variables globales

//tics---------------------------------------------------
extern bool tic0; //timer  SEMIPERIODO_TIC0
extern bool tic1;// timer  tic0 x ESCALADO_TIC1 


extern uint8_t nivelAgua ; // almacena nivel actual del deposito de agua (BAJO,MEDIO,ALTO,MAX)

extern bool error1; // flujo insuficiente se pone a cero al reiniciar o desde pulador reset 
extern bool error2; // tiempo  bomba en funcionamiento excedido se pone a cero al reiniciar o desde el pulsador reset
extern bool errorClorado;// no hay concordancia entre el tiempo de clorado y la diferencia de peso
extern bool errorNivelCloro; // nivel cloro bajo

extern volatile unsigned int bloqueAgua; // acumula la cantidad de pulsos del caudalimetro durante tic2
extern float litrosBloque; // pasa litros de agua del ciclo a la funcion que genera la peticion de clorado
extern float caudal; //caudal agua ingresada en litros/min 
extern float cicloAgua; //acumula la cantidad total del ciclo en litros, desde la variable bloqueAguaCopia


extern bool estadoBombaAgua; // HIGH funciona bomba, LOW detenida
extern bool estadoBombaCloro; // HIGH funciona bomba, LOW detenida
extern unsigned int tiempoFuncionamientoBombaAgua;//tiempo de funcionamiento de la bomba en sg
extern float pesoInicialCloro;// en gr



extern float volumenAClorar; //litros de agua a clorar, si esta variable no es cero se inicia el clorado

extern int nivelCloroPorcentaje; 
 



/////////////////////declaracion funciones  
void configurarGpio(void);
void generacionTics(void);
void testLeds (void);
void actualizaLedNivel(void);
void actualizaLedBomba(void);
void actualizaLedCloro(void);
void controlBombaAgua(void);
void solicitudClorado (void);
void controlCicloAgua(void);
void controlNivel(void);
void incrementoBloqueAgua(void);
void controlCicloClorado(void);
void controlPeso(void);
void actualizaPantalla1(void);
void dibujaPantalla1(void);
void dibujaPantalla2(void);
void actualizaPantalla2(void);
void dibujaPantalla3(void);
void actualizaPantalla3(void);
void dibujaPantalla4(void);
void lcdPrintEstadoBomba(void);
void maquinaEstado(void);

#endif
