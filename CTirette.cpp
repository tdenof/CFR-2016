#include "CTirette.h"
#include "constantes.h"
#include <Arduino.h>
CTirette::CTirette()
{
   m_Tpin = PIN_TIRETTE;
    //ctor
}

CTirette::~CTirette()
{
    //dtor
}

void CTirette::initTirette()
{
    pinMode(m_Tpin,INPUT_PULLUP);
}

int CTirette::etat()
{
  int etat = digitalRead(m_Tpin);
  return !etat;
}

void CTirette::printEtat()
{
  Serial.print("tirette\t");
  Serial.println(etat());  
}
