#include "../headers/CRobot.h"
#include "../headers/TimerFive.h"

CRobot::CRobot(): m_capteurIRD(PIN_CAPTEURD), m_capteurIRG(PIN_CAPTEURG)
{
    //ctor
}

CRobot::~CRobot()
{
    //dtor
}

void CRobot::initRobot()
{
    
    m_plier.init();
    delay(2000);
    m_rod.init();
    m_capteurIRD.initCapteur();
    m_capteurIRG.initCapteur();
    m_tirette.initTirette();
    m_locomotion.lStop();

}

void CRobot::servoPos(int pos)
{
  
}

bool CRobot::etatTirette()
{
  return m_tirette.etat();
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

void CRobot::goTo(int x, int y, int angleF, bool detection)
{
  do{
    m_locomotion.lGoTo(x,y,angleF, detection);
    Serial.println(m_locomotion.getFlag());
  }while(m_locomotion.getFlag());
  Timer5.stop();
}

void CRobot::openPlier(){
  m_plier.open();
}

void CRobot::straightPlier(){
  m_plier.straight();
}

void CRobot::closePlier(){
  m_plier.close();
}

void CRobot::deployRod()
{
  m_rod.deploy();
}

void CRobot::deployRod(int angle)
{
  m_rod.deploy(angle);
}

void CRobot::undeployRod()
{
  m_rod.undeploy();
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
  if(m_capteurIRD.valeur() > SEUIL_IR || m_capteurIRG.valeur() > SEUIL_IR) {
    m_locomotion.setFlag(true);
    Serial.println("SET FLAG!!!");
  }
  else m_locomotion.setFlag(false);
}