#include "../headers/CSwitch.h"
#include "../headers/constantes.h"
#include <Arduino.h>

CSwitch::CSwitch(): m_pinA(PIN_SWA), m_pinB(PIN_SWB), m_green(0), m_purple(0)
{
    //ctor
}

CSwitch::~CSwitch()
{
    //dtor
}

void CSwitch::init()
{
	pinMode(m_pinA,INPUT_PULLUP);
	pinMode(m_pinB,INPUT_PULLUP);
}

int CSwitch::color()
{
	m_green = digitalRead(m_pinA);
	m_purple = digitalRead(m_pinB);
	if(m_green ==0 && m_purple ==0 ) return 0;
	if(m_green ==1 && m_purple ==1 ) return 0;
	if(m_green==1) return 1;
	if(m_purple==1) return -1;
}