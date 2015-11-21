#include "../headers/CLocomotion.h"

#include "../headers/zoneInterdite.h"
#include <Arduino.h>

CLocomotion::CLocomotion() :  m_etat({X_INIT,Y_INIT,THETA_INIT}), 
m_moteurD(PIN_M1IN1,PIN_M1IN2,PIN_M1PWM), 
m_moteurG(PIN_M2IN1,PIN_M2IN2,PIN_M2PWM), 
m_encodeurD(PIN_A1,PIN_B1), m_encodeurG(PIN_A2,PIN_B2)
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
etatLocomotion CLocomotion::getCurrentPosition()
{
    etatLocomotion pos;
    pos = {getCurrentX(),getCurrentY(),getCurrentTheta()};
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

void CLocomotion::lAvancer(int speed)
{
  m_moteurD.updatePower(speed);
  m_moteurG.updatePower(speed);
}

void CLocomotion::lTourner(int speed)
{
  m_moteurD.updatePower(speed);
  m_moteurG.updatePower(-speed);
}

void CLocomotion::printLPulses()
{
  Serial.print("Encodeur D : ");
  m_encodeurD.printPulse();
  Serial.print("Encodeur G : ");
  m_encodeurG.printPulse();   
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
