#include <Arduino.h>
#ifndef PULSADOR_H
#define PULSADOR_H
enum lecturasPulsador
{
    NO_ACCION,
    PULSACION_CORTA,
    PULSACION_LARGA
};

const bool PULSADO = LOW;
const bool NO_PULSADO = HIGH;
const unsigned long TIEMPO_ACTIVACION_PRESIONADO_LARGO = 5000L;

class Pulsador
{

private:
    uint8_t pinPulsador;
    unsigned long tiempoInicioPulsacion;
    bool estadoAnteriorPulsador;
    bool estadoActualPulsador;
    bool bloqueoTrasPulsacionLarga;

public:
    Pulsador(uint8_t);
    int lee(void);
};

#endif