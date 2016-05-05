#include "../headers/CRod.h"

CRod::CRod(): m_id(ID_ROD)
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
	m_servo.WritePos(m_id,220,100);
}

void CRod::deploy(int angle)
{
	m_servo.WritePos(m_id,angle,100);
}


void CRod::undeploy()
{
	m_servo.WritePos(m_id,800,100);
}