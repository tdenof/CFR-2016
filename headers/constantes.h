#ifndef CONSTANTES_H
#define CONSTANTES_H

#define WHEEL_DIAMETER 116L
#define BASE_DIAMETER 306L
#define PIN_TIRETTE 22
#define PIN_CAPTEUR A2
#define PIN_SERVO 12
#define SEUIL_IR 150
#define X_INIT 0
#define Y_INIT 0
#define THETA_INIT 90
#define SPEED_INIT 0
#define DIR_INIT 0
#define NBZONEINTERDITE 1

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
#define KP 2
#define KI	0
#define KD	0
#define KR 1
#define KRT 1.2F //polar control
#define SPEEDMAX 100
#define SPEEDMIN 50
#define SPEEDMAXTURN 70
#define SPEEDMINTURN 60

//direction
#define FORWARD 1
#define BACKWARD -1
#define RIGHT 2
#define LEFT -2


#endif // CONSTANTES_H
