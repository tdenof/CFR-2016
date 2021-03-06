#include "headers/CRobot.h"

#include "headers/TimerThree.h"
#include "headers/TimerFive.h"


CRobot robot;

void setup()
{
  attachInterrupt(digitalPinToInterrupt(PIN_A1), interruptionA1, CHANGE); 
  attachInterrupt(digitalPinToInterrupt(PIN_B1), interruptionB1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_A2), interruptionA2, CHANGE); 
  attachInterrupt(digitalPinToInterrupt(PIN_B2), interruptionB2, CHANGE);
  Timer3.initialize(20000);
  Timer3.attachInterrupt(speedControl);
  Timer3.stop();
  Timer5.initialize(10000);
  Timer5.attachInterrupt(obstacleDetection);
  Timer5.stop();
  Serial3.begin(1000000);
  robot.initRobot();
  Serial.begin(115200);
}

void loop()
{
  delay(2000);
  while(robot.etatTirette()){
    delay(50);
  }
  long tInitial = millis();
  long tInstant = tInitial;
  while(robot.getColor() == 0){
    delay(50);
  }

  if(robot.getColor()==1){
    Serial.println("GREEN");
    robot.openPlier();
    delay(3000);
    robot.goTo(0,400,false);
    delay(500);
    robot.straightPlier();
    delay(3000);
    robot.goTo(-100,800,false);
    delay(500);
    robot.openPlier();
    delay(3000);

    robot.goTo(0,400,true, BACKWARD);
    delay(500);
    tInstant = millis();
    if(tInstant-tInitial > 80000){
      while(1){
       delay(1000);
     }
    }
    robot.closePlier();
    delay(3000);
    tInstant = millis();
    if(tInstant-tInitial > 80000){
      while(1){
       delay(1000);
     }
    }
    robot.goTo(-900,500,90,true);
    delay(500);
    tInstant = millis();
    if(tInstant-tInitial > 80000){
      while(1){
       delay(1000);
     }
    }
    robot.undeployRod();
    delay(2000);
    tInstant = millis();
    if(tInstant-tInitial > 80000){
      while(1){
       delay(1000);
     }
    }
    robot.goTo(-900,750,90,true);
    delay(500);
    tInstant = millis();
    if(tInstant-tInitial > 80000){
      while(1){
       delay(1000);
     }
    }
    robot.deployRod(600);
    delay(2000);

    tInstant = millis();
    if(tInstant-tInitial > 80000){
      while(1){
       delay(1000);
     }
    }
    robot.goTo(-850,1000,90,true);
    delay(500);
    tInstant = millis();
    if(tInstant-tInitial > 80000){
      while(1){
       delay(1000);
     }
    }
    robot.deployRod();
    delay(2000);
    tInstant = millis();
    if(tInstant-tInitial > 80000){
      while(1){
       delay(1000);
     }
    }
    robot.turn(90,RIGHT);
    delay(500);
    tInstant = millis();
    if(tInstant-tInitial > 80000){
      while(1){
       delay(1000);
     }
    }
    robot.undeployRod();
    delay(2000);
    tInstant = millis();
    if(tInstant-tInitial > 80000){
      while(1){
       delay(1000);
     }
    }
    robot.goTo(-600,300,90,true);
    delay(500);
    tInstant = millis();
    if(tInstant-tInitial > 80000){
      while(1){
       delay(1000);
     }
    }
    robot.goTo(-900,580,90,true);
    delay(500);
    tInstant = millis();
    if(tInstant-tInitial > 80000){
      while(1){
       delay(1000);
     }
    }
    robot.deployRod();
    delay(2000);
    tInstant = millis();
    if(tInstant-tInitial > 80000){
      while(1){
       delay(1000);
     }
    }
    robot.goTo(-900,800,90,true);
    delay(500);
    tInstant = millis();
    if(tInstant-tInitial > 80000){
      while(1){
       delay(1000);
     }
    }
    robot.deployRod(600);
    delay(2000);

}
  else{
    Serial.println("PURPLE");
    robot.openPlier();
    delay(3000);
    robot.goTo(0,400,false);
    delay(500);
    robot.straightPlier();
    delay(3000);
    robot.goTo(100,800,false);
    delay(500);
    robot.openPlier();
    delay(3000);
    robot.goTo(0,400,true, BACKWARD);
    delay(500);
    tInstant = millis();
    if(tInstant-tInitial > 80000){
      while(1){
       delay(1000);
     }
    }
    robot.closePlier();
    delay(3000);
    tInstant = millis();
    if(tInstant-tInitial > 80000){
      while(1){
       delay(1000);
     }
    }
    robot.goTo(900,500,90,true);
    delay(500);
    tInstant = millis();
    if(tInstant-tInitial > 80000){
      while(1){
       delay(1000);
     }
    }
    robot.deployRod();
    delay(2000);
    tInstant = millis();
    if(tInstant-tInitial > 80000){
      while(1){
       delay(1000);
     }
    }
    robot.goTo(900,750,90,true);
    delay(500);
    tInstant = millis();
    if(tInstant-tInitial > 80000){
      while(1){
       delay(1000);
     }
    }
    robot.deployRod(400);
    delay(2000);
    tInstant = millis();
    if(tInstant-tInitial > 80000){
      while(1){
       delay(1000);
     }
    }
    robot.goTo(850,1000,90,true);
    delay(500);
    tInstant = millis();
    if(tInstant-tInitial > 80000){
      while(1){
       delay(1000);
     }
    }
    robot.deployRod();
    delay(2000);
    tInstant = millis();
    if(tInstant-tInitial > 80000){
      while(1){
       delay(1000);
     }
    }
    robot.turn(90,RIGHT);
    delay(500);
    tInstant = millis();
    if(tInstant-tInitial > 80000){
      while(1){
       delay(1000);
     }
    }
    robot.undeployRod();
    delay(2000);
    tInstant = millis();
    if(tInstant-tInitial > 80000){
      while(1){
       delay(1000);
     }
    }
    robot.goTo(600,300,90,true);
    delay(500);
    tInstant = millis();
    if(tInstant-tInitial > 80000){
      while(1){
       delay(1000);
     }
    }
    robot.goTo(900,580,90,true);
    delay(500);
    tInstant = millis();
    if(tInstant-tInitial > 80000){
      while(1){
       delay(1000);
     }
    }
    robot.deployRod();
    delay(2000);
    tInstant = millis();
    if(tInstant-tInitial > 80000){
      while(1){
       delay(1000);
     }
    }
    robot.goTo(900,800,90,true);
    delay(500);
    tInstant = millis();
    if(tInstant-tInitial > 80000){
      while(1){
       delay(1000);
     }
    }
    robot.deployRod(400);
    delay(2000);
    // robot.goTo(850,1000,90,true);
    // delay(500);
    // robot.deployRod();
    // delay(2000);
    // robot.turn(90,RIGHT);
    // robot.undeployRod();
    // robot.goTo(600,300,90,true);
    // delay(500);
    // robot.goTo(850,360,90,true);
    // delay(500);
    // robot.deployRod();
    // delay(2000);
    // robot.goTo(850,680,90,true);
    // delay(500);
    // robot.deployRod(400);
    // delay(2000);
    // robot.goTo(850,900,90,true);
    // delay(500);
    // robot.deployRod();
    // delay(2000);
    // robot.turn(90,RIGHT);
    // robot.undeployRod();
    // robot.goTo(600,300,90,true);
    // delay(500);
  }





  // robot.goTo(500,500,false);
  // delay(500);
  // robot.goTo(500,0,false);
  // delay(500);
  // robot.goTo(0,0,90,false);
  // delay(500);
  
  // robot.deployRod();
  // delay(2000);
  

  // robot.deployRod(400);
  // delay(1000);
  // robot.goTo(0,900,false);
  // delay(500);
  // robot.deployRod();
  // delay(1000);
  // robot.turn(90,2);
  
  // robot.turn(90,LEFT);
  // delay(1000);
  // robot.avancer(400,FORWARD);
  // robot.avancer(500,FORWARD);
  // delay(1000);
  // robot.turn(90,LEFT);
  // delay(1000);
  // robot.avancer(500,FORWARD);
  // delay(1000);
  // robot.turn(90,LEFT);
  // delay(1000);
  // robot.avancer(500,FORWARD);
  // delay(1000);
  // robot.turn(90,LEFT);
  // delay(1000);


    

  while(1){
    Serial.println("FINISH");
    delay(1000);
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

void speedControl()
{
  robot.robotSpeedControl();
}

void obstacleDetection()
{
  robot.robotObstacleDetection();
}

