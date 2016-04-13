#include "headers/CRobot.h"
#include "headers/CCapteur_IR.h"
#include "headers/CEncodeur.h"
#include "headers/CLocomotion.h"
#include "headers/CMoteur.h"
#include "headers/CTirette.h"
#include "headers/TimerThree.h"
#include "headers/TimerFour.h"


CRobot robot;

void setup()
{
  attachInterrupt(digitalPinToInterrupt(PIN_A1), interruptionA1, CHANGE); 
  attachInterrupt(digitalPinToInterrupt(PIN_B1), interruptionB1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_A2), interruptionA2, CHANGE); 
  attachInterrupt(digitalPinToInterrupt(PIN_B2), interruptionB2, CHANGE);
  Timer3.initialize(50);
  Timer3.stop();
  Timer4.initialize(50);
  Timer4.stop();
  Timer3.attachInterrupt(positionControl);
  Timer4.attachInterrupt(speedControl);

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

void positionControl()
{
  robot.robotPositionControl();
}

void speedControl()
{
  robot.robotSpeedControl();
}

