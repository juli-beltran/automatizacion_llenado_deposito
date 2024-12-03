#include"declaraciones.h"

int accionesUsusario (void)
{



int estadoPulsadorAdelante;
int estadoPulsadorAtras;
int tiempoPulsadorAdelante;

estadoPulsadorAdelante = pulsadorAdelante.estadoPulsador(); 
tiempoPulsadorAdelante = pulsadorAdelante.tiempoPulsacion();

if (estadoPulsadorAdelante == CLICK)
{
    pulsadorAtras.actualiza();
    return PULSADOR_1_CLICK;
}

if (estadoPulsadorAdelante == PRESIONADO)
{
    pulsadorAtras.actualiza();
    if (tiempoPulsadorAdelante > 5)
    {
        return PULSADOR_1_PULSACION_LARGA;
    }
    else
    {
        return PULSADOR_1_PULSADO;
    }
}

estadoPulsadorAtras = pulsadorAtras.estadoPulsador();
if (estadoPulsadorAtras == CLICK)
{
    return PULSADOR_2_CLICK;
}

return NULA;
}