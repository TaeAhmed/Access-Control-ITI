/*
 * SPI_Interface.h
 *
 *  Created on: Aug 24, 2023
 *      Author: Ahmed
 */

#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_


void SPI_voidInit(void);

u8 SPI_u8TransmitRecieve(u8 copy_u8Data);

void SPI_voidSendData(u8 copy_u8Data);

u8 SPI_u8RecieveData(void);


#define MASTER   1
#define SLAVE    2

/**
 * OPTIONS :
 * 1-MASTER
 * 2-SLAVE  **/

#define M_MODE        MASTER

#endif /* SPI_INTERFACE_H_ */
