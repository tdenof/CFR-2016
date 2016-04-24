/*
 * Leg.cpp
 * ArduinoHexapod
 *  Created on: Jun 7, 2011
 *      Author: Danfei Xu
 */
 /** velocity : 0 (no control) from 1 to 0x3ff (1023) (62 RPM)
 position :  from 0 to 0x3ff (0 to 300бу)
 **/
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#define printf(args) (Serial3.write(args))
#else
#include "WProgram.h"
#define printf(args) (Serial3.print(args,BYTE))
#endif
#include "../headers/CDS5500.h"

CDS5500::CDS5500 (){
}


void CDS5500:: WritePos(int ID, int position, int velocity){
	int messageLength = 7;
	byte pos2 =  position/255;
	byte pos =  position%255;

	byte vel2 =  velocity/255;
	byte vel =  velocity%255;

	printf(startByte);              // send some data
	printf(startByte);
	printf(ID);
	printf(messageLength);
	printf(INST_WRITE);
	printf(P_GOAL_POSITION_L);
	printf(pos);
	printf(pos2);
	printf(vel);
	printf(vel2);
	printf((~(ID + (messageLength) + INST_WRITE + P_GOAL_POSITION_L + pos + pos2 + vel + vel2))&0xFF);
}


void CDS5500:: RegWritePos(int ID, int position, int velocity){
	int messageLength = 5;
	byte pos2 =  position/255;
	byte pos =  position%255;

	byte vel2 =  velocity/255;
	byte vel =  velocity%255;

	printf(startByte);              // send some data
	printf(startByte);
	printf(ID);
	printf(messageLength);
	printf(INST_REG_WRITE);
	printf(P_GOAL_POSITION_L);
	printf(pos);
	printf(pos2);
//	printf(vel);
//	printf(vel2);
	printf((~(ID + (messageLength) + INST_WRITE + P_GOAL_POSITION_L + pos + pos2 + vel + vel2))&0xFF);
}

void CDS5500:: RegWriteAction(){
	int messageLength = 2;
	byte ID =  0xFE;

	printf(startByte);              // send some data
	printf(startByte);
	printf(ID);
	printf(messageLength);
	printf(INST_ACTION);
	printf((~(ID + (messageLength) + INST_ACTION))&0xFF);



}

void CDS5500:: SetID(int ID, int newID){
	int messageLength = 4;
	printf(startByte);              // send some data
	printf(startByte);
	printf(ID);
	printf(messageLength);
	printf(INST_WRITE);
	printf(P_ID);
	printf(newID);
	printf((~(ID + (messageLength) + INST_WRITE+ P_ID + newID))&0xFF);
}

void CDS5500:: SetAngleLimit(int ID, int lowerLimit, int upperLimit){
	int messageLength = 8;
	byte lowerLimitB = lowerLimit%255;
	byte lowerLimitS = lowerLimit/255;
	byte upperLimitB = upperLimit%255;
	byte upperLimitS = upperLimit/255;
	printf(startByte);              // send some data
	printf(startByte);
	printf(ID);
	printf(messageLength);
	printf(INST_WRITE);
	printf(0x08);
	printf(upperLimitB);
	printf(0x09);
	printf(upperLimitS);
	printf(0x06);
	printf(lowerLimitB);
	printf(0x07);
	printf(lowerLimitS);
	printf((~(ID + (messageLength) + INST_WRITE+ 0x08 + 0x09 + 0x06 + 0x07 + upperLimitB+ upperLimitS+
					 lowerLimitB + lowerLimitS))&0xFF);
}

//void CDS5500:: SyncWritePos(int[] ID, int[] pos; int[] vel){
//	int messageLength = ()*sizeof(ID);
//}
//
//
//void CDS5500:: SyncWritePos(int[] ID, int pos; int vel){
//
//}
//

void CDS5500:: tempMethod(){

	printf(startByte);              // send some data
	printf(startByte);
	printf(0x01);
	printf(0x05);
	printf(0x03);
	printf(0x08);
	printf(0xFF);
	printf(0x01);
	printf(0xF4);
	printf(0xef);

}

void CDS5500:: Reset(int ID){
	printf(startByte);              // send some data
	printf(startByte);
	printf(ID);
	printf(0x02);
	printf(0x06);
	printf((~(ID + 0x02 +0x06))&0xFF);
}

void CDS5500::SetTempLimit(int ID, int temperature){
	printf(startByte);              // send some data
	printf(startByte);
	printf(ID);
	printf(0x04);
	printf(0x03);
	printf(0x0B);
	printf(temperature);
	printf((~(ID + 0x04 +0x03 + 0x0B + temperature))&0xFF);
}
