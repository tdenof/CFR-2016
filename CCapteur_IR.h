#ifndef CCAPTEUR_IR_H
#define CCAPTEUR_IR_H


class CCapteur_IR
{
    public:
        CCapteur_IR();
        virtual ~CCapteur_IR();
        void initCapteur();
        int valeur();
        void printValeur();
    protected:
    private:
    int m_Cpin;
    
};

#endif // CCAPTEUR_IR_H
