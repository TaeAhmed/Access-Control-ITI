/* LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <util/delay.h>

/* MCAL */
#include "DIO_Interface.h"
/* HAL */
#include "KPD_Interface.h"
u8 KPD_Au8Keys[4][4]  = KPD_KEYS;
u8 KPD_Au8RowsPins[4] = {KPD_R1_PIN, KPD_R2_PIN, KPD_R3_PIN, KPD_R4_PIN};
u8 KPD_Au8ColsPins[4] = {KPD_C1_PIN, KPD_C2_PIN, KPD_C3_PIN, KPD_C4_PIN};

void KPD_voidInit(void)
{
	DIO_voidSetPortDirection(KPD_PORT, 0b00001111);  // ROWS OUT , COLUMNS INPUT
	DIO_voidSetPortValue(KPD_PORT,0xff);
}
u8 KPD_u8GetKeyValue(void)
{
	u8 Local_u8RowsCounter,Local_u8ColsCounter,Local_u8GetPin,Local_u8ReturnedKey;

	/* LOOP FOR ROWS */
	for(Local_u8RowsCounter = 0; Local_u8RowsCounter<=3; Local_u8RowsCounter++)
	{
		/* Activate Row */
		DIO_voidSetPinValue(KPD_PORT, KPD_Au8RowsPins[Local_u8RowsCounter],DIO_LOW);
		/* LOOP FOR COLS */
		for(Local_u8ColsCounter = 0; Local_u8ColsCounter<=3; Local_u8ColsCounter++)
		{
			/* READ CURRENT PIN IN COLUMNS */
			Local_u8GetPin = DIO_u8GetPinValue(KPD_PORT, KPD_Au8ColsPins[Local_u8ColsCounter]);
			if(Local_u8GetPin == DIO_LOW)
			{
				/* Debouncing Problem */
				_delay_ms(20);
				Local_u8GetPin = DIO_u8GetPinValue(KPD_PORT, KPD_Au8ColsPins[Local_u8ColsCounter]);
				while(Local_u8GetPin == DIO_LOW)
				{
					Local_u8GetPin = DIO_u8GetPinValue(KPD_PORT, KPD_Au8ColsPins[Local_u8ColsCounter]);
				}
				return KPD_Au8Keys[Local_u8RowsCounter][Local_u8ColsCounter];
			}
		}
		/* Deactivate Row */
		DIO_voidSetPinValue(KPD_PORT, KPD_Au8RowsPins[Local_u8RowsCounter],DIO_HIGH);

	}
	return KPD_KEY_NOT_PRESSED;
}
