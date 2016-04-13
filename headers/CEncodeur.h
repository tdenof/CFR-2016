#ifndef CENCODEUR_H
#define CENCODEUR_H

#include <Arduino.h>
class CEncodeur
{
	public:
		CEncodeur(int pisteAPin, int pisteBPin);
		virtual ~CEncodeur();
		long pulseCountValue(); // retourne la valeur du compteur
		void printPulse();
		void printPistes();
		void reset();
   	//traitement des interruptions
    void pisteAInterrupt();
    void pisteBInterrupt();	
   
	protected:
	private:
		
		//pins
		int m_pisteAPin, m_pisteBPin;
		//etat des pistes
		boolean m_pisteAValue, m_pisteBValue;
		// compteur de pulsations
		volatile long m_pulseCount;


};

#endif // CENCODEUR_H
