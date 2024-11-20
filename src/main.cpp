
#include "declaraciones.h"

    
void setup() {
    
    configurarGpio(); //configura pines IO
    Balanza.begin(SENSOR_PESO_DOUT, SENSOR_PESO_SCK); //pines bakanza
    Balanza.set_scale(FACTOR_BALANZA); // escala para convertir a gramos
    Lcd.init();// initialize the lcd 
    Lcd.noBacklight ();
    Serial.begin(9600); 
    //obtiene error clorado tras reset
    EEPROM.get(16, errorClorado);
    
    testLeds(); //secuencia de verificacion de leds
    //presentacion  pantalla bienvenida
    Lcd.backlight();
    Lcd.setCursor ( 3,1);
    Lcd.print ("control llenado");
    Lcd.setCursor ( 3,2);
    Lcd.print ("V 1.0");
    EEPROM.get(VOLUMEN_AGUA_TOTAL_ACUMULADO, volAguaTotalAcc);//recupera agua acumulada
    EEPROM.get (ERROR_CLORADO, errorClorado);//recupera anterior error clorado al resetear
    //lectura peso inicial cloro y generacion de aviso de nivel bajo 
    pesoCloro = Balanza.get_units(5);
    nivelCloroPorcentaje = static_cast <int> (pesoCloro * 100/ PESO_DEPOSITO_CLORO_LLENO);
    if(pesoCloro < MINIMO_PESO_CLORO)
    {
        errorNivelCloroBajo = HIGH;
    }
    delay(2000);
    Lcd.clear();
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
        controlCicloLlenadoAgua();//cada 5 sg. resetea bloqueAgua, modifica bloqueAguaCopia usada como indicador de flujo, activa error 1, modifica ciclos clorado, modifica ciclo agua
    }
  
}
