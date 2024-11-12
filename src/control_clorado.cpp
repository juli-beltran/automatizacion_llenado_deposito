
#include "declaraciones.h"


bool estadoBombaCloro = LOW;
bool errorClorado= false;

unsigned int pesoCicloClorado = 0;
unsigned int tiempoClorado = 0 ;
unsigned int pesoFinalCloro = 0;

void controlCicloClorado() {  
  const uint8_t TIEMPO_ESTABILIZACION=5;
  static unsigned int contadorTiempoclorado = 0;  // Contador de tiempo de clorado
  static uint8_t contadorTiempoEstabilizacion = 0;  // Contador de tiempo de estabilización

 
 
// si no hay volumen a clorar sale 
  if (volumenAClorar == 0){
    return;
  }

  // Si hay volumen y un error de clorado, acumula el volumen y sale
  if (volumenAClorar != 0 && errorClorado == false) {  
    volumenNoClorado += volumenAClorar;
    EEPROM.update(0, volumenNoClorado);
    litrosNoClorados = volumenNoClorado * FACTOR_CAUDALIMETRO / 1000;//para lcd
    volumenAClorar = 0;
    return;
  }

  // Si no hay tiempo de estabilización y hay volumen a clorar sin error
  if (contadorTiempoEstabilizacion == 0 && volumenAClorar != 0 && errorClorado == LOW) {  

    if (estadoBombaCloro == LOW) {  // Inicia la bomba de cloro y calcula los parámetros
      pesoCicloClorado = (volumenAClorar / 100000.0) * DOSIS_CLORO;  
      tiempoClorado = pesoCicloClorado / FACTOR_BOMBA_CLORO;
      pesoInicialCloro = static_cast<int>(balanza.get_units(NUMERO_MUESTRAS_PESO));  
      
      // Activa bomba y resetea tiempo
      contadorTiempoclorado = 0;
      

      digitalWrite(RELE_CLORO, HIGH);
      estadoBombaCloro = HIGH;
      return;
    }
    
    // Si la bomba está encendida, controla el tiempo de clorado
    if (contadorTiempoclorado < tiempoClorado) {  
      contadorTiempoclorado++;
      return;
    }

    // Finaliza el ciclo de clorado
    digitalWrite(RELE_CLORO, LOW);  
    estadoBombaCloro = LOW;
    contadorTiempoclorado = 0;  // Resetea el tiempo
    contadorTiempoEstabilizacion = TIEMPO_ESTABILIZACION;// Activa tiempo de estabilización
    return;
      
  }

  // Cuenta regresiva para estabilización; solo sigue si ha terminado

if (contadorTiempoEstabilizacion > 1) {
    contadorTiempoEstabilizacion--;
    return;
}
  

  controlPeso();  // Controla el peso tras estabilización
  
  // Si se detectó un error en el ciclo de clorado, actualiza el volumen no clorado
  if (errorClorado == HIGH) {  
    volumenNoClorado += volumenAClorar;  
    EEPROM.update(0, volumenNoClorado); 
    litrosNoClorados = volumenNoClorado * FACTOR_CAUDALIMETRO / 1000;//para lcd
  }
  contadorTiempoEstabilizacion = 0;
  volumenAClorar = 0;  // Finaliza la petición de clorado
}

void controlPeso() {
  pesoFinalCloro = static_cast<int>(balanza.get_units(NUMERO_MUESTRAS_PESO));
  int diferenciaPesoMedidoCloro = pesoInicialCloro - pesoFinalCloro;
  
  // Verifica el nivel mínimo de cloro y el error en el peso
  if (pesoFinalCloro < MINIMO_PESO_CLORO) {
    errorNivelCloro = HIGH;
  }
  if (abs(diferenciaPesoMedidoCloro - pesoCicloClorado) > 0.1 * pesoCicloClorado) {  // Factor de error ajustado al 10%
    errorClorado = HIGH;
  }
}