#include"declaraciones.h"

void lcdPrintEstadoBomba(void)
{

  if (errorCaudalAguaInsuficiente)
  {
    Lcd.print("ErrCaudal");
    return;
  }
  if (errorTiempoFuncionamientoBombaExcedido)
  {
    Lcd.print("ErrTiempo");
    return;
  }
  Lcd.print("SinError ");
  return;
}
void actualizaPantalla0(void)
{
}
void actualizaPantalla1(void)
{
  float volNoClor;
  EEPROM.get(VOLUMEN_AGUA_NO_CLORADO_ACUMULADO, volNoClor); 
  Lcd.setCursor(11, 0);
  lcdPrintEstadoBomba();
  Lcd.setCursor(12, 1);
  Lcd.print(caudal);
  Lcd.setCursor(14, 2);
  Lcd.print(volNoClor);
  Lcd.setCursor(14, 3);
  Lcd.print(nivelCloroPorcentaje);
}
void actualizaPantalla2(void)
{
  float VolAguaAc;
  EEPROM.get(VOLUMEN_A_CLORAR_ULTIMO_CICLO, VolAguaAc);
  Lcd.setCursor(16, 0);
  Lcd.print(tiempoFuncionamientoBombaAgua);
  Lcd.setCursor(17, 1);
  Lcd.print(cicloLlenadoAgua);
  Lcd.setCursor(12, 3);
  Lcd.print(caudal); 
  Lcd.setCursor(15, 3) ; 
  Lcd.print(VolAguaAc);
}
void actualizaPantalla3(void)
{
  float volAClorar;
  unsigned int tiempoBombaCl;
  float pesoCloTeor;
  float pesoCloReal;
  EEPROM.get(VOLUMEN_A_CLORAR_ULTIMO_CICLO, volAClorar);
  EEPROM.get(TIEMPO_CLORADO_ULTIMO_CICLO, tiempoBombaCl);  
  EEPROM.get(PESO_CLORO_CALCULADO_ULTIMO_CICLO, pesoCloTeor);
  EEPROM.get(PESO_CLORO_MEDIDO_ULTIMO_CICLO, pesoCloReal);

  Lcd.setCursor(14, 0);
  Lcd.print(volAClorar);
  Lcd.setCursor(18, 1);
  Lcd.print(tiempoBombaCl);
  Lcd.setCursor(16, 3);
  Lcd.print(pesoCloTeor); 
  Lcd.setCursor(16, 3) ; 
  Lcd.print( pesoCloReal);
}
void actualizaPantalla4_1(void)
{

}
void actualizaPantalla4_2(void)
{

}
void actualizaPantalla4_3(void)
{

}
void actualizaPantalla4_4(void)
{

}