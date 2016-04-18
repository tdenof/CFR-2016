#include "../headers/CLocomotion.h"
#include "../headers/TimerThree.h"

#include "../headers/zoneInterdite.h"
#include <Arduino.h>

CLocomotion::CLocomotion() :  m_etat({X_INIT,Y_INIT,THETA_INIT,SPEED_INIT,DIR_INIT}), 
m_moteurD(PIN_M1IN1,PIN_M1IN2,PIN_M1PWM), 
m_moteurG(PIN_M2IN1,PIN_M2IN2,PIN_M2PWM), 
m_encodeurD(PIN_A1,PIN_B1), m_encodeurG(PIN_A2,PIN_B2), 
m_speedConsigne(0), m_speedErrorSum(0), m_speedErrorPrev(0)
{
   //ctor
   

}

CLocomotion::~CLocomotion()
{
    //dtor
}

etatLocomotion CLocomotion::goTo(int x, int y)
{
  int distance = sqrt(pow(x-m_etat.x,2)+pow(y-m_etat.y,2));
  int phi = asin((y-m_etat.y)/distance);
  if(x-m_etat.x<0) phi = 180- phi;
  int psi = phi - m_etat.theta;
  if(abs(psi) < 180){
    if(psi > 0) lTurn(psi,RIGHT);
    else lTurn(-psi,LEFT);
  }
  else{
    if(psi > 0) lTurn(360-psi,LEFT);
    else lTurn(360+psi,RIGHT);
  }

  lAvancer(distance,FORWARD);
}
etatLocomotion CLocomotion::getCurrentState()
{
    etatLocomotion pos;
    pos = {getCurrentX(),getCurrentY(),getCurrentTheta(),getCurrentSpeed()};
    return pos;
}

bool CLocomotion::eviter()
{
    return evitementCarre();
}

bool CLocomotion::appartientZoneInterdite(int x, int y)  // determine si une position est autoris��e ou non
{
    int i;
    for(i=0;i<NB_ZONEINTERDITE;i++)
    {
        if( (x <= m_zoneInterdite[i].xFin && x >= m_zoneInterdite[i].xDebut) && (y <= m_zoneInterdite[i].yFin && y >= m_zoneInterdite[i].yDebut) )  return true;
    }
    return false;
}

bool CLocomotion::traverseZoneInterdite(int distance) // determine si un trajet est autoris�� ou non
{
    int i,j;
    for (i=0;i<NB_ZONEINTERDITE;i++)
    {
        for(j=1;j<abs(distance);j+=10)
        {
            if(appartientZoneInterdite(calculXEvitementCarre(j*distance/abs(distance)),calculYEvitementCarre(j*distance/abs(distance)))) return true;
        }
    }
    return false;
}

bool CLocomotion::evitementCarre() // Un type d'evitement
{
   // rotation d'un angle Pi/2 dans le sens horaire si possible
    if(!traverseZoneInterdite(DISTANCE_EVITEMENT))
       {
            goTo(calculXEvitementCarre(DISTANCE_EVITEMENT),calculYEvitementCarre(DISTANCE_EVITEMENT));
                       
            return true;
        }
     // rotation d'un angle Pi/2 dans le sens anti-horaire si possible
      if(!traverseZoneInterdite(-DISTANCE_EVITEMENT))
       {
            goTo(calculXEvitementCarre(-DISTANCE_EVITEMENT),calculYEvitementCarre(-DISTANCE_EVITEMENT));
           
            return true;
        }
     return false; // cas o�� les 2 positions sont interdites (peu probable dans notre cas, �� ��tudier)
    }

int CLocomotion::calculXEvitementCarre(int distance)
{
    return getCurrentX() + distance*cos(getCurrentTheta());
}

int CLocomotion::calculYEvitementCarre(int distance)
{
    return getCurrentY()+ distance*sin(getCurrentTheta());
}

int CLocomotion::ticksToSpeed(int ticks){
  int speed = ticks;
  return speed;
}

// MUTATEURS

// ACCESSEURS
int CLocomotion::getCurrentX()
{
    return m_etat.x;
}

int CLocomotion::getCurrentY()
{
    return m_etat.y;
}

int CLocomotion::getCurrentTheta()
{
    return m_etat.theta;
}

int CLocomotion::getCurrentSpeed()
{
    return m_etat.speed;
}

void CLocomotion::lAvancer (unsigned int distance, int dir)
{
  if (distance == 0) return;
  resetPulses();
  unsigned int fPulses = 360L*distance/(PI*WHEEL_DIAMETER);
  m_etat.dir = dir;
  m_speedConsigne=40;
  lPositionControl(fPulses);
  lStop();
} 

void CLocomotion::lTurn (unsigned int angle, int dir)
{
  if (angle == 0) return;
  resetPulses();
  unsigned int fPulses = angle*BASE_DIAMETER/WHEEL_DIAMETER;
  m_etat.dir = dir;
  m_speedConsigne=40;
  lPositionControl(fPulses);
  lStop();
}

void CLocomotion::lStop()
{
  while(m_speedConsigne > 40){
    m_mPulses = (abs(m_encodeurD.pulseCountValue()) + abs(m_encodeurG.pulseCountValue()))/2;
    m_speedConsigne -= 5;
    updatePower(m_speedConsigne);
    updateEtat();
    delay(20);
  }
}

