#ifndef CLOCOMOTION_H
#define CLOCOMOTION_H
#include "CMoteur.h"
#include "CEncodeur.h"
#include "constantes.h"
#define DISTANCE_EVITEMENT 300 // Distance sur laquelle va avancer le robot lors de l'evitement carre : 300 mm
#define NB_ZONEINTERDITE 1  // Nombre de zones interdites


typedef struct EtatLocomotion // Une structure renseignant l'etat de la locomotion
{
    int x; // Son X actuel ect ..
    int y;
    int theta;
}etatLocomotion ;



class CLocomotion
{
    public:
        CLocomotion();
        virtual ~CLocomotion();
        void initLocomotion();
        bool eviter(); // Fonction d'evitement appell��e lors de la detection d'un robot
        // MUTATEURS
        etatLocomotion goTo(int x, int y);
        // ACCESSEURS
        int getCurrentX();
        int getCurrentY();
        int getCurrentTheta();
        etatLocomotion getCurrentPosition();
        void lAvancer(unsigned int distance, int speed);
        void lTurn(unsigned int angle, int speed);
        void lStop();
        void printLPulses();
        void locomotionA1Interrupt();
        void locomotionB1Interrupt();
        void locomotionA2Interrupt();
        void locomotionB2Interrupt();       

    protected:

    private:
        etatLocomotion m_etat;
        bool evitementCarre(); // Un type d'evitement
        int calculXEvitementCarre(int d);
        int calculYEvitementCarre(int d);
        
        bool appartientZoneInterdite(int x,int y);
        bool traverseZoneInterdite(int distance);
        CMoteur m_moteurD, m_moteurG;
        CEncodeur m_encodeurD, m_encodeurG;



};

#endif // CLOCOMOTION_H
