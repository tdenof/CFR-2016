#include "../headers/CCapteur_IR.h"
#include "../headers/constantes.h"
#include <Arduino.h>
CCapteur_IR::CCapteur_IR()
{
    //ctor
}

CCapteur_IR::CCapteur_IR(int pin)
{
    //ctor
    m_Cpin = pin;
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


