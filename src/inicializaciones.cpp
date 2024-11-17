#include "declaraciones.h"

HX711 balanza;
LiquidCrystal_I2C lcd(0x27,20,4);




uint8_t nivelAgua = 0;

float pesoInicialCloro = 0;
bool errorNivelCloro = LOW;

volatile unsigned int bloqueAgua=0;
float litrosBloque = 0;
float cicloAgua = 0; 
float caudal = 0;
bool estadoBombaAgua = LOW;
unsigned int tiempoFuncionamientoBombaAgua = 0;

float volumenAClorar = 0;
bool error1 = false;
bool error2 = false;
 
bool estadoBombaCloro = LOW;
bool errorClorado= false;


 int nivelCloroPorcentaje = 0;