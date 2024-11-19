#include "declaraciones.h"

HX711 Balanza;
LiquidCrystal_I2C Lcd(0x27,20,4);




uint8_t nivelAgua = 0;
float pesoCalculadoCicloClorado = 0; //peso de cloro a bombear
unsigned int tiempoClorado = 0 ;// tiempo en segundos de bombeado de cloro
float pesoInicialCloro = 0;
bool errorNivelCloroBajo = LOW;

volatile unsigned int bloqueAgua=0;

float cicloLlenadoAgua = 0; 
float caudal = 0;
bool estadoBombaAgua = LOW;
unsigned int tiempoFuncionamientoBombaAgua = 0;

float volumenAClorar = 0;
bool errorCaudalAguaInsuficiente = false;
bool errorTiempoFuncionamientoBombaExcedido = false;
 
bool estadoBombaCloro = LOW;
bool errorClorado= false;


 int nivelCloroPorcentaje = 0;