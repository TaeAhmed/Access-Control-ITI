/*
 * SERVOMOTOR_Interface.h
 *
 *  Created on: Aug 21, 2023
 *      Author: Ahmed
 */

#ifndef SERVOMOTOR_INTERFACE_H_
#define SERVOMOTOR_INTERFACE_H_

/* CHOOSE 'A' or 'B'*/
#define OCR1CHANNEL 'A'


void TIMER1_voidFPWM(void);

void SERVO_voidSetAngle(u8 copy_u8Angle);


#endif /* SERVOMOTOR_INTERFACE_H_ */
