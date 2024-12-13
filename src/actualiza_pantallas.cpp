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
  displayValue( 13, 1, 7, caudal , 1);
  displayValue( 14, 2, 6, volNoClor, 0);
  displayValue( 15, 3, 5, nivelCloroPorcentaje, 1);
}
void actualizaPantalla2(void)
{
  float VolAguaAc;
  EEPROM.get(VOLUMEN_AGUA_TOTAL_ACUMULADO, VolAguaAc);
  displayValue( 16, 0, 4, tiempoFuncionamientoBombaAgua/60);
  displayValue( 15, 1, 5, cicloLlenadoAgua, 1);
  displayValue( 13, 2, 7, caudal, 1);
  displayValue( 15, 3, 5, VolAguaAc , 1);
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


  displayValue( 14, 0, 6,volAClorar,1 );
  displayValue( 18, 1, 2,tiempoBombaCl );
  displayValue( 16, 2, 4,pesoCloTeor , 0);
  displayValue( 16, 3, 4, pesoCloReal , 0);
  
}
void actualizaPantalla4_1(void)
{
   
  if (banderaBorradoError==true)
  {
    if (contadorPresentacionBorradoDisplay<2)
    {
      Lcd.setCursor (0,0);
      Lcd.print (" sin errores       ");
      contadorPresentacionBorradoDisplay++;
      return;
    }
    else
    {
      
      banderaBorradoError = false; 
      Lcd.setCursor (0,0);
      Lcd.print (">BorraErroresBomba");
    }     
    return;  
  }
}
void actualizaPantalla4_2(void)
{
  
  if (banderaBorradoError==true)
  {
    if (contadorPresentacionBorradoDisplay<2)
    {
      Lcd.setCursor (0,1);
      Lcd.print (" sin errores       ");
      contadorPresentacionBorradoDisplay++;
      return;
    }
    else
    {
     
      banderaBorradoError = false; 
      
      Lcd.setCursor (0,1);
      Lcd.print(">BorraErroresCloro");
    }     
    return;  
  }
  return;
}


void actualizaPantalla4_3(void)
{

}
void actualizaPantalla4_4(void)
{

}
void actualizaPantalla4_3_1 (void)
{

  
  Lcd.setCursor(7, 1);
  if (estadoBombaCloro==HIGH)
  {
    Lcd.print("  ");
  }
  else
  {
    Lcd.print("No");
  }
  displayValue( 17, 1, 3,tiempoCloradoManual);


}
void displayValue(int col, int row,  unsigned int width, float value, int decimals) {
    // Mueve el cursor a la posición inicial
    Lcd.setCursor(col, row);
    
    // Genera el formato del número con el número de decimales deseados
    String formattedValue = String(value, decimals);
    if (formattedValue[0] == ' ') 
      {
          formattedValue = formattedValue.substring(1); // Eliminar el primer carácter
      }
    
    // Ajusta la longitud del texto con espacios en blanco al final
    while (formattedValue.length() < width) {
        formattedValue += " ";
    }
  
    
    // Asegura que no exceda el ancho asignado
    formattedValue = formattedValue.substring(0, width);
    // Escribe el texto formateado en el LCD
    Lcd.print(formattedValue);
}

// Función para formatear y mostrar un número int
void displayValue( int col, int row, unsigned int width, unsigned int value) {
    // Mueve el cursor a la posición inicial
    Lcd.setCursor(col, row);
    
    // Convierte el valor en String
    String formattedValue = String(value);

    
    // Ajusta la longitud del texto con espacios en blanco al final
    while (formattedValue.length() < width) {
        formattedValue += " ";
    }
    
    // Asegura que no exceda el ancho asignado
    formattedValue = formattedValue.substring(0, width);
    
    // Escribe el texto formateado en el LCD
    Lcd.print(formattedValue);
}