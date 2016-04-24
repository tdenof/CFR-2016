#include "../headers/CRod.h"

CRod::CRod(): m_idG(ID_PINCEG), m_idD(ID_PINCED)
{
    //ctor
}

CRod::~CRod()
{
    //dtor
}

void CRod::open()
{
	m_servo.WritePos(m_idG,90,150);
	m_servo.WritePos(m_idD,90,150);
}

void CRod::open(int angle)
{
	m_servo.WritePos(m_idG,angle,150);
	m_servo.WritePos(m_idD,angle,150);
}

void CRod::close()
{
	m_servo.WritePos(m_idG,0,150);
	m_servo.WritePos(m_idD,0,150);
}