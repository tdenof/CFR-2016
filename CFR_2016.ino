#include "headers/CRobot.h"

CRobot robot;

void setup()
{
  attachInterrupt(digitalPinToInterrupt(PIN_A1), interruptionA1, CHANGE); 
  attachInterrupt(digitalPinToInterrupt(PIN_B1), interruptionB1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_A2), interruptionA2, CHANGE); 
  attachInterrupt(digitalPinToInterrupt(PIN_B2), interruptionB2, CHANGE);
  robot.initRobot();
  Serial.begin(9600);
}

void loop()
{
  delay(2000);
  robot.printPulses();
  delay(3000);
  robot.turn(360,80);
  delay(5000);
 robot.printPulses();
 /*  robot.stop();
  delay(1500);
  robot.tourner(120);
  delay(3000);
  robot.printPulses();
  robot.stop();
  delay(1000);
  robot.avancer(500,-200);
  delay(3000);
  robot.printPulses();
  robot.stop();
  delay(1500);
  robot.tourner(-120);
  delay(3000);
  robot.printPulses();
  robot.stop();*/
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