void CLocomotion::printLPulses()
{
  Serial.print("Encodeur D : ");
  m_encodeurD.printPulse();
  Serial.print("Encodeur G : ");
  m_encodeurG.printPulse();
  Serial.print("Difference : ");
  Serial.println(abs(m_encodeurD.getPulseCount()) - abs(m_encodeurG.getPulseCount()));   
}

void CLocomotion::callback_sensors()
{
  long pulses_moy = (abs(m_encodeurD.getPulseCount())+abs(m_encodeurG.getPulseCount()))/2; // moy pulses
  resetPulses(); // set pulses to 0
  updateEtat();
 
}

void CLocomotion::lSpeedControl()
{
    int speedError = m_speedConsigne - m_etat.speed; //error
    m_speedErrorSum += speedError; //integration
    int speedErrorDerivative = speedError - m_speedErrorPrev;// action derivee
    m_speedErrorPrev = speedError;
    int command = KP*speedError + KI*m_speedErrorSum + KD*m_speedErrorPrev;
    int commandD = command + KR*m_dPulses;
    int commandG = command - KR*m_dPulses;
    updatePower(commandD,commandG);
    
}

void CLocomotion::lPositionControl(unsigned int fPulses)
{
  Timer3.start();
  while(m_mPulses < fPulses && !m_flag ){
    m_mPulses = (abs(m_encodeurD.pulseCountValue()) + abs(m_encodeurG.pulseCountValue()))/2;
    m_dPulses = (abs(m_encodeurD.pulseCountValue()) - abs(m_encodeurG.pulseCountValue()))/2;
    if(fPulses - m_mPulses < 2048 && m_speedConsigne > SPEEDMIN) m_speedConsigne-=5;
    else if(m_speedConsigne < SPEEDMAX) m_speedConsigne+=5;
      
  updateEtat();
    
  delay(20);
  }
  Timer3.stop();
}

void CLocomotion::updatePower(int power)
{
  switch (m_etat.dir){
    case FORWARD :
      m_moteurG.updatePower(power);
      m_moteurD.updatePower(power);
      break;
    case BACKWARD :
      m_moteurG.updatePower(-power);
      m_moteurD.updatePower(-power);
      break;
    case RIGHT :
      m_moteurG.updatePower(power);
      m_moteurD.updatePower(-power);
      break;
    case LEFT :
      m_moteurG.updatePower(-power);
      m_moteurD.updatePower(power);
      break;
     }
}

void CLocomotion::updatePower(int powerD, int powerG)
{
  switch (m_etat.dir){
    case FORWARD :
      m_moteurG.updatePower(powerG);
      m_moteurD.updatePower(powerD);
      break;
    case BACKWARD :
      m_moteurG.updatePower(-powerG);
      m_moteurD.updatePower(-powerD);
      break;
    case RIGHT :
      m_moteurG.updatePower(powerG);
      m_moteurD.updatePower(-powerD);
      break;
    case LEFT :
      m_moteurG.updatePower(-powerG);
      m_moteurD.updatePower(powerD);
      break;
     }
}
void CLocomotion::resetPulses()
{
   m_encodeurD.reset();
   m_encodeurG.reset();
   m_mPulses = 0;
   m_speedErrorPrev = 0;
   m_speedErrorSum = 0;
   m_speedConsigne = 40;
}

void CLocomotion::updateEtat()
{
  // update etat speed
  m_etat.speed = m_mPulses - m_etat.pulses ;

  //update etat pulses
  m_etat.pulses = m_mPulses;

  switch (m_etat.dir){

    case FORWARD :
      {
        unsigned int distance = m_etat.speed*(PI*WHEEL_DIAMETER)/360L;
        m_etat.x += distance*cos(getCurrentTheta());
        m_etat.y += distance*sin(getCurrentTheta());
      }
     break;

    case BACKWARD :
      {
        unsigned int distance = m_etat.speed*(PI*WHEEL_DIAMETER)/360L;
        m_etat.x -= distance*cos(getCurrentTheta());
        m_etat.y -= distance*sin(getCurrentTheta());
      }
      break;

    case RIGHT :
      m_etat.theta += m_etat.speed*WHEEL_DIAMETER/BASE_DIAMETER;
      while(m_etat.theta>=360) m_etat.theta-= 360;
      while(m_etat.theta<0) m_etat.theta+= 360;
      break;

    case LEFT :
      m_etat.theta -= m_etat.speed*WHEEL_DIAMETER/BASE_DIAMETER;
      while(m_etat.theta>=360) m_etat.theta-= 360;
      while(m_etat.theta<0) m_etat.theta+= 360;
      break;
  }
}



void CLocomotion::locomotionA1Interrupt()
{
  m_encodeurD.pisteAInterrupt();
}

void CLocomotion::locomotionB1Interrupt()
{
  m_encodeurD.pisteBInterrupt();
}

void CLocomotion::locomotionA2Interrupt()
{
  m_encodeurG.pisteAInterrupt();
}

void CLocomotion::locomotionB2Interrupt()
{
  m_encodeurG.pisteBInterrupt();
}

