
#include "declaraciones.h"

HX711 balanza;
LiquidCrystal_I2C lcd(0x27,20,4);


bool ledsApagados = LOW;
unsigned int pesoInicialCloro = 0;
bool errorNivelCloro = LOW;
unsigned long volumenNoClorado = 0;

    
void setup() {
    configurarGpio();
    Serial.begin(9600);   
    balanza.begin(SENSOR_PESO_DOUT, SENSOR_PESO_SCK);
    balanza.set_scale(FACTOR_BALANZA);
    lcd.init();// initialize the lcd 
    lcd.noBacklight ();
    EEPROM.get(0, volumenNoClorado);
    
    testLeds();
    lcd.backlight();
    lcd.setCursor ( 3,1);
    lcd.print ("control llenado");
    lcd.setCursor ( 3,2);
    lcd.print ("V 1.0");
    pesoInicialCloro = balanza.get_units(5);
    if(pesoInicialCloro < MINIMO_PESO_CLORO){
        errorNivelCloro = HIGH;
    }
    delay(2000);
    lcd.clear();
    dibujaPantalla1();
    
}

void loop() {
    static boolean anteriorTic0 = LOW;
    static boolean anteriorTic1 = LOW;
    static boolean anteriorTic2 = LOW;

    generacionTics(); 
    maquinaEstado();
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if(tic0 != anteriorTic0){ //PROCESOS QUE ACTUALIZAN CADA TIC0
        anteriorTic0 = tic0;
        actualizaLeds(ledsApagados);
    } 



 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if(tic1 != anteriorTic1){//PROCESOS QUE ACTUALIZAN CADA TIC1
        anteriorTic1 = tic1;
        controlNivel();// actualiza nivel Agua;
        controlBombaAgua(); //activa o desactiva rele bomba, modifica estadoBombaAgua, activa error 2
        controlCicloClorado ();
        calculos();
    }


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if(tic2 != anteriorTic2){//PROCESOS QUE ACTUALIZAN CADA TIC2
        anteriorTic2 = tic2;
        controlCicloAgua();//cada 5 sg. resetea bloqueAgua, modifica bloqueAguaCopia usada como indicador de flujo, activa error 1, modifica ciclos clorado, modifica ciclo agua
    }
  
}
