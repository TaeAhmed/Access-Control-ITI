/*MCU1*/
#include <util\delay.h>
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_Interface.h"
#include "SPI_Interface.h"
#include "KPD_Interface.h"
#include "LCD_Interface.h"

/* PROTOTYPES */
void showResponse(u8 A_response,u8 A_Tries);
/* MAIN */
int main(void){
	unsigned char L_response = 0, L_message = 0;
	unsigned char Tries = 3;
	unsigned char dirtyScreen = 0;

	  DIO_voidSetPinDirection(DIO_PORTB,DIO_PIN4,DIO_OUTPUT);  //SS
	  DIO_voidSetPinDirection(DIO_PORTB,DIO_PIN5,DIO_OUTPUT); //MOSI
	  DIO_voidSetPinDirection(DIO_PORTB,DIO_PIN6,DIO_INPUT);  //MISO
	  DIO_voidSetPinDirection(DIO_PORTB,DIO_PIN7,DIO_OUTPUT); //CLK

  SPI_voidInit();
  KPD_voidInit();
  LCD_voidInit();

  while(1){
	  L_response = SPI_u8TransmitRecieve(L_message);
	  L_message = 0;

	  char key = KPD_u8GetKeyValue();
	  if (key != KPD_KEY_NOT_PRESSED) {
		  if(L_response == 4) continue;
		  L_message = key;
	      // Display the key on the LCD
		  if(dirtyScreen) {
			  LCD_voidSendCommand(LCD_CLEAR);
			  dirtyScreen = 0;
		  }
	      if(key >= '0' && key <= '9'){
	    	  LCD_voidSendChar(key);
	      }
	      else if(key == 'C'){
	    	  LCD_voidSendCommand(LCD_CLEAR);
	      }
      }
	  if(L_response){
		  // Display response
		  if((L_response & 0xF0) == 0x10) {
			  /*response 0b0000 0000  when bit4 is 1 we are sending tries*/
			  Tries = L_response - 0x10;
			  L_response = 3;
		  }
		  showResponse(L_response,Tries);
		  dirtyScreen = 1;
	  }
  }
  return 0;
}

void showResponse(u8 A_response,u8 A_Tries){
	if(A_response == 2){
  	  LCD_voidSetLocation (LCD_U8_LINE2 , 0);
  	  LCD_voidSendString (" Access Granted");
  	  LCD_voidSetLocation (LCD_U8_LINE1 , 0);
    }
    else if(A_response == 3){
  	  LCD_voidSetLocation (LCD_U8_LINE1 , 0);
  	  LCD_voidSendString ("Incorrect");
  	  LCD_voidSetLocation (LCD_U8_LINE2 , 0);
  	  LCD_voidSendChar(A_Tries+48);
  	  LCD_voidSendString (" Tries left    ");
  	  LCD_voidSetLocation (LCD_U8_LINE1 , 0);
    }
    else if(A_response == 4){
  	  LCD_voidSetLocation (LCD_U8_LINE1 , 0);
  	  LCD_voidSendString ("Incorrect       ");
  	  LCD_voidSetLocation (LCD_U8_LINE2 , 0);
  	  LCD_voidSendString ("    LOCKDOWN    ");
  	  LCD_voidSetLocation (LCD_U8_LINE1 , 0);
    }
}
