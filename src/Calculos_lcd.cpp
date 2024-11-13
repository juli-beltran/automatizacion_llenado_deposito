#include "declaraciones.h"

 float caudal = 0;
 float litrosCicloAgua = 0;
 float litrosNoClorados = 0;
 int nivelCloroPorcentaje = 0;
 unsigned int metros3volumenAcumulado = 0;
 
void calculos() {//calculos para obtener valores validos para pasar a lcd
  litrosCicloAgua = cicloAgua * FACTOR_CAUDALIMETRO / 1000; //valor de ciclo de agua en litros para datos lcd
  caudal = bloqueAguaCopia * FACTOR_CAUDALIMETRO / 83.3333;// valor cakculado del caudalpara datos lcd
  nivelCloroPorcentaje = static_cast <int> (pesoInicialCloro * 100/ PESO_DEPOSITO_CLORO);
  litrosNoClorados = volumenNoClorado * FACTOR_CAUDALIMETRO / 1000;//para lcd
}