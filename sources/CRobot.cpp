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
    
    
    m_capteurIR.initCapteur();
    m_tirette.initTirette();
    m_locomotion.lStop();

}

void CRobot::servoPos(int pos)
{
  
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

void CRobot::avancer(unsigned int distance, int dir)
{
  m_locomotion.lAvancer(distance, dir);
}

void CRobot::turn(unsigned int angle, int dir)
{
  Serial.println("TEUR");
  m_locomotion.lTurn(angle, dir);
}

void CRobot::stop()
{
  m_locomotion.lStop();
}

void CRobot::goTo(int x, int y, bool detection)
{
  do{
    m_locomotion.lGoTo(x,y, detection);
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
  if(m_capteurIR.valeur() > SEUIL_IR) {
    m_locomotion.setFlag(true);
    Serial.println("SET FLAG!!!");
    Serial.println(m_capteurIR.valeur());
  }
  else m_locomotion.setFlag(false);
}