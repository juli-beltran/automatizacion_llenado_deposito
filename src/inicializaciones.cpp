#include "declaraciones.h"

HX711 balanza;
LiquidCrystal_I2C lcd(0x27,20,4);




uint8_t nivelAgua = 0;
bool ledsApagados = LOW;
unsigned int pesoInicialCloro = 0;
bool errorNivelCloro = LOW;
unsigned long volumenNoClorado = 0;
float metros3volumenAcumulado = 0;
volatile unsigned int bloqueAgua=0;

unsigned int bloqueAguaCopia = 0;
unsigned int cicloAgua = 0;

bool estadoBombaAgua = LOW;
unsigned int tiempoFuncionamientoBombaAgua = 0;

unsigned int volumenAClorar = 0;
bool error1 = false;
bool error2 = false;