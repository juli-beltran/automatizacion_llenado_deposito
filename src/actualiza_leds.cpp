#include "declaraciones.h"


//actualiza el led de cloro
void actualizaLedCloro()
{

  if (errorClorado == true)             //error clorado led rojo encendido
  {
    digitalWrite(LED_CLORO_VERDE, LOW);
    digitalWrite(LED_CLORO_ROJO, HIGH);
    return;
  }
  if (estadoBombaCloro == HIGH)         //bomba cloro funcionando led verde intermitente
  {
    digitalWrite(LED_CLORO_VERDE, tic1);
    digitalWrite(LED_CLORO_ROJO, LOW);
    return;
  }
  if (errorNivelCloroBajo == true)          // nivel cloro bajo led amarillo
  {
    digitalWrite(LED_CLORO_VERDE, HIGH);
    digitalWrite(LED_CLORO_ROJO, HIGH);
    return;
  }

  digitalWrite(LED_CLORO_VERDE, HIGH);  // sin incidencias led verde
  digitalWrite(LED_CLORO_ROJO, LOW);
}

//actualiza el led de bomba
void actualizaLedBomba()
{
  if (errorCaudalAguaInsuficiente == true || errorTiempoFuncionamientoBombaExcedido == true)
  {
    digitalWrite(LED_BOMBA_VERDE, LOW);//con algun error led rojo
    digitalWrite(LED_BOMBA_ROJO, HIGH);
    return;
  }
  if (estadoBombaAgua == HIGH)
  {
    digitalWrite(LED_BOMBA_VERDE, HIGH);//en funcionamiento  led verde
    digitalWrite(LED_BOMBA_ROJO, LOW);
  }
  else
  {
    digitalWrite(LED_BOMBA_VERDE, LOW);//apagada, led apagado
    digitalWrite(LED_BOMBA_ROJO, LOW);
  }
}

//actualiza el led de nivel agua
void actualizaLedNivel()
{
  if (nivelAgua >= ALTO)
  {
    digitalWrite(LED_AGUA_ROJO, LOW); // apaga led rojo
    if (caudal != 0)         // si hay flujo led verde parpadea
      digitalWrite(LED_AGUA_VERDE, tic0);
    else
      digitalWrite(LED_AGUA_VERDE, HIGH); // si no hay flujo led verde fijo
    return;
  }
  if (nivelAgua == MEDIO)
  { // led rojo + verde para hacer amarillo
    if (caudal != 0)
    {
      digitalWrite(LED_AGUA_VERDE, tic0);
      digitalWrite(LED_AGUA_ROJO, tic0);
    }
    else
    {
      digitalWrite(LED_AGUA_VERDE, HIGH);
      digitalWrite(LED_AGUA_ROJO, HIGH);
    }
    return;
  }
  if (nivelAgua == BAJO)
  { // led rojo
    digitalWrite(LED_AGUA_VERDE, LOW);
    if (caudal != 0)
      digitalWrite(LED_AGUA_ROJO, tic0);
    else
      digitalWrite(LED_AGUA_ROJO, HIGH);
    return;
  }
}

//test de leds se enciende secuencialmente unos tras otro
void testLeds()
{
  digitalWrite(LED_AGUA_ROJO, HIGH); // rojo
  digitalWrite(LED_CLORO_ROJO, HIGH);
  digitalWrite(LED_BOMBA_ROJO, HIGH);
  delay(1000);
  digitalWrite(LED_AGUA_VERDE, HIGH); // amarillo
  digitalWrite(LED_CLORO_VERDE, HIGH);
  digitalWrite(LED_BOMBA_VERDE, HIGH);
  delay(1000);
  digitalWrite(LED_AGUA_ROJO, LOW); // verde
  digitalWrite(LED_CLORO_ROJO, LOW);
  digitalWrite(LED_BOMBA_ROJO, LOW);
  delay(1000);
  digitalWrite(LED_AGUA_VERDE, LOW); // los tres leds apagados
  digitalWrite(LED_CLORO_VERDE, LOW);
  digitalWrite(LED_BOMBA_VERDE, LOW);
  return;
}