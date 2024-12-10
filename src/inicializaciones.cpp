#include "declaraciones.h"

HX711 Balanza;
LiquidCrystal_I2C Lcd(0x27,20,4);
Pulsador pulsadorAdelante(PULSADOR_ADELANTE);
Pulsador pulsadorAtras(PULSADOR_ATRAS);


bool tic0 = LOW;
bool tic1 = LOW;
unsigned int tiempoClorado =0;
float pesoFinalCloro =0;
uint8_t nivelAgua = 0;
float pesoMedidoCicloCloro =0;
float volumenCloradoManual=0;
float pesoCloro = 0;
bool errorNivelCloroBajo = false;
float pesoCalculadoCicloClorado = 0;
volatile unsigned int bloqueAgua=0;

float cicloLlenadoAgua = 0; 
float caudal = 0;
bool estadoBombaAgua = LOW;
unsigned int tiempoFuncionamientoBombaAgua = 0;
unsigned int tiempoCloradoManual= 0;

float volumenAClorar = 0;
bool errorCaudalAguaInsuficiente = false;
bool errorTiempoFuncionamientoBombaExcedido = false;
 
bool estadoBombaCloro = LOW;
bool errorClorado= false;
bool banderaBorradoError= false;
bool bloqueoPorCloradoManual = false;
uint8_t contadorPresentacionBorradoDisplay= 0;



 int nivelCloroPorcentaje = 0;