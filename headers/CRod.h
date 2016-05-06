#ifndef CROD_H
#define CROD_H

#include "CDS5500.h"
#include "constantes.h"

class CRod
{
    public:
        CRod();
        virtual ~CRod();
        void deploy();
        void deploy(int angle);
        void undeploy();
        void init(int color);

    protected:
    private:

    int m_id;
    CDS5500 m_servo;
};

#endif // CROD_H
