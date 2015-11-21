#include "../headers/CCapteur_IR.h"
#include "../headers/constantes.h"
#include <Arduino.h>
CCapteur_IR::CCapteur_IR()
{
   m_Cpin = PIN_CAPTEUR;
    //ctor
}

CCapteur_IR::~CCapteur_IR()
{
    //dtor
}

void CCapteur_IR::initCapteur()
{
    pinMode(m_Cpin,INPUT);
}

int CCapteur_IR::valeur()
{
  int valeur = analogRead(m_Cpin);
  return valeur;
}

void CCapteur_IR::printValeur()
{
  Serial.print("capteur\t");
  Serial.println(valeur());
}


