#include<declaraciones.h>
void updateEEPPOM( int direccion,float valorNuevo)
{
  float valorAnterior;
  EEPROM.get(direccion,valorAnterior);
  if (valorNuevo!=valorAnterior )
  {
    EEPROM.put (direccion,valorNuevo);
  }
return;
}
void updateEEPPOM( int direccion,unsigned int valorNuevo)
{
  unsigned int valorAnterior;
  EEPROM.get(direccion,valorAnterior);
  if (valorNuevo!=valorAnterior )
  {
    EEPROM.put (direccion,valorNuevo);
  }
return;
}
void updateEEPPOM( int direccion,bool valorNuevo)
{
  bool valorAnterior;
  EEPROM.get(direccion,valorAnterior);
  if (valorNuevo!=valorAnterior )
  {
    EEPROM.put (direccion,valorNuevo);
  }
return;
}