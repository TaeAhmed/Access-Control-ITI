/*
 * SPI_Program.c
 *
 *  Created on: Aug 24, 2023
 *      Author: Ahmed
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <avr/io.h>
#include <avr/delay.h>
#include "SPI_Interface.h"
#include "DIO_Interface.h"

void SPI_voidInit(void)
{
#if   M_MODE == MASTER
	/* MASTER MODE */
	SET_BIT(SPCR, MSTR);

	/* CLK/64 */
	CLR_BIT(SPCR, SPR0);
	SET_BIT(SPCR, SPR1);
	/* DISABLE DOUBLE SPEED */
	CLR_BIT(SPSR, SPI2X);
	/* CPOL & CPHA */
	CLR_BIT(SPCR, CPOL);
	SET_BIT(SPCR, CPHA);
	/* LSB DATA */
	SET_BIT(SPCR, DORD);
	/*set SS to high*/
    DIO_voidSetPinValue(DIO_PORTB,DIO_PIN4,DIO_HIGH);
	/*wait until other peripherals be initialized */
	_delay_ms(300) ;
#elif M_MODE == SLAVE
	/* SLAVE MODE */
	CLR_BIT(SPCR, MSTR);
	/* DISABLE DOUBLE SPEED */
	CLR_BIT(SPSR, SPI2X);
	/* CPOL & CPHA */
	SET_BIT(SPCR, CPOL);
	SET_BIT(SPCR, CPHA);
	/* LSB DATA */
	SET_BIT(SPCR, DORD);
#endif
	/* ENABLE SPI */
	SET_BIT(SPCR, SPE);
}

u8 SPI_u8TransmitRecieve(u8 copy_u8Data)
{
	/*Clear SS to send data to slave*/
	DIO_voidSetPinValue(DIO_PORTB,DIO_PIN4,DIO_LOW);
	SPDR = copy_u8Data;
	while(GET_BIT(SPSR, SPIF) == 0);
	return SPDR;
}

void SPI_voidSendData(u8 copy_u8Data)
{
	/*Clear SS to send data to slave*/
	DIO_voidSetPinValue(DIO_PORTB,DIO_PIN4,DIO_LOW);
	SPDR = copy_u8Data;
}
u8 SPI_u8RecieveData(void)
{
	while(GET_BIT(SPSR, SPIF) == 0);
	return SPDR;
}
