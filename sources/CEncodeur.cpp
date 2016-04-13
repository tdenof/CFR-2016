#include "../headers/CEncodeur.h"


CEncodeur::CEncodeur(int pisteAPin, int pisteBPin)
{
  m_pisteAPin = pisteAPin;
  m_pisteBPin = pisteBPin;
  pinMode(m_pisteAPin, INPUT);
  pinMode(m_pisteBPin, INPUT);
  m_pisteAValue = digitalRead(m_pisteAPin);
  m_pisteBValue = digitalRead(m_pisteBPin);
}


CEncodeur::~CEncodeur()
{
  
}


long CEncodeur::pulseCountValue()
{
  return m_pulseCount;
}

void CEncodeur::printPulse()
{
  Serial.println(m_pulseCount);
}

void CEncodeur::printPistes()
{
  Serial.print("Piste A : ") ;
  Serial.println(m_pisteAValue);
  Serial.print("Piste B : ") ;
  Serial.println(m_pisteBValue);
}

void CEncodeur::reset()
{
  m_pulseCount = 0;
}

void CEncodeur::pisteAInterrupt()
{
  if (digitalRead(m_pisteAPin) == HIGH) {

      if (!m_pisteBValue) {
       m_pisteAValue = true;
       m_pulseCount++;
      }

      else {
          m_pisteAValue = true;
          m_pulseCount--;
      }
  }

    else {

      if (m_pisteBValue) {
        m_pisteAValue = false;
        m_pulseCount++;
    }

      else {
          m_pisteAValue = false;
          m_pulseCount--;
      }
    }
}


void CEncodeur::pisteBInterrupt()
{
  if (digitalRead(m_pisteBPin) == HIGH) {

      if (!m_pisteAValue) {
       m_pisteBValue = true;
       m_pulseCount--;
      }

      else {
          m_pisteBValue = true;
          m_pulseCount++;
      }
  }

    else {

      if (!m_pisteAValue) {
        m_pisteBValue = false;
        m_pulseCount++;
    }

      else {
          m_pisteBValue = false;
          m_pulseCount--;
      }
    }
}


