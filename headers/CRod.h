#ifndef CROD_H
#define CROD_H

#include "CDS5500.h"
#include "constantes.h"

class CRod
{
    public:
        CRod();
        virtual ~CRod();
        void open();
        void open(int angle);
        void close();

    protected:
    private:

    int m_idG, m_idD;
    CDS5500 m_servo;
};

#endif // CROD_H
