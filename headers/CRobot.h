#ifndef CROBOT_H
#define CROBOT_H

#include <Servo.h>
#include "CCapteur_IR.h"
#include "CTirette.h"
#include "CLocomotion.h"

class CRobot
{
    public:
        CRobot();
        virtual ~CRobot();
        void initRobot();
        void servoPos(int pos);
        int etatTirette();
        int capteurIRValeur();
        void printCapteurIR();
        void printTirette();
        void avancer(unsigned int distance, int speed);
        void turn(unsigned int angle, int speed);
        void stop();
        void printPulses();
        void robotA1Interrupt();
        void robotB1Interrupt();
        void robotA2Interrupt();
        void robotB2Interrupt();

    protected:
    private:
    Servo m_servo;
    CTirette m_tirette;
    CCapteur_IR m_capteurIR;
    CLocomotion m_locomotion;
};

#endif // CROBOT_H
