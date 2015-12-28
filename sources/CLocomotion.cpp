#include "../headers/CLocomotion.h"

#include "../headers/zoneInterdite.h"
#include <Arduino.h>

CLocomotion::CLocomotion() :  m_etat({X_INIT,Y_INIT,THETA_INIT}), 
m_moteurD(PIN_M1IN1,PIN_M1IN2,PIN_M1PWM), 
m_moteurG(PIN_M2IN1,PIN_M2IN2,PIN_M2PWM), 
m_encodeurD(PIN_A1,PIN_B1), m_encodeurG(PIN_A2,PIN_B2), 
m_speedConsigne(0)
{
   //ctor
   

}

CLocomotion::~CLocomotion()
{
    //dtor
}

etatLocomotion CLocomotion::goTo(int x, int y)
{

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
void CLocomotion::lAvancer (unsigned int distance, int speed)
{
  unsigned int dPulses = 360L*distance/(PI*WHEEL_DIAMETER);
  Serial.print("dPulses = ");
  Serial.println(dPulses);
  delay(1000);
  unsigned int mPulses = (abs(m_encodeurD.pulseCountValue()) + abs(m_encodeurG.pulseCountValue()))/2;
  Serial.print("mPulses = ");
  Serial.println(mPulses);
  delay(1000);
  unsigned int fPulses = mPulses + dPulses;
  Serial.print("fPulses = ");
  Serial.println(fPulses);
  delay(1000);
  if (distance == 0) return;
  m_moteurD.updatePower(speed);
  m_moteurG.updatePower(1.16*speed);
  while(mPulses < fPulses){
    mPulses = (abs(m_encodeurD.pulseCountValue()) + abs(m_encodeurG.pulseCountValue()))/2;
    delay(10);
  }
  m_moteurD.updatePower(0);
  m_moteurG.updatePower(0);
  Serial.print("FIN : mPulses = ");
  Serial.println(mPulses);
  delay(1000);
} 

void CLocomotion::lTurn (unsigned int angle, int speed)
{
  int i;
  unsigned int dPulses = angle*BASE_DIAMETER/WHEEL_DIAMETER;
  Serial.print("dPulses = ");
  Serial.println(dPulses);
  delay(1000);
  unsigned int mPulses = (m_encodeurD.pulseCountValue() + m_encodeurG.pulseCountValue())/2;
  Serial.print("mPulses = ");
  Serial.println(mPulses);
  delay(1000);
  unsigned int fPulses = mPulses + abs(dPulses);
  Serial.print("fPulses = ");
  Serial.println(fPulses);
  if (angle == 0) return;
  m_moteurD.updatePower(speed);
  m_moteurG.updatePower(-speed);
  while(mPulses < fPulses){
    mPulses = (m_encodeurD.pulseCountValue() + m_encodeurG.pulseCountValue())/2;
    delay(10);
   }
  m_moteurD.updatePower(0);
  m_moteurG.updatePower(0);
  for (i=0;i<10;i++){
    printLPulses();
    delay(50);
  }
  Serial.print("FIN : mPulses = ");
  Serial.println(mPulses);
  delay(1000);
  printLPulses();
  delay(1000);
}

void CLocomotion::lStop()
{
  m_moteurD.updatePower(0);
  m_moteurG.updatePower(0);
}

void CLocomotion::printLPulses()
{
  Serial.print("Encodeur D : ");
  m_encodeurD.printPulse();
  Serial.print("Encodeur G : ");
  m_encodeurG.printPulse();
  Serial.print("Difference : ");
  Serial.println(abs(m_encodeurD.pulseCountValue()) - abs(m_encodeurG.pulseCountValue()));   
}

void CLocomotion::callback_sensors()
{
  long pulses_moy = (abs(m_encodeurD.pulseCountValue())+abs(m_encodeurG.pulseCountValue()))/2; // moy pulses
  resetPulses(); // set pulses to 0
  updateEtat(pulses_moy);
 
}

void CLocomotion::callback_control()
{
    int speedError = m_speedConsigne - m_etat.speed; //error
    m_speedErrorSum += speedError; //integration
    int speedErrorDerivative = 0// action derivee
    int command = KP * speedError + KI * m_speedConsigneSum + KD * speedErrorDerivative;
    m_moteurG.updatePower(command);
    m_moteurD.updatePower(command);
}

void CLocomotion::resetPulses()
{
  m_encodeurD.reset();
  m_encodeurG.reset();
}

void CLocomotion::updateEtat(long pulses)
{
  updateCurrentSpeed(pulses);
  if (flag == 1) {
    unsigned int distance = pulses*(PI*WHEEL_DIAMETER)/360L;
    updatePos();
  }

  if (flag == 2) {
    unsigned int angle = pulses*WHEEL_DIAMETER/BASE_DIAMETER;
    updateAngle(theta);
  }
}

void CLocomotion::updateCurrentSpeed(long pulses)
{
  int speed = convertToTension(pulses);
  m_etat.speed = speed;
}

void CLocomotion::updatePos(unsigned int distance)
{
  m_etat.x += distance*cos(getCurrentTheta());
  m_etat.y += distance*sin(getCurrentTheta());
}

void CLocomotion::updateAngle(unsigned int angle)
{
  m_etat.theta += angle;
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
