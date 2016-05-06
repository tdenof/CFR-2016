#ifndef CROBOT_H
#define CROBOT_H

#include "CSwitch.h"
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
        int getColor();
        bool etatTirette();
        void printTirette();
        void avancer(unsigned int distance, int dir);
        void turn(unsigned int angle, int dir);
        void stop();
        void goTo(int x, int y, bool detection);
        void goTo(int x, int y, int angleF, bool detection);
        void goTo(int x, int y, bool detection, int dir);
        void openPlier();
        void straightPlier();
        void closePlier();
        void deployRod();
        void deployRod(int angle);
        void undeployRod();
        void printPulses();
        void robotA1Interrupt();
        void robotB1Interrupt();
        void robotA2Interrupt();
        void robotB2Interrupt();
        void robotSpeedControl();
        void robotObstacleDetection();

    protected:
    private:
    CSwitch m_switch;
    CTirette m_tirette;
    CCapteur_IR m_capteurIRD;
    CCapteur_IR m_capteurIRG;
    CCapteur_IR m_capteurIRA;
    CLocomotion m_locomotion;
    CPlier m_plier;
    CRod m_rod;
    int m_color;
    int m_cDir; //command dir
};

#endif // CROBOT_H
