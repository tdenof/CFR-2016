
#include <Servo.h>
#include "CRobot.h"


CRobot robot;

void setup()
{
  attachInterrupt(digitalPinToInterrupt(PIN_A1), interruptionA1, CHANGE); 
  attachInterrupt(digitalPinToInterrupt(PIN_B1), interruptionB1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_A2), interruptionA2, CHANGE); 
  attachInterrupt(digitalPinToInterrupt(PIN_B2), interruptionB2, CHANGE);
  analogReference(EXTERNAL);
  robot.initRobot();
  Serial.begin(9600);
}

void loop()
{
  int i, k;	
  int j=1;
  boolean flag=false;
  robot.avancer(0);
  delay(1000);
  if (!robot.etatTirette())
  {
    for(i=80; i<260 && j<180; i+=10){

      robot.avancer(i);

      for(k=j ; k<=j+10; k++){

       while(robot.capteurIRValeur() > SEUIL_IR){
         robot.avancer(0);
         delay(50);
         robot.printCapteurIR();
         k=180;
       }
       robot.servoPos(k);
       delay(15);
     }

      j=k;
      robot.printPulses();
    }

    delay(100);
    robot.avancer(0);
    delay(1500);
    robot.tourner(120);
    delay(3000);
    robot.printPulses();
    delay(2000);
    robot.printPulses();
    robot.avancer(0);
    delay(1000);
  
    for(i=80; i<260 && j>0; i+=10){
      robot.avancer(i);
      for(k=j ; k>=j-10; k--){
        while(robot.capteurIRValeur() > SEUIL_IR){
          robot.avancer(0);
          delay(50);
          robot.printCapteurIR();
          k=0;
        }
        robot.servoPos(k);
        delay(15);
      }
      j=k;
      robot.printPulses();
    }

    delay(100);
    robot.avancer(0);
    delay(1500);
    robot.tourner(-120);
    delay(3000);
    robot.printPulses();
    delay(2000);
    robot.printPulses();
  }
  else {
    robot.printTirette();
   
    robot.printCapteurIR();
    delay(800);
  }
}

void interruptionA1()
{
  robot.robotA1Interrupt();
}

void interruptionB1()
{
  robot.robotB1Interrupt();
}

void interruptionA2()
{
  robot.robotA2Interrupt();
}

void interruptionB2()
{
  robot.robotB2Interrupt();
}

