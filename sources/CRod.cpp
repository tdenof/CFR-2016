#include "../headers/CRod.h"

CRod::CRod(): m_idL(ID_RODL), m_idH(ID_RODH)
{
    //ctor
}

CRod::~CRod()
{
    //dtor
}

void CRod::init()
{
	undeploy();
}

void CRod::deploy()
{
	m_servo.WritePos(m_idL,780,100);
	delay(1000);
	m_servo.WritePos(m_idH,200,100);
}

void CRod::deploy(int angle)
{
	m_servo.WritePos(m_idL,angle,100);
	delay(1000);
	m_servo.WritePos(m_idH,200,100);
}


void CRod::undeploy()
{
	m_servo.WritePos(m_idL,512,100);
	delay(1000);
	m_servo.WritePos(m_idH,512,100);
}