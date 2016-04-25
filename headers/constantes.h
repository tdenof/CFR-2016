#ifndef CONSTANTES_H
#define CONSTANTES_H

#define WHEEL_DIAMETER 116L
#define BASE_DIAMETER 340L
#define PIN_TIRETTE 45
#define PIN_CAPTEUR A2
#define PIN_SERVO 12
#define SEUIL_IR 250
#define X_INIT 0
#define Y_INIT 0
#define THETA_INIT 90
#define SPEED_INIT 0
#define DIR_INIT 0
#define NBZONEINTERDITE 1

//Plier
#define ID_PINCED 1
#define ID_PINCEG 3

//Rod
#define ID_RODL 2 //low
#define ID_RODH 4 //high

//moteurs
#define PIN_M1IN1 5		//droite
#define PIN_M1IN2 6
#define PIN_M1PWM 7
#define PIN_M2IN1 8		// gauche
#define PIN_M2IN2 9
#define PIN_M2PWM 10

//encodeurs	gris : VCC - rouge : GND - marron : A - B : violet
// switch A and B connectics for 2nd encoder
#define PIN_A1 18		// droite
#define PIN_B1 19
#define PIN_A2 20		//gauche
#define PIN_B2 21

//Control
#define KP 0.5F
#define KI	0.1F
#define KD	0.1F
#define KPP 1
#define KPI 0
#define KPD 0
#define KPPR 1 //polar control
#define SPEEDMAX 23
#define SPEEDMIN 5
#define SPEEDMAXTURN 25
#define SPEEDMINTURN 5

//direction
#define FORWARD 1
#define BACKWARD -1
#define RIGHT 2
#define LEFT -2


#endif // CONSTANTES_H
