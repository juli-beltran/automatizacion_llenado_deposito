#include <Arduino.h>
#include "Pulsador.h"
// contructor
Pulsador::Pulsador(uint8_t pinPulsador) : estadoAnteriorPulsador(NO_PULSADO), bloqueoTrasPulsacionLarga(false)
{
    this->pinPulsador = pinPulsador;
    pinMode(Pulsador::pinPulsador, INPUT_PULLUP);
}
// lee accion del pulsador
int Pulsador::lee()
{
    Pulsador::estadoActualPulsador = digitalRead(Pulsador::pinPulsador);

    if (Pulsador::estadoActualPulsador == NO_PULSADO && Pulsador::estadoAnteriorPulsador == NO_PULSADO)
    {
        return NO_ACCION;
    }

    if (Pulsador::estadoActualPulsador == NO_PULSADO && Pulsador::estadoAnteriorPulsador == PULSADO)
    {
        Pulsador::estadoAnteriorPulsador = NO_PULSADO;
        if (Pulsador::bloqueoTrasPulsacionLarga == true)
        {
            Pulsador::bloqueoTrasPulsacionLarga = false;
            return NO_ACCION;
        }
        else
        {
            return PULSACION_CORTA;
        }
    }

    if (Pulsador::estadoActualPulsador == PULSADO && Pulsador::estadoAnteriorPulsador == NO_PULSADO)
    {
        tiempoInicioPulsacion = millis();
        Pulsador::estadoAnteriorPulsador = PULSADO;
    }
    if (Pulsador::estadoActualPulsador == PULSADO && Pulsador::estadoAnteriorPulsador == PULSADO && Pulsador::bloqueoTrasPulsacionLarga == false)
    {
        if (millis() - tiempoInicioPulsacion > TIEMPO_ACTIVACION_PRESIONADO_LARGO)
        {
            Pulsador::bloqueoTrasPulsacionLarga = true;
            return PULSACION_LARGA;
        }
        else
        {
            return NO_ACCION;
        }
    }

    return NO_ACCION;
}
