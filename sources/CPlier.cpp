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
	close();
}

void CPlier::open()
{
	m_servo.WritePos(m_idG,400,150);
	delay(1000);
	m_servo.WritePos(m_idD,912,150);
}

void CPlier::straight()
{
	m_servo.WritePos(m_idG,480,150);
	delay(1000);
	m_servo.WritePos(m_idD,840,150);
}

void CPlier::close()
{
	m_servo.WritePos(m_idD,540,150);
	delay(1000);
	m_servo.WritePos(m_idG,765,150);
}