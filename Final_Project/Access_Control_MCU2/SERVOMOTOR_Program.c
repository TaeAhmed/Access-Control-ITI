/*
 * SERVOMOTOR_Program.c
 *
 *  Created on: Aug 21, 2023
 *      Author: Ahmed
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>
#include "DIO_Interface.h"
#include "SERVOMOTOR_Interface.h"

void TIMER1_voidFPWM(void)
{
	/* SELECT FAST PWM */
	CLR_BIT(TCCR1A, WGM10);
	SET_BIT(TCCR1A, WGM11);
	SET_BIT(TCCR1B, WGM12);
	SET_BIT(TCCR1B, WGM13);
#if OCR1CHANNEL == 'A'
	/* CLEAR OC1A */
	CLR_BIT(TCCR1A, COM1A0);
	SET_BIT(TCCR1A, COM1A1);
#elif OCR1CHANNEL == 'B'
	/* CLEAR OC1B */
	CLR_BIT(TCCR1A, COM1B0);
	SET_BIT(TCCR1A, COM1B1);
#endif
	/* ICR1 */
	ICR1 = 19999;

	/* CLK/8 */
	CLR_BIT(TCCR1B, CS10);
	SET_BIT(TCCR1B, CS11);
	CLR_BIT(TCCR1B, CS12);
#if OCR1CHANNEL == 'A'
	DIO_voidSetPinDirection(DIO_PORTD, DIO_PIN5, DIO_OUTPUT);
#elif OCR1CHANNEL == 'B'
	DIO_voidSetPinDirection(DIO_PORTD, DIO_PIN4, DIO_OUTPUT);
#endif
}

void SERVO_voidSetAngle(u8 copy_u8Angle)
{
#if OCR1CHANNEL == 'A'
	OCR1A = ((50* copy_u8Angle)+8991)/9;
#elif OCR1CHANNEL == 'B'
	OCR1B = ((50* copy_u8Angle)+8991)/9;
#endif
}

