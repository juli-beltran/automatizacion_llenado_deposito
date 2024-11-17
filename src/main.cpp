
#include "declaraciones.h"

    
void setup() {
    
    configurarGpio(); //configura pines IO
    balanza.begin(SENSOR_PESO_DOUT, SENSOR_PESO_SCK); //pines bakanza
    balanza.set_scale(FACTOR_BALANZA); // escala para convertir a gramos
    lcd.init();// initialize the lcd 
    lcd.noBacklight ();
    Serial.begin(9600); 
    //obtiene error clorado tras reset
    EEPROM.get(16, errorClorado);
    
    testLeds(); //secuencia de verificacion de leds
    //presentacion  pantalla bienvenida
    lcd.backlight();
    lcd.setCursor ( 3,1);
    lcd.print ("control llenado");
    lcd.setCursor ( 3,2);
    lcd.print ("V 1.0");
    //lectura peso inicial cloro y generacion de aviso de nivel bajo
    pesoInicialCloro = balanza.get_units(5);
    nivelCloroPorcentaje = static_cast <int> (pesoInicialCloro * 100/ PESO_DEPOSITO_CLORO);
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


    generacionTics(); 
    maquinaEstado();
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if (tic0 != anteriorTic0)
    { // PROCESOS QUE ACTUALIZAN CADA TIC0
        anteriorTic0 = tic0;

        controlNivel();//lee nivel Agua;
        controlBombaAgua(); //activa o desactiva rele bomba, modifica estadoBombaAgua, activa error 2
        controlCicloClorado();
        actualizaLedBomba();
        actualizaLedCloro();
        actualizaLedNivel();
        
    }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if(tic1 != anteriorTic1){//PROCESOS QUE ACTUALIZAN CADA TIC2
        anteriorTic1 = tic1;
        controlCicloAgua();//cada 5 sg. resetea bloqueAgua, modifica bloqueAguaCopia usada como indicador de flujo, activa error 1, modifica ciclos clorado, modifica ciclo agua
    }
  
}
