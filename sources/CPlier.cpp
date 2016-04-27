#include "../headers/CPlier.h"

CPlier::CPlier()
{
    //ctor
}

CPlier::~CPlier()
{
    //dtor
}

void CPlier::init(){
	m_idG = ID_PINCEG;
	m_idD = ID_PINCED;
}

void CPlier::open()
{
	m_servo.WritePos(m_idG,20,200);
	delay(100);
	m_servo.WritePos(m_idD,980,200);
}

void CPlier::open(int angle)
{
	m_servo.WritePos(m_idG,angle,200);
	m_servo.WritePos(m_idD,angle,200);
}

void CPlier::close()
{
	m_servo.WritePos(m_idG,230,200);
	delay(100);
	m_servo.WritePos(m_idD,820,200);
}