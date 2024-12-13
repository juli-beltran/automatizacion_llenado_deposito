//fichero cabecera "automatizacion llenado deposito v2.0"
#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <HX711.h>
#include <EEPROM.h>
#include <Pulsador.h> //libreria propia

#ifndef DECLARACIONES_H
#define DECLARACIONES_H

 
extern LiquidCrystal_I2C Lcd; //declara objeto Lcd
extern HX711 Balanza;// declara objeto Balanza
extern Pulsador pulsadorAdelante;
extern Pulsador pulsadorAtras;






//ASIGNACION DE PINES ARDUINO UNO
//pines leds
const uint8_t LED_AGUA_ROJO = 13;
const uint8_t LED_AGUA_VERDE = 12;
const uint8_t LED_CLORO_ROJO = 11;
const uint8_t LED_CLORO_VERDE = 10;
const uint8_t LED_BOMBA_ROJO = 9;
const uint8_t LED_BOMBA_VERDE = 8;
//pines reles
const uint8_t RELE_CLORO = 7;
const uint8_t RELE_AGUA = 6;
//pines sensores nivel
const uint8_t SENSOR_NIVEL_MAX = 14;   // pin arduino A0
const uint8_t SENSOR_NIVEL_ALTO = 15;  // pin arduino A1
const uint8_t SENSOR_NIVEL_MEDIO = 16; // pin arduino A2
// pines sensor flujo
const uint8_t SENSOR_FLUJO = 2;
//comunicacion sensor peso
const uint8_t SENSOR_PESO_SCK = 3;
const uint8_t SENSOR_PESO_DOUT = 4;
// pines pulsadores
const uint8_t PULSADOR_ADELANTE = 17; // pin arduino A3
const uint8_t PULSADOR_ATRAS = 5;

//CONSTANTES DE USO EN MAS DE UN FICHERO
  //nombres de los niveles posibles de agua en el tanque
enum nivelesDeposito
{
  BAJO = 0,  // < 500 lt. Aviso nivel muy bajo, led rojo
  MEDIO = 1, // 500, aviso nivel, led amarillo
  ALTO = 2,  // 750, se activa la bomba para el llenado, led verde
  MAX = 3    // 850, maximo, detencion de bomba 850lt
};
enum direccionesEEPROM
{
  VOLUMEN_AGUA_NO_CLORADO_ACUMULADO = 0, // volumenNoClorado, float
  VOLUMEN_AGUA_TOTAL_ACUMULADO = 4,      // m3volumenAcumulado, float
  PESO_CLORO_CALCULADO_ULTIMO_CICLO = 8, // peso ultimo ciclo clorado calculado, float
  PESO_CLORO_MEDIDO_ULTIMO_CICLO = 12,   // peso ultimo iclo clorado real, float
  TIEMPO_CLORADO_ULTIMO_CICLO = 16,      // tiempo clorado ultimo ciclo, unsigned int
  VOLUMEN_A_CLORAR_ULTIMO_CICLO = 20,    // volumen a clorar ultimo ciclo, float
  ERROR_CLORADO = 24                     // error clorado
};
enum estadosMaquina
{

  PANTALLA_0,   // ajuste iluminacion pantalla
  PANTALLA_1,   // solo lectura, estado general de funcionamiento
  PANTALLA_2,   // solo lectura, estado llenado
  PANTALLA_3,   // solo lectura, datos del ultimo ciclo clorado
  PANTALLA_4_1, // borrado errores bomba agua
  PANTALLA_4_2, // borrado errores bomba cloro
  PANTALLA_4_3, // accionamiento manual bomba de cloro
  PANTALLA_4_4, // calibrado balanza
  PANTALLA_4_3_1// acciona bomba de cloro
};
enum accionesUsuario
{
  NULA,
  PULSADOR_1_PULSADO,
  PULSADOR_1_CLICK,
  PULSADOR_1_PULSACION_LARGA,
  PULSADOR_2_CLICK
};

