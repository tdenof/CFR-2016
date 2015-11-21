#ifndef ZONEINTERDITE_H
#define ZONEINTERDITE_H
#include "constantes.h"
typedef struct ZoneInterdite
{
    int xDebut;
    int xFin;
    int yDebut;
    int yFin;
}zoneInterdite;

zoneInterdite m_zoneInterdite[NBZONEINTERDITE] = {
{-200,-100,-45,60}
};

#endif //ZONEINTERDITE_H

