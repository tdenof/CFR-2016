#ifndef CROBOT_H
#define CROBOT_H


#include "CCapteur_IR.h"
#include "CTirette.h"
#include "CLocomotion.h"
#include "CPlier.h"
#include "CRod.h"

class CRobot
{
    public:
        CRobot();
        virtual ~CRobot();
        void initRobot();
        void servoPos(int pos);
        bool etatTirette();
        int capteurIRValeur();
        void printCapteurIR();
        void printTirette();
        void avancer(unsigned int distance, int dir);
        void turn(unsigned int angle, int dir);
        void stop();
        void goTo(int x, int y, bool detection);
        void openPlier();
        void openPlier(int angle);
        void closePlier();
        void printPulses();
        void robotA1Interrupt();
        void robotB1Interrupt();
        void robotA2Interrupt();
        void robotB2Interrupt();
        void robotSpeedControl();
        void robotObstacleDetection();

    protected:
    private:
    
    CTirette m_tirette;
    CCapteur_IR m_capteurIR;
    CLocomotion m_locomotion;
    CPlier m_plier;
    CRod m_rod;
};

#endif // CROBOT_H
