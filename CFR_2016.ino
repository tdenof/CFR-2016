#include "headers/CRobot.h"

#include "headers/TimerThree.h"


CRobot robot;

void setup()
{
  attachInterrupt(digitalPinToInterrupt(PIN_A1), interruptionA1, CHANGE); 
  attachInterrupt(digitalPinToInterrupt(PIN_B1), interruptionB1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_A2), interruptionA2, CHANGE); 
  attachInterrupt(digitalPinToInterrupt(PIN_B2), interruptionB2, CHANGE);
  Timer3.initialize(50);
  Timer3.attachInterrupt(speedControl);
  Timer3.stop();
  robot.initRobot();
  Serial.begin(9600);
}

void loop()
{
  robot.printPulses();
  delay(500);
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

void speedControl()
{
  robot.robotSpeedControl();
}

