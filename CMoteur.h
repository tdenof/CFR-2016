#ifndef CMOTEUR_H
#define CMOTEUR_H


class CMoteur
{
    public:
        CMoteur(int dirPin1, int dirPin2, int pwmPin);
        CMoteur(int dirPin1, int dirPin2, int pwmPin, int maxPower);

        virtual ~CMoteur();

        void updatePower(int power);

    protected:
    private:
        //pins
        int m_dirPin1, m_dirPin2, m_pwmPin;

        int m_power, m_maxPower;
};

#endif // CMOTEUR_H
