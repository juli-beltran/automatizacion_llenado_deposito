#include "declaraciones.h"
void cloradoManual(void)
{

    if (estadoBombaCloro==LOW)
    {
        digitalWrite(RELE_CLORO, HIGH);
        estadoBombaCloro = HIGH;  
    }

      if (inicioContadorTiempoCloradoManual == false)
      {
        inicioContadorTiempoCloradoManual = true;
        tiempoCloradoManual = 0;

        banderaCloradoManualEfectuado = true;
      }
      else
      {
        tiempoCloradoManual++;
        pesoCalculadoCicloClorado = tiempoClorado * FACTOR_BOMBA_CLORO;
        pesoFinalCloro = Balanza.get_units(NUMERO_MUESTRAS_PESO);
        pesoMedidoCicloCloro = pesoCloro - pesoFinalCloro;
        volumenCloradoManual = pesoMedidoCicloCloro / DOSIS_CLORO;
        actualizaPantalla4_3_1();
      }
}