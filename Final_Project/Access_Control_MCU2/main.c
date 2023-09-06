/* MCU2 */
#include <util\delay.h>
#include <string.h>
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "SPI_Interface.h"
#include "DIO_Interface.h"
#include "SERVOMOTOR_Interface.h"

char correctCode[16] = "1234"; // Change this to your desired access code

const int maxAttempts = 3;      // Maximum  attempts
int attempts = 0;               // Counter for attempts

/* PROTOTYPES */
void accessGranted(void);
void accessDenied(void);
void lockDown(void);
/* MAIN */
int main(void){
	unsigned char L_response = 0, L_message = 0;
	char receivedCode[16];
	int codeIndex = 0;

	DIO_voidSetPinDirection(DIO_PORTB,DIO_PIN4,DIO_INPUT);  //SS
	DIO_voidSetPinDirection(DIO_PORTB,DIO_PIN5,DIO_INPUT);  //MOSI
	DIO_voidSetPinDirection(DIO_PORTB,DIO_PIN6,DIO_OUTPUT); //MISO
	DIO_voidSetPinDirection(DIO_PORTB,DIO_PIN7,DIO_INPUT);  //CLK

	SPI_voidInit();
	TIMER1_voidFPWM();

	DIO_voidSetPinDirection(DIO_PORTB,DIO_PIN3,DIO_OUTPUT);//Buzzer Pin
	DIO_voidSetPinDirection(DIO_PORTC,DIO_PIN3,DIO_OUTPUT);//Relay Pin
	DIO_voidSetPinValue(DIO_PORTC,DIO_PIN3,DIO_LOW);//Ensure the relay is  off

	DIO_voidSetPortDirection(DIO_PORTA, 0xff);//debug

	while(1){
		L_response = SPI_u8TransmitRecieve(L_message);
		L_message = 0;

		if(L_response != 0) DIO_voidSetPortValue(DIO_PORTA,L_response);//debug

		if(attempts >= maxAttempts){
			_delay_ms(5000);
			attempts = 0;
			accessDenied();
		}
		if(L_response >= '0' && L_response <= '9'){
			receivedCode[codeIndex] = L_response;
			codeIndex++;
		}
		else if(L_response == 'C'){
			for(codeIndex = 0;codeIndex < 16; codeIndex++) receivedCode[codeIndex] = 0;
			codeIndex = 0;
			accessDenied();
		}
		// Check if the received code matches the correct code
		else if (L_response == '=' && strncmp(receivedCode, correctCode, 16) == 0) {
			// Access granted
			L_message = 2;
			accessGranted();
			attempts = 0;
		}
		else if(L_response == '='){
			for(codeIndex = 0;codeIndex < 16; codeIndex++) receivedCode[codeIndex] = 0;
			codeIndex = 0;

			attempts++;
			if (attempts >= maxAttempts) {
				// Lock  for a defined duration (e.g., 10 minutes)
				L_message = 4;
				lockDown();
			}
			else{
				// Access denied
				L_message = 16 + maxAttempts-attempts;
				accessDenied();

			}
		}
	}
}

void accessGranted(void){
	SERVO_voidSetAngle(90);
	DIO_voidSetPinValue(DIO_PORTC,DIO_PIN3,DIO_HIGH);
	DIO_voidSetPinValue(DIO_PORTB,DIO_PIN3,DIO_LOW);
}

void accessDenied(void){
	SERVO_voidSetAngle(0);
	DIO_voidSetPinValue(DIO_PORTC,DIO_PIN3,DIO_LOW);
	DIO_voidSetPinValue(DIO_PORTB,DIO_PIN3,DIO_LOW);
}

void lockDown(void){
	SERVO_voidSetAngle(0);
	DIO_voidSetPinValue(DIO_PORTC,DIO_PIN3,DIO_LOW);
	DIO_voidSetPinValue(DIO_PORTB,DIO_PIN3,DIO_HIGH);
}
