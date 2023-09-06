#ifndef KPD_INTERFACE_H
#define KPD_INTERFACE_H

/* MACROS OF PORT */
#define       KPD_PORT              DIO_PORTA

/* MACROS FOR ROWS */
#define KPD_R1_PIN                  DIO_PIN0
#define KPD_R2_PIN                  DIO_PIN1
#define KPD_R3_PIN                  DIO_PIN2
#define KPD_R4_PIN                  DIO_PIN3

/* MACROS FOR COLUMNS */
#define KPD_C1_PIN                  DIO_PIN4
#define KPD_C2_PIN                  DIO_PIN5
#define KPD_C3_PIN                  DIO_PIN6
#define KPD_C4_PIN                  DIO_PIN7

/* INDICATION */
#define KPD_KEY_NOT_PRESSED         0xff

/* MACROS OF KPD */

#define KPD_KEYS                       {{'7','8','9','/'},  \
                                        {'4','5','6','*'},  \
										{'1','2','3','-'},  \
										{'C','0','=','+'}}

/* MACROS OF FUNCTION */
void KPD_voidInit(void);
u8   KPD_u8GetKeyValue(void);




#endif
