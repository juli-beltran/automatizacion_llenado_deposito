
#include "declaraciones.h"

    
void setup() {
Serial.begin(9600);
    configurarGpio(); //configura pines IO
    Balanza.begin(SENSOR_PESO_DOUT, SENSOR_PESO_SCK); //pines bakanza
    Balanza.set_scale(FACTOR_BALANZA); // escala para convertir a gramos
    Lcd.init();// initialize the lcd 
    Lcd.noBacklight (); 
    //secuencia de verificacion de leds
    testLeds();
    //presentacion  pantalla bienvenida
    Lcd.backlight();
    Lcd.setCursor ( 3,1);
    Lcd.print ("Control Llenado");
    Lcd.setCursor ( 3,2);
    Lcd.print ("    V 1.0");
    //recupera anterior error clorado al resetear
    EEPROM.get (ERROR_CLORADO, errorClorado);
    //lectura peso inicial cloro, 5 muestras y generacion de aviso de nivel bajo 
    pesoCloro = Balanza.get_units(5);
    nivelCloroPorcentaje = static_cast <int> (pesoCloro * 100/ PESO_DEPOSITO_CLORO_LLENO);
    if(pesoCloro < MINIMO_PESO_CLORO)
    {
        errorNivelCloroBajo = true;
    }
    delay(2000);
    //entrada en pantalla 1
    Lcd.clear();
    dibujaPantalla1();
    
}

void loop() {
    static boolean anteriorTic0 = LOW;
    static boolean anteriorTic1 = LOW;

    generacionTics(); 
    maquinaEstado();
    
// PROCESOS QUE ACTUALIZAN CADA TIC0, 1 sg
     if (tic0 != anteriorTic0)
    { 
        anteriorTic0 = tic0;

        controlNivel();//lee nivel Agua;
        controlBombaAgua(); //activa o desactiva rele bomba, modifica estadoBombaAgua, activa error 2
        
        if(bloqueoPorCloradoManual==false)  
        {
            controlCicloClorado();
        }
        //actualiza leds
        actualizaLedBomba();
        actualizaLedCloro();
        actualizaLedNivel();        
    }
//PROCESOS QUE ACTUALIZAN CADA TIC2
    if(tic1 != anteriorTic1){
        anteriorTic1 = tic1;
        controlCicloLlenadoAgua();//cada 5 sg. resetea bloqueAgua, modifica bloqueAguaCopia usada como indicador de flujo, activa error 1, modifica ciclos clorado, modifica ciclo agua
    }
   
}
