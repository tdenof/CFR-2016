#include "../headers/CLocomotion.h"
#include "../headers/TimerThree.h"
#include "../headers/TimerFive.h"

#include "../headers/zoneInterdite.h"
#include <Arduino.h>

CLocomotion::CLocomotion() :  m_etat({X_INIT,Y_INIT,THETA_INIT,SPEED_INIT,DIR_INIT}), 
m_moteurD(PIN_M2IN1,PIN_M2IN2,PIN_M2PWM), 
m_moteurG(PIN_M1IN1,PIN_M1IN2,PIN_M1PWM), 
m_encodeurD(PIN_A1,PIN_B1), m_encodeurG(PIN_A2,PIN_B2), 
m_speedConsigne(0), m_speedErrorSum(0), m_speedErrorPrev(0),m_flag(false), m_mPulses(0), m_dPulses(0)
{
   //ctor
   

}

CLocomotion::~CLocomotion()
{
    //dtor
}

void CLocomotion::lGoTo(int x, int y, bool detection)
{
  if(detection) Timer5.start();
  while(m_flag){
    Serial.println("Blocked");
    delay(50);
  }
  float distance = sqrt(pow(x-m_etat.x,2)+pow(y-m_etat.y,2));
  if(distance==0) return;
  // Serial.print("distance : ");
  // Serial.print(distance);
  //from origin to new pos
  int phi = (int)(asin((y-m_etat.y)/distance)*180.0F/PI);
  Serial.print("phi : ");
  Serial.print(phi);

  if(x-m_etat.x<0) phi = 180- phi;
  //Final theta
  int phiF = phi;
  if (phiF<0) phiF += 360;
  // between actual and new pos
  int psi = phi - m_etat.theta;
  Serial.print("psi : ");
  Serial.print(psi);
  if(abs(psi) < 180){
    if(psi > 0) lTurn(psi,RIGHT);
    else lTurn(-psi,LEFT);
  }
  else{
    if(psi > 0) lTurn(360-psi,LEFT);
    else lTurn(360+psi,RIGHT);
  }
  printCoord();
  // Serial.println("Avancer");
  delay(500);
  lAvancer(distance,FORWARD);
  printCoord();
  //Correct final angle
  delay(500);
  Serial.println("Correct FINAL THETA");
  int corTheta = getCurrentTheta() - phiF;
  if(abs(corTheta)<180){
    if(corTheta <0) lTurn(- corTheta,RIGHT);
    else{
      if (corTheta > 0) lTurn(corTheta,LEFT);
    }
  }
  else {
    if(corTheta <0) lTurn(360+corTheta,LEFT);
    else{
      if (corTheta > 0) lTurn(360-corTheta,RIGHT);
    }
  }
  printCoord();
}

void CLocomotion::lGoTo(int x, int y, int angleF, bool detection)
{
  if(detection) Timer5.start();
  while(m_flag){
    delay(50);
  }
  float distance = sqrt(pow(x-m_etat.x,2)+pow(y-m_etat.y,2));
  if(distance==0) return;
  // Serial.print("distance : ");
  // Serial.print(distance);
  //from origin to new pos
  int phi = (int)(asin((y-m_etat.y)/distance)*180.0F/PI);
  Serial.print("phi : ");
  Serial.print(phi);

  if(x-m_etat.x<0) phi = 180- phi;
  
  // between actual and new pos
  int psi = phi - m_etat.theta;
  Serial.print("psi : ");
  Serial.print(psi);
  if(abs(psi) < 180){
    if(psi > 0) lTurn(psi,RIGHT);
    else lTurn(-psi,LEFT);
  }
  else{
    if(psi > 0) lTurn(360-psi,LEFT);
    else lTurn(360+psi,RIGHT);
  }
  printCoord();
  // Serial.println("Avancer");
  delay(500);
  lAvancer(distance,FORWARD);
  printCoord();
  //Correct final angle
  delay(500);
  Serial.println("Correct FINAL THETA");
  int corTheta = getCurrentTheta() - angleF;
  if(abs(corTheta)<180){
    if(corTheta <0) lTurn(- corTheta,RIGHT);
    else{
      if (corTheta > 0) lTurn(corTheta,LEFT);
    }
  }
  else {
    if(corTheta <0) lTurn(360+corTheta,LEFT);
    else{
      if (corTheta > 0) lTurn(360-corTheta,RIGHT);
    }
  }
  printCoord();
}


void CLocomotion::lGoTo(int x, int y, bool detection, int dir)
{
  if(detection) Timer5.start();
  while(m_flag){
    Serial.println("Blocked");
    delay(50);
  }
  float distance = sqrt(pow(x-m_etat.x,2)+pow(y-m_etat.y,2));
  if(distance==0) return;
  // Serial.print("distance : ");
  // Serial.print(distance);
  // //from origin to new pos
  // int phi = (int)(asin((y-m_etat.y)/distance)*180.0F/PI);
  // Serial.print("phi : ");
  // Serial.print(phi);

  // if(x-m_etat.x<0) phi = 180- phi;
  // //Final theta
  // int phiF = phi;
  // if (phiF<0) phiF += 360;
  // // between actual and new pos
  // int psi = phi - m_etat.theta;
  // Serial.print("psi : ");
  // Serial.print(psi);
  // if(abs(psi) < 180){
  //   if(psi > 0) lTurn(psi,RIGHT);
  //   else lTurn(-psi,LEFT);
  // }
  // else{
  //   if(psi > 0) lTurn(360-psi,LEFT);
  //   else lTurn(360+psi,RIGHT);
  // }
  // printCoord();
  // // Serial.println("Avancer");
  // delay(500);
  lAvancer(distance,BACKWARD);
  printCoord();
  //Correct final angle
  // delay(500);
  // Serial.println("Correct FINAL THETA");
  // int corTheta = getCurrentTheta() - phiF;
  // if(abs(corTheta)<180){
  //   if(corTheta <0) lTurn(- corTheta,RIGHT);
  //   else{
  //     if (corTheta > 0) lTurn(corTheta,LEFT);
  //   }
  // }
  // else {
  //   if(corTheta <0) lTurn(360+corTheta,LEFT);
  //   else{
  //     if (corTheta > 0) lTurn(360-corTheta,RIGHT);
  //   }
  // }
  // printCoord();
}

void CLocomotion::setFlag(bool flag)
{
  m_flag=flag;
}

etatLocomotion CLocomotion::getCurrentState()
{
    etatLocomotion pos;
    pos = {getCurrentX(),getCurrentY(),getCurrentTheta(),getCurrentSpeed()};
    return pos;
}

bool CLocomotion::inPosition(int x, int y)
{
  Serial.println("TEST POSITION");
  if ((abs(getCurrentX()-x)) < 100 && (abs(getCurrentY()-y)) < 100){
    Serial.println("IN POSITION");
    Serial.println(abs(getCurrentX()-x));
    Serial.println(abs(getCurrentY()-y));
    return true;
  }
  else {
    Serial.println("NOT POSITION");
    return false;
  }
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
            lGoTo(calculXEvitementCarre(DISTANCE_EVITEMENT),calculYEvitementCarre(DISTANCE_EVITEMENT), true);
                       
            return true;
        }
     // rotation d'un angle Pi/2 dans le sens anti-horaire si possible
      if(!traverseZoneInterdite(-DISTANCE_EVITEMENT))
       {
            lGoTo(calculXEvitementCarre(-DISTANCE_EVITEMENT),calculYEvitementCarre(-DISTANCE_EVITEMENT), true);
           
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

unsigned long CLocomotion::DToPulses(unsigned int distance)
{
  return 1024L*distance/(PI*WHEEL_DIAMETER);
}

unsigned int CLocomotion::toDistance(unsigned long pulses)
{
  return (int)(pulses*PI*WHEEL_DIAMETER/1024L);
}

unsigned long CLocomotion::AToPulses(unsigned int angle)
{
  return 1024L*angle*BASE_DIAMETER/(360L*WHEEL_DIAMETER);
}

int CLocomotion::toAngle(long pulses){
  return (int)(360L*pulses*WHEEL_DIAMETER/(1024L*BASE_DIAMETER));
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


bool CLocomotion::getFlag()
{
  return m_flag;
}

void CLocomotion::lAvancer (unsigned int distance, int dir)
{
  Serial.println("ENTER LAVANCER");
  Serial.println(distance);

  if (distance == 0) return;
  
  resetPulses();
  if(m_flag) {
    lStop();
    updatePulses();
    updateCoord();
    return;
  }

  
  unsigned long fPulses = DToPulses(distance);
  Serial.print("FPULSES : ");
  Serial.println(fPulses);
  m_etat.dir = dir;
  m_speedConsigne=10;
  lPositionControl(fPulses);
  lStop();
  delay(200);
  Serial.println("FINAL PULSES");
  printLPulses();
  updatePulses();
  updateCoord();
  // Serial.println(getCurrentX());
  // Serial.println(getCurrentY());
  // Serial.println(getCurrentTheta());
  // Serial.println(m_dPulses);
  // Serial.println(m_mPulses);

} 

void CLocomotion::lTurn (unsigned int angle, int dir)
{
  Serial.println("ENTER LTURN");
  Serial.println(angle);
  if (angle == 0) {
    // Serial.println("RETURN1");
    return;
  }
  // Serial.println("RESET");
  resetPulses();
  // Serial.println("TEST2");
  // if(m_flag) {
  //   Serial.println("LSTOP");
  //   lStop();
  //   Serial.println("RETURN");
  //   return;
    
  // }
  
  unsigned long fPulses = AToPulses(angle);
  Serial.print("FPULSES : ");
  Serial.println(fPulses);
  m_etat.dir = dir;
  m_speedConsigne=10;
  lAngleControl(fPulses);
  lStop();
  delay(200);
  updatePulses();
  updateCoord();
  // printLPulses();
  Serial.print("THETA FINAL : ");
  Serial.println(m_etat.theta);
  // Serial.println(getCurrentTheta());
}

void CLocomotion::lStop()
{
  Serial.println("STOP PROCEDURE");
  while(m_speedConsigne > 5){
    updatePulses();
    m_speedConsigne -= 5;
    updateEtat();
    delay(20);
    // printLPulses();
  }
  Timer3.stop();
  updatePower(0);
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


void CLocomotion::lSpeedControl()
{
    int speedError = m_speedConsigne - m_etat.speed; //error
    Serial.print("Error : ");
    Serial.println(speedError);
    m_speedErrorSum += speedError; //integration
    int speedErrorDerivative = speedError - m_speedErrorPrev;// action derivee
    m_speedErrorPrev = speedError;
    int command = KP*speedError + KI*m_speedErrorSum + KD*m_speedErrorPrev;
  int commandD = command;
  int commandG = command;
    if(abs(m_etat.dir)==1){
      commandD -= (int)(KPP*m_dPulses);
      commandG += (int)(KPP*m_dPulses);
  //     Serial.print("Droite 1: ");
  // Serial.println(commandD);
  // Serial.print("Gauche 1: ");
  // Serial.println(commandG);
    }
    else {
      commandD -= (int)KPP*m_dPulses;
      commandG += (int)KPP*m_dPulses;
    }
    // Serial.print("commandD :");
    // Serial.println(commandD);
    // Serial.print("commandG :");
    // Serial.println(commandG);
  // command = 32*sqrt(command);
  commandD = 32*sqrt(commandD);
  commandG = 32*sqrt(commandG);
  Serial.print("Droite : ");
  Serial.println(commandD);
  Serial.print("Gauche : ");
  Serial.println(commandG);
  
    updatePower(commandD,commandG);
    
}

void CLocomotion::lPositionControl(unsigned long fPulses)
{
  Timer3.start();

  for(int i = 5 ; i<SPEEDMAX && m_mPulses < fPulses && !m_flag ; i+=2){
    updatePulses();
    m_speedConsigne = i;
    // Serial.print("Consigne Pos1: ");
    // Serial.println(m_speedConsigne);
    printLPulses();
    updateEtat();
    delay(20);
  }
      
  while(m_mPulses < fPulses && !m_flag ){
    updatePulses();
    
    if(fPulses - m_mPulses < 350 && m_speedConsigne >= SPEEDMIN) 
      m_speedConsigne-=5;
    
    // Serial.print("Consigne Pos2: ");
    // Serial.println(m_speedConsigne);
    printLPulses();
  updateEtat();
    
  delay(20);
  }

}

void CLocomotion::lAngleControl(unsigned long fPulses)
{
  Timer3.start();

  for(int i = 5 ; i<SPEEDMAXTURN && m_mPulses < fPulses ; i+=2){
    updatePulses();
    m_speedConsigne = i;
    // Serial.print("Consigne : TUR1");
    // Serial.println(m_speedConsigne);
    // printLPulses();
    updateEtat();
    delay(20);
  }
      
  while(m_mPulses < fPulses ){
    updatePulses();
    if(fPulses - m_mPulses < 200 && m_speedConsigne >= SPEEDMINTURN) 
      m_speedConsigne-=5;
    
    // Serial.print("Consigne TUR2: ");
    // Serial.println(m_speedConsigne);
    // printLPulses();
  updateEtat();
    
  delay(20);
  }
  
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
      m_moteurG.updatePower(-power);
      m_moteurD.updatePower(power);
      break;
    case LEFT :
      m_moteurG.updatePower(power);
      m_moteurD.updatePower(-power);
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
      m_moteurG.updatePower(-powerG);
      m_moteurD.updatePower(powerD);
      break;
    case LEFT :
      m_moteurG.updatePower(powerG);
      m_moteurD.updatePower(-powerD);
      break;
     }
}
void CLocomotion::resetPulses()
{
   m_encodeurD.reset();
   m_encodeurG.reset();
   m_etat.speed=0;
   m_etat.pulses=0;
   m_mPulses = 0;
   m_dPulses = 0;
   m_speedErrorPrev = 0;
   m_speedErrorSum = 0;
   m_speedConsigne = 10;
   m_flag = false;
   delay(100);
}

void CLocomotion::updateEtat()
{
  // update etat speed
  m_etat.speed = m_mPulses - m_etat.pulses ;

  //update etat pulses
  m_etat.pulses = m_mPulses;

}

void CLocomotion::updateCoord()
{
  switch (m_etat.dir){

    case FORWARD :
      {
        // Serial.print("m_mPulses : ");
        // Serial.println(m_mPulses);
        unsigned int distance = toDistance(m_mPulses);
        // Serial.print("distance : ");
        // Serial.println(distance);
        m_etat.x += distance*cos(getCurrentTheta()*PI/180);
        // Serial.print("x : ");
        // Serial.println(m_etat.x);
        m_etat.y += distance*sin(getCurrentTheta()*PI/180);
        // Serial.print("y : ");
        // Serial.println(m_etat.y);
        // Serial.print("m_dPulses : ");
        // Serial.println(m_dPulses);
        m_etat.theta +=toAngle(m_dPulses);
        // Serial.println(m_etat.theta);
      }
     break;

    case BACKWARD :
      {
        unsigned int distance = toDistance(m_mPulses);
        m_etat.x -= distance*cos(getCurrentTheta()*PI/180);
        m_etat.y -= distance*sin(getCurrentTheta()*PI/180);
        m_etat.theta -=toAngle(m_dPulses);
      }
      break;

    case RIGHT :
      m_etat.theta += toAngle(m_mPulses);
      Serial.println(m_etat.theta);
      while(m_etat.theta>=360) m_etat.theta-= 360;
      while(m_etat.theta<0) m_etat.theta+= 360;
      // Serial.println(m_etat.theta);
      break;

    case LEFT :
      m_etat.theta -= toAngle(m_mPulses);
      while(m_etat.theta>=360) m_etat.theta-= 360;
      while(m_etat.theta<0) m_etat.theta+= 360;
      break;
  }
}

void CLocomotion::updatePulses(){
   m_mPulses = (abs(m_encodeurD.pulseCountValue()) + abs(m_encodeurG.pulseCountValue()))/2;
    m_dPulses = (abs(m_encodeurD.pulseCountValue()) - abs(m_encodeurG.pulseCountValue()))/2;
    // Serial.print("UPDATE DPULSES");
    // Serial.println(m_dPulses);
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

void CLocomotion::printCoord()
{
  Serial.print("X : ");
  Serial.println(getCurrentX());
  Serial.print("Y : ");
  Serial.println(getCurrentY());
  Serial.print("theta : ");
  Serial.println(getCurrentTheta());
}

