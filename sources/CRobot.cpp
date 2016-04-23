#include "../headers/CRobot.h"
#include "../headers/TimerFive.h"

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
    m_locomotion.lStop();

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

void CRobot::avancer(unsigned int distance, int speed)
{
  m_locomotion.lAvancer(distance, speed);
}

void CRobot::turn(unsigned int angle, int speed)
{
  m_locomotion.lTurn(angle, speed);
}

void CRobot::stop()
{
  m_locomotion.lStop();
}

void CRobot::goTo(int x, int y)
{
  do{
    m_locomotion.lGoTo(x,y);
    Serial.println(m_locomotion.getFlag());
  }while(m_locomotion.getFlag());
  Timer5.stop();
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

void CRobot::robotSpeedControl()
{
  m_locomotion.lSpeedControl();
}

void CRobot::robotObstacleDetection()
{
  Serial.println("Timer5");
  if(m_capteurIR.valeur() < SEUIL_IR) m_locomotion.setFlag(true);
  else m_locomotion.setFlag(false);
}