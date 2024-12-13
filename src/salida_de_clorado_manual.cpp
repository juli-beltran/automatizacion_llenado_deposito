
#include "declaraciones.h"
void salidaDeCloradoManual(void)
{



if (estadoBombaCloro == HIGH)
      {
        digitalWrite(RELE_CLORO, LOW);
        estadoBombaCloro = LOW;
      }

      if (banderaCloradoManualEfectuado == true)
      {
        pesoCloro = pesoFinalCloro;
        updateEEPPOM(VOLUMEN_A_CLORAR_ULTIMO_CICLO, volumenCloradoManual);
        updateEEPPOM(PESO_CLORO_CALCULADO_ULTIMO_CICLO, pesoCalculadoCicloClorado);
        updateEEPPOM(TIEMPO_CLORADO_ULTIMO_CICLO, tiempoCloradoManual);
        updateEEPPOM(PESO_CLORO_MEDIDO_ULTIMO_CICLO, pesoMedidoCicloCloro);
        banderaCloradoManualEfectuado = false;
      }

      bloqueoPorCloradoManual = false;
      inicioContadorTiempoCloradoManual = false;
      banderaPrimeraEntrada = true;
      contadorTiempoInactivo = 0;
      
      }