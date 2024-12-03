
#include "pulsador.h"
// contructor
Pulsador::Pulsador(uint8_t _pinPulsador)

{
    this->Pulsador::pinPulsador = _pinPulsador;
    pinMode(Pulsador::pinPulsador, INPUT_PULLUP);
}

int Pulsador::estadoPulsador()
{
    Pulsador::estadoActualPulsador = digitalRead(Pulsador::pinPulsador);
    if (estadoActualPulsador != estadoAnteriorPulsador) //debounce
    {
        int contador = 0; //cuenta el numero fijado de lecturas iguales para darlas por buena
        bool controlEstado;
        do
        {
            controlEstado = digitalRead (pinPulsador); //nueva lectura
            if (controlEstado != estadoActualPulsador)// si no coincide cambia el valor anterior al actual 
            {
                estadoActualPulsador = controlEstado;
                contador = 0; //reinicia contador
                    
            }
            else// si coincide aumemta contador
            {
                contador ++;
            }
            delay(1);
        } while (contador<  FILTRO_DEBOUNCE);
    
    }//fin debounce

    if (Pulsador::estadoActualPulsador == NO_PULSADO)
    {
        if (Pulsador::estadoAnteriorPulsador == PULSADO)
        {
            Pulsador::estadoAnteriorPulsador = NO_PULSADO;
            if (millis() - tiempoInicioPulsacion < TIEMPO_CLICK_EXCEDIDO)
            {
                return CLICK;
            }
        }
        return NO_ACCION;
        
    }

    else// estado pulsador pulsado
    {
        if (Pulsador::estadoAnteriorPulsador == NO_PULSADO)
        {
            tiempoInicioPulsacion = millis();
            Pulsador::estadoAnteriorPulsador = PULSADO;
           
        }
        else //estado anterior pulsado
        {
            if (millis()-tiempoInicioPulsacion > TIEMPO_CLICK_EXCEDIDO)
            {
                return PRESIONADO;  
            }
            
        }
        return INICIO_PULSACION;    
    }
   
}


int Pulsador::tiempoPulsacion()
{
    if ((estadoAnteriorPulsador == PULSADO))
    {
        return static_cast <int> ((millis()-tiempoInicioPulsacion)/1000);
    }
    else
    {
        return 0;
    }
}
void Pulsador::actualiza ()
{
    estadoAnteriorPulsador = NO_PULSADO;
}
