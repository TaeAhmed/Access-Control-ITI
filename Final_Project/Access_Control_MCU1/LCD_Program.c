#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <util/delay.h>

#include "DIO_Interface.h"
#include "LCD_Interface.h"



void LCD_voidInit()
{
	/* SET DATA PORT OUTPUT */
	DIO_voidSetPortDirection(LCD_DATA_PORT, 0xff);
	
	/* SET PINS OF CONTROL OUTPUT */
	DIO_voidSetPinDirection(LCD_CONTROL_PORT, RS, DIO_OUTPUT);
	DIO_voidSetPinDirection(LCD_CONTROL_PORT, RW, DIO_OUTPUT);
	DIO_voidSetPinDirection(LCD_CONTROL_PORT, EN, DIO_OUTPUT);
	
	/* WAIT 30ms AFTER VDD RISES TO 4.5V */
	_delay_ms(30);
	
	/* FUNCTION SET */
	LCD_voidSendCommand (LCD_FUNC_SET);
	_delay_ms(1);
	
	/* DISPLAY ON/OFF */
	LCD_voidSendCommand (LCD_ONOF);
	_delay_ms(1);
	
	/* DISPLAY CLEAR */
	LCD_voidSendCommand (LCD_CLEAR);
	_delay_ms(2);

}

void LCD_voidSendCommand(u8 Copy_U8Command)
{
	/* RS = 0 */
	DIO_voidSetPinValue(LCD_CONTROL_PORT, RS, DIO_LOW);
	/* RW = 0 */
	DIO_voidSetPinValue(LCD_CONTROL_PORT, RW, DIO_LOW);
	/* PUT THE COMMAND ON DATA PINS */
	DIO_voidSetPortValue(LCD_DATA_PORT, Copy_U8Command);
	/* E = 1 */
	DIO_voidSetPinValue(LCD_CONTROL_PORT, EN, DIO_HIGH);
	_delay_ms(2);
	/* E = 0 */
	DIO_voidSetPinValue(LCD_CONTROL_PORT, EN, DIO_LOW);
	
}

void LCD_voidSendChar (u8 Copy_U8Data)
{
	/* RS = 1 */
	DIO_voidSetPinValue(LCD_CONTROL_PORT, RS, DIO_HIGH);
    /* RW = 0 */
    DIO_voidSetPinValue(LCD_CONTROL_PORT, RW, DIO_LOW);
    /* PUT THE COMMAND ON DATA PINS */
    DIO_voidSetPortValue(LCD_DATA_PORT, Copy_U8Data);
    /* E = 1 */
    DIO_voidSetPinValue(LCD_CONTROL_PORT, EN, DIO_HIGH);
    _delay_ms(2);
    /* E = 0 */
    DIO_voidSetPinValue(LCD_CONTROL_PORT, EN, DIO_LOW);
}

void LCD_voidSendString (u8 *Copy_U8String)
{
	u8 Local_U8Counter ;
	for (Local_U8Counter = 0 ; Copy_U8String[Local_U8Counter] != '\0' ; Local_U8Counter++)
	{
		LCD_voidSendChar(Copy_U8String[Local_U8Counter]);
	}
		
}
void LCD_voidSetLocation (u8 Copy_U8LineNum , u8 Copy_U8CharNum)
{
	switch (Copy_U8LineNum)
	{
		case LCD_U8_LINE1 : LCD_voidSendCommand(0x80+Copy_U8CharNum); break ;
		
		case LCD_U8_LINE2 : LCD_voidSendCommand(0xc0+Copy_U8CharNum); break ;
	}
}
