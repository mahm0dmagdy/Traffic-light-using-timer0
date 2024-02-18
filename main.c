

#include "Library/BIT_MATH.h"
#include "Library/STD_TYPES.h"
#include "Library/defines.h"

#include "MCAL/1- DIO/DIO_interface.h"
#include "MCAL/2- PORT/PORT_interface.h"
#include "MCAL/6- TIMERS/TIMERS_interface.h"
#include "MCAL/4- GIE/GIE_interface.h"
#include "ECUAL/1- CLCD/CLCD_interface.h"

void TrafficLight(void);
unsigned char Local_SSD[10]= {0b0111111,0b0000110,0b1011011,0b1001111,0b1100110,0b1101101,0b1111101,0b0000111,0b1111111,0b1101111};
uint8 Local_u8Counter=0;

int main(void)
{
	PORT_voidInit();
	CLCD_voidInit();
	TIMER0_voidInit();
	TIMER0_voidSetComp(250);
	TIMERS_u8SetCallBack(TIMER0_COMP,&TrafficLight);
	GIE_voidEnableGlobal();

    while (1) 
    {
	//***************************RED****************************
	CLCD_voidSendCmd(1);
	CLCD_u8Send_String("STOP");
		DIO_u8SetPortValue(DIO_u8PORTC, Local_SSD[0]);
		DIO_u8SetPortValue(DIO_u8PORTD, Local_SSD[0]);
		DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN0,DIO_u8PIN_HIGH);
		while(Local_u8Counter<10)
		{
			DIO_u8SetPortValue(DIO_u8PORTD, Local_SSD[Local_u8Counter]);
		}
		DIO_u8SetPortValue(DIO_u8PORTC, Local_SSD[1]);
		Local_u8Counter=0;
		while(Local_u8Counter<2)
		{
			DIO_u8SetPortValue(DIO_u8PORTD, Local_SSD[Local_u8Counter]);
		}
		//DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN0,DIO_u8PIN_LOW);
		DIO_u8SetPortValue(DIO_u8PORTC, Local_SSD[0]);
		Local_u8Counter=0;
	//*************************END OF RED*************************

	//***************************YELLOW***************************
	CLCD_voidSendCmd(1);
	CLCD_u8Send_String("GET READY");
	DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN3,DIO_u8PIN_HIGH);	
	while(Local_u8Counter <3)
	{
		DIO_u8SetPortValue(DIO_u8PORTD, Local_SSD[Local_u8Counter]);
	}
	DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN3,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN0,DIO_u8PIN_LOW); // TURNOFF RED
	Local_u8Counter=0;
	//************************END OF YELLOW***********************
	
	//***************************GREEN****************************
	CLCD_voidSendCmd(1);
	CLCD_u8Send_String("GO");
		DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN6,DIO_u8PIN_HIGH);
		while(Local_u8Counter<10)
		{
		DIO_u8SetPortValue(DIO_u8PORTD, Local_SSD[Local_u8Counter]);
		}
		Local_u8Counter=0;
		DIO_u8SetPortValue(DIO_u8PORTC, Local_SSD[1]);

		while(Local_u8Counter < 2)
		{
			DIO_u8SetPortValue(DIO_u8PORTD, Local_SSD[Local_u8Counter]);
		}
		Local_u8Counter=0;
		DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN6,DIO_u8PIN_LOW);
		DIO_u8SetPortValue(DIO_u8PORTC,Local_SSD[0]);
	//*********************END OFGREEN************************

	//************************YELLOW**************************
	CLCD_voidSendCmd(1);
	CLCD_u8Send_String("STOP IF SAFE");
		DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN3,DIO_u8PIN_HIGH);	
		while(Local_u8Counter<3)
		{
		DIO_u8SetPortValue(DIO_u8PORTD,Local_SSD[Local_u8Counter]);
		}		
		DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN3,DIO_u8PIN_LOW);
		Local_u8Counter=0;
	//************************END OF YELLOW***********************
    }
}
void TrafficLight(void){
	static uint16 Local_u16CompMatchCounter = 0;
	Local_u16CompMatchCounter++;
	if(Local_u16CompMatchCounter == 1000u){
		Local_u8Counter++;
		Local_u16CompMatchCounter = 0;
	}
}