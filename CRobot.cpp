#include "CRobot.h"

CRobot::CRobot()
{
    //ctor
}

CRobot::~CRobot()
{
    //dtor
}

void CRobot::initRobot()
{
    m_servo.attach(PIN_SERVO);
    m_servo.write(0);
    m_capteurIR.initCapteur();
    m_tirette.initTirette();

}

void CRobot::servoPos(int pos)
{
  m_servo.write(pos);
}

int CRobot::etatTirette()
{
  return m_tirette.etat();
}

int CRobot::capteurIRValeur()
{
  return m_capteurIR.valeur();
}

void CRobot::printCapteurIR()
{
  m_capteurIR.printValeur();
}

void CRobot::printTirette()
{
  m_tirette.printEtat();
}

void CRobot::avancer(int speed)
{
  m_locomotion.lAvancer(speed);
}

void CRobot::tourner(int speed)
{
  m_locomotion.lTourner(speed);
}

void CRobot::printPulses()
{
  m_locomotion.printLPulses();  
}

void CRobot::robotA1Interrupt()
{
  m_locomotion.locomotionA1Interrupt();
}

void CRobot::robotA2Interrupt()
{
  m_locomotion.locomotionA2Interrupt();
}

void CRobot::robotB1Interrupt()
{
  m_locomotion.locomotionB1Interrupt();
}

void CRobot::robotB2Interrupt()
{
  m_locomotion.locomotionB2Interrupt();
}
