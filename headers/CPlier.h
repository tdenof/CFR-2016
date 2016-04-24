#ifndef CPLIER_H
#define CPLIER_H

#include "CDS5500.h"
#include "constantes.h"

class CPlier
{
    public:
        CPlier();
        virtual ~CPlier();
        void open();
        void open(int angle);
        void close();
        void init();

    protected:
    private:

    int m_idG, m_idD;
    CDS5500 m_servo;
};

#endif // CPLIER_H