//constantes generacion de tics
  const unsigned int PERIODO_TIC0 = 1000; //tic 0 cambio de nivel 1000 ms
  const unsigned int ESCALADO_TIC1 = 5; //escalado para tic 1 cambio de nivel cada 1 sg
  // factores caudalimetro, bomba cloro y balanza
  const float FACTOR_CAUDALIMETRO = (float) 50; // en ml / imp  //3.5
  const float FACTOR_BOMBA_CLORO = 1.42F; //en gr/ sg
  const float FACTOR_BALANZA = 416.4F;
  // cinstantes ciclo agua---------------------------------------------------
  const unsigned int MAXIMO_TIEMPO_FUNCIONAMIENTO_BOMBA = 3600; // tiempo maximo de funcionamiento en sg 
  const float  VOLUMEN_FINALIZACION_CICLO_AGUA =  15 ; //litros finalizacion ciclo llenado, empieza clorado
  const float VOLUMEN_MINIMO_A_CLORAR =10 ; // litros minimos ingresados para iniciar un clorado, genera error1
  const float MINIMO_CAUDAL = 1; //caudal minimo en litros/min

  // constantes coclo clorado
  const uint8_t NUMERO_MUESTRAS_PESO = 5;
  const unsigned int MINIMO_PESO_CLORO = 500; //gr
  const float  DOSIS_CLORO = 0.20;   // en gr/ lt con concentracion de 3% hipoclorito
  const unsigned int PESO_DEPOSITO_CLORO_LLENO = 5000; // peso en gramos de cloro



//////////////////////declaracion variables globales

//tics---------------------------------------------------
extern bool tic0; //timer  SEMIPERIODO_TIC0
extern bool tic1;// timer  tic0 x ESCALADO_TIC1 

extern volatile unsigned int bloqueAgua; // acumula la cantidad de pulsos del caudalimetro durante tic2
extern uint8_t nivelAgua ; // almacena nivel actual del deposito de agua (BAJO,MEDIO,ALTO,MAX)
extern float caudal; //caudal agua ingresada en litros/min 
extern float cicloLlenadoAgua; //acumula la cantidad total del ciclo en litros, desde la variable bloqueAguaCopia
extern unsigned int tiempoFuncionamientoBombaAgua;//tiempo de funcionamiento de la bomba en sg

extern bool errorCaudalAguaInsuficiente; // flujo insuficiente se pone a cero al reiniciar o desde pulador reset 
extern bool errorTiempoFuncionamientoBombaExcedido; // tiempo  bomba en funcionamiento excedido se pone a cero al reiniciar o desde el pulsador reset


extern bool estadoBombaAgua; // HIGH funciona bomba, LOW detenida
extern bool estadoBombaCloro; // HIGH funciona bomba, LOW detenida
extern bool banderaBorradoError;//utilizada para señalar el borrado de los errores en el lcd

extern uint8_t contadorPresentacionBorradoDisplay;

extern float pesoCloro;// en gr
extern int nivelCloroPorcentaje;

extern float volumenAClorar; //litros de agua a clorar, si esta variable no es cero se inicia el clorado
extern unsigned int tiempoClorado;
extern unsigned int tiempoCloradoManual;
extern float pesoCalculadoCicloClorado; //peso de cloro a bombear
extern bool bloqueoPorCloradoManual;
extern bool errorClorado;// no hay concordancia entre el tiempo de clorado y la diferencia de peso
extern bool errorNivelCloroBajo; // nivel cloro bajo
extern float pesoFinalCloro;// en gr
extern float pesoMedidoCicloCloro;
 
extern float volumenCloradoManual;
extern bool activacionCloradoManual;
extern bool inicioContadorTiempoCloradoManual;
extern bool banderaCloradoManualEfectuado;
extern bool banderaPrimeraEntrada;
extern bool contadorTiempoInactivo;

/////////////////////declaracion funciones  
void configurarGpio(void);
void generacionTics(void);
void testLeds (void);
void actualizaLedNivel(void);
void actualizaLedBomba(void);
void actualizaLedCloro(void);
void controlBombaAgua(void);
void solicitudClorado (void);
void controlCicloLlenadoAgua(void);
void controlNivel(void);
void incrementoBloqueAgua(void);
void controlCicloClorado(void);
void controlPeso(void);
void actualizaPantalla0(void);
void actualizaPantalla1(void);
void actualizaPantalla2(void);
void actualizaPantalla3(void);
void actualizaPantalla4_1(void);
void actualizaPantalla4_2(void);
void actualizaPantalla4_3(void);
void actualizaPantalla4_4(void);
void actualizaPantalla4_3_1(void);
void dibujaPantalla0(void);
void dibujaPantalla1(void);
void dibujaPantalla2(void);
void dibujaPantalla3(void);
void dibujaPantalla4_1(void);
void dibujaPantalla4_2(void);
void dibujaPantalla4_3(void);
void dibujaPantalla4_4(void);
void dibujaPantalla4_3_1(void);
int accionesUsusario (void);








void lcdPrintEstadoBomba(void);
void maquinaEstado(void);
void updateEEPPOM(int,float);
void updateEEPPOM(int,unsigned int);
void updateEEPPOM(int,bool);
void displayValue(int, int, unsigned int, float , int );
void displayValue( int , int , unsigned int , unsigned int ) ;
void cloradoManual(void);
void salidaDeCloradoManual(void);


#endif



