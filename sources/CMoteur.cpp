#include "../headers/CMoteur.h"
#include <Arduino.h>

CMoteur::CMoteur(int dirPin1, int dirPin2, int pwmPin)
{
    //ctor
    m_dirPin1 = dirPin1;
    m_dirPin2 = dirPin2;
    m_pwmPin = pwmPin;
    m_power = 0;
    m_maxPower = 254;
    pinMode(m_pwmPin, OUTPUT);
    pinMode(m_dirPin1, OUTPUT);
    pinMode(m_dirPin2, OUTPUT);
    updatePower(m_power);
}

CMoteur::CMoteur(int dirPin1, int dirPin2, int pwmPin, int maxPower)
{
    //ctor
    m_dirPin1 = dirPin1;
    m_dirPin2 = dirPin2;
    m_pwmPin = pwmPin;
    m_power = 0;
    m_maxPower = maxPower;
    pinMode(m_pwmPin, OUTPUT);
    pinMode(m_dirPin1, OUTPUT);
    pinMode(m_dirPin2, OUTPUT);
    updatePower(m_power);
}

CMoteur::~CMoteur()
{
    //dtor
}

void CMoteur::updatePower(int power)
{
    m_power = power;
    if(power >= 0) {
        m_power = power;
        digitalWrite(m_dirPin1,HIGH);
        digitalWrite(m_dirPin2,LOW);
    }
  else {
        m_power = abs(power);
        digitalWrite(m_dirPin1,LOW);
        digitalWrite(m_dirPin2,HIGH);
    }

  if(m_power > m_maxPower)  {
     m_power = m_maxPower; 
     Serial.print("MAX Dépassé, New Power : ");
     Serial.println(m_power);
  }
  analogWrite(m_pwmPin,m_power);
  // Serial.println(m_power);
}
