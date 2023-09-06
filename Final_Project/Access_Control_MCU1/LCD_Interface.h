#ifndef LCD_H
#define LCD_H

/* MACROS For Used Ports & Pins */
#define 	LCD_DATA_PORT 			DIO_PORTC
#define 	LCD_CONTROL_PORT 		DIO_PORTD
#define 	RS 						DIO_PIN5
#define 	RW  					DIO_PIN6
#define 	EN  					DIO_PIN7

/* MACROS For LCD Command */
#define 	LCD_FUNC_SET 			0b00111000
#define 	LCD_ONOF 				0b00001111
#define  	LCD_CLEAR 				0b00000001

/* MACROS For LCD Line */
#define 	LCD_U8_LINE1 			1
#define 	LCD_U8_LINE2 			2



/*Functions*/
void LCD_voidInit ();
void LCD_voidSendCommand(u8 Copy_U8Command);
void LCD_voidSendChar (u8 Copy_U8Data);
void LCD_voidSendString (u8 *Copy_U8String);
void LCD_voidSetLocation (u8 Copy_U8LineNum , u8 Copy_U8CharNum);

#endif