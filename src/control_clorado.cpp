
#include "declaraciones.h"







void controlCicloClorado() {  
  
  const uint8_t TIEMPO_ESTABILIZACION=5; // ciclos de entrada en funcion para estabilizar el peso del cloro
  static unsigned int contadorTiempoclorado = 0;  // Contador de tiempo de clorado
  static uint8_t contadorTiempoEstabilizacion = 0;  // Contador de tiempo de estabilización  
  float volumenNoClorado;// en litros, volumen acumulado que el clorado no ha sido correcto
  static unsigned int tiempoClorado = 0 ;// tiempo en segundos de bombeado de cloro
 
// si no hay volumen a clorar sale 
  if (volumenAClorar == 0){
    return;
  }

  // Si hay volumen y un error de clorado, acumula el volumen y sale
  if ( errorClorado == true) { 
    
    EEPROM.get(VOLUMEN_AGUA_NO_CLORADO_ACUMULADO, volumenNoClorado); 
    volumenNoClorado += volumenAClorar;
    updateEEPPOM(VOLUMEN_AGUA_NO_CLORADO_ACUMULADO, volumenNoClorado);
    volumenAClorar = 0;
    return;
  }

  // Si no hay tiempo de estabilización , o sea primera pasada
  if (contadorTiempoEstabilizacion == 0) {  
    

    if (estadoBombaCloro == LOW) {  // Inicia la bomba de cloro y calcula los parámetros
      
      pesoCalculadoCicloClorado = (volumenAClorar * DOSIS_CLORO ) +1;
      tiempoClorado = static_cast <int> (pesoCalculadoCicloClorado / FACTOR_BOMBA_CLORO) + 1;// redondeado siempre hacia arriba
      updateEEPPOM(VOLUMEN_A_CLORAR_ULTIMO_CICLO, volumenAClorar);
      updateEEPPOM(PESO_CLORO_CALCULADO_ULTIMO_CICLO, pesoCalculadoCicloClorado);
      updateEEPPOM(TIEMPO_CLORADO_ULTIMO_CICLO, tiempoClorado);
      pesoCloro = Balanza.get_units(NUMERO_MUESTRAS_PESO);  
      
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
    //contadorTiempoclorado = 0;  // Resetea el tiempo
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
  EEPROM.get(VOLUMEN_AGUA_NO_CLORADO_ACUMULADO, volumenNoClorado); 
  volumenNoClorado += volumenAClorar;  
  updateEEPPOM(VOLUMEN_AGUA_NO_CLORADO_ACUMULADO, volumenNoClorado); 
}
  contadorTiempoEstabilizacion = 0;
  volumenAClorar = 0;  // Finaliza la petición de clorado
}

void controlPeso() {
  float pesoFinalCloro;// en gr
  float PesoMedidoCicloCloro; //peso real cloro bombeado
  pesoFinalCloro = Balanza.get_units(NUMERO_MUESTRAS_PESO);
  PesoMedidoCicloCloro = pesoCloro - pesoFinalCloro;
  updateEEPPOM(PESO_CLORO_MEDIDO_ULTIMO_CICLO, PesoMedidoCicloCloro);
  pesoCloro = pesoFinalCloro;
  nivelCloroPorcentaje = static_cast <int> (pesoCloro * 100/ PESO_DEPOSITO_CLORO_LLENO);
  
  // Verifica el nivel mínimo de cloro y el error en el peso
  if (pesoCloro < MINIMO_PESO_CLORO) {
    errorNivelCloroBajo = HIGH;
    
  }
  if (abs(PesoMedidoCicloCloro - pesoCalculadoCicloClorado) > 0.1 * pesoCalculadoCicloClorado) {  // Factor de error ajustado al 10%
    errorClorado = HIGH;
    updateEEPPOM(ERROR_CLORADO, errorClorado);
    
  }
}