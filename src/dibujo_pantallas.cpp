#include"declaraciones.h"

void dibujaPantalla0(void)
{
  Lcd.clear();
  Lcd.setCursor(0, 0);
  Lcd.print(">Ajustar iluminacion");
}
void dibujaPantalla1(void)
{
  Lcd.clear();
  Lcd.setCursor(1, 0);
  Lcd.print("BombaAgua=");
  Lcd.setCursor(1, 1);
  Lcd.print("Caudal[l/m]=");
  Lcd.setCursor(1, 2);
  Lcd.print("VolNoClor[l]=");
  Lcd.setCursor(1, 3);
  Lcd.print("NivelCloro[%]=");
}
void dibujaPantalla2(void)
{
  Lcd.clear();
  Lcd.setCursor(1, 0);
  Lcd.print("BombaTiempo[m]=");
  Lcd.setCursor(1, 1);
  Lcd.print("VolCicloAg[l]=");
  Lcd.setCursor(1, 2);
  Lcd.print("Caudal[l/m]=");
  Lcd.setCursor(1, 3);
  Lcd.print("VolAguaAc[m3]=");
}
void dibujaPantalla3(void)
{
  Lcd.clear();
  Lcd.setCursor(1, 0);
  Lcd.print("VolAClorar[l]=");
  Lcd.setCursor(1, 1);
  Lcd.print("TiempoBombaCl[s]=");
  Lcd.setCursor(1, 2);
  Lcd.print("PesoCloTeor[g]=");
  Lcd.setCursor(1, 3);
  Lcd.print("PesoCloReal[g]=");
}
void dibujaPantalla4_1(void)
{
  Lcd.clear();
  Lcd.setCursor(0, 0);
  Lcd.print(">BorraErroresBomba");
  Lcd.setCursor(0, 1);
  Lcd.print(" BorraErroresCloro");
  Lcd.setCursor(0, 2);
  Lcd.print(" Clorado manual");
  Lcd.setCursor(0, 3);
  Lcd.print(" Calibrado balanza");
  
}
void dibujaPantalla4_2(void)
{
  Lcd.clear();
  Lcd.setCursor(0, 0);
  Lcd.print(" BorraErroresBomba");
  Lcd.setCursor(0, 1);
  Lcd.print(">BorraErroresCloro");
  Lcd.setCursor(0, 2);
  Lcd.print(" Clorado manual");
  Lcd.setCursor(0, 3);
  Lcd.print(" Calibrado balanza");
}
void dibujaPantalla4_3(void)
{
  Lcd.clear();
  Lcd.setCursor(0, 0);
  Lcd.print(" BorraErroresBomba");
  Lcd.setCursor(0, 1);
  Lcd.print(" BorraErroresCloro");
  Lcd.setCursor(0, 2);
  Lcd.print(">Clorado manual");
  Lcd.setCursor(0, 3);
  Lcd.print(" Calibrado balanza");
}
void dibujaPantalla4_4(void)
{
  Lcd.clear();
  Lcd.setCursor(0, 0);
  Lcd.print(" BorraErroresBomba");
  Lcd.setCursor(0, 1);
  Lcd.print(" BorraErroresCloro");
  Lcd.setCursor(0, 2);
  Lcd.print(" Clorado manual");
  Lcd.setCursor(0, 3);
  Lcd.print(">Calibrado balanza");
}

void dibujaPantalla4_3_1 (void)
{
  Lcd.clear();
  Lcd.setCursor(0, 0);
  Lcd.print(" Clorado Manual");
  Lcd.setCursor(0, 1);
  Lcd.print(" Bomba NoActiva t=");
  Lcd.setCursor(0, 2);
  Lcd.print(" Vol=     Peso=");
  Lcd.setCursor(0, 3);
  Lcd.print("VolAguaClorado="); 
}