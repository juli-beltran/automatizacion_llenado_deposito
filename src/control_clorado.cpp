
#include "declaraciones.h"




float pesoCicloClorado = 0; //peso de cloro a bombear
unsigned int tiempoClorado = 0 ;// tiempo en segundos de bombeado de cloro


void controlCicloClorado() {  
  float volumenNoClorado;// en litros, volumen que el clorado no ha sido correcto
  const uint8_t TIEMPO_ESTABILIZACION=5; // ciclos de entrada en funcion para estabilizar el peso del cloro
  static unsigned int contadorTiempoclorado = 0;  // Contador de tiempo de clorado
  static uint8_t contadorTiempoEstabilizacion = 0;  // Contador de tiempo de estabilización

 
 
// si no hay volumen a clorar sale 
  if (volumenAClorar == 0){
    return;
  }

  // Si hay volumen y un error de clorado, acumula el volumen y sale
  if ( errorClorado == true) { 
    EEPROM.get(0, volumenNoClorado); 
    volumenNoClorado += volumenAClorar;
    EEPROM.update(0, volumenNoClorado);
    volumenAClorar = 0;
    return;
  }

  // Si no hay tiempo de estabilización 
  if (contadorTiempoEstabilizacion == 0) {  

    if (estadoBombaCloro == LOW) {  // Inicia la bomba de cloro y calcula los parámetros
      pesoCicloClorado = (volumenAClorar * DOSIS_CLORO ) +1;
      tiempoClorado = static_cast <int> (pesoCicloClorado / FACTOR_BOMBA_CLORO) + 1;// redondeado siempre hacia arriba
      EEPROM.update(24, volumenAClorar);
      EEPROM.update(12, pesoCicloClorado);
      EEPROM.update(20, tiempoClorado);
      pesoInicialCloro = balanza.get_units(NUMERO_MUESTRAS_PESO);  
      
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
if (errorClorado == HIGH) 
{  
  volumenNoClorado += volumenAClorar;  
  EEPROM.update(0, volumenNoClorado); 
}
  contadorTiempoEstabilizacion = 0;
  volumenAClorar = 0;  // Finaliza la petición de clorado
}

void controlPeso() {
  float pesoFinalCloro;// en gr
  float diferenciaPesoMedidoCloro; //peso real cloro bombeado
  pesoFinalCloro = balanza.get_units(NUMERO_MUESTRAS_PESO);
  diferenciaPesoMedidoCloro = pesoInicialCloro - pesoFinalCloro;
  EEPROM.update(16, diferenciaPesoMedidoCloro);
  pesoInicialCloro = pesoFinalCloro;
  nivelCloroPorcentaje = static_cast <int> (pesoInicialCloro * 100/ PESO_DEPOSITO_CLORO);
  
  // Verifica el nivel mínimo de cloro y el error en el peso
  if (pesoInicialCloro < MINIMO_PESO_CLORO) {
    errorNivelCloro = HIGH;
    
  }
  if (abs(diferenciaPesoMedidoCloro - pesoCicloClorado) > 0.1 * pesoCicloClorado) {  // Factor de error ajustado al 10%
    errorClorado = HIGH;
    EEPROM.update(28, errorClorado);
  }
}