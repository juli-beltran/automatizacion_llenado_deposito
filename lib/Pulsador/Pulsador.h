#include <Arduino.h>
#ifndef PULSADOR_H

enum estadoPulsador
{
    NO_ACCION,
    PRESIONADO, // mas de TIEMPO DE CLICK EXCEDIDO pulsado
    CLICK,
    INICIO_PULSACION //inicio de pulsacion, a continuacion sera CLICK o PRESIONADO
};
//lectura pulsador
const bool PULSADO = LOW;
const bool NO_PULSADO = HIGH;
const uint8_t FILTRO_DEBOUNCE = 15;
const unsigned int TIEMPO_CLICK_EXCEDIDO = 1800;

class Pulsador
{

private:
    uint8_t pinPulsador;
    unsigned long tiempoInicioPulsacion;
    bool estadoAnteriorPulsador = NO_PULSADO;
    bool estadoActualPulsador;

    uint8_t debonce;

public:
    Pulsador(uint8_t);
    int estadoPulsador(void);
    int tiempoPulsacion (void);
    void actualiza (void);
};
#endif