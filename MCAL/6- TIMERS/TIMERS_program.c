/*
 * TIMERS_program.c
 *
 * Created: 9/30/2023 11:29:42 AM
 *  Author: mahmo
 */ 

#include "../../Library/STD_TYPES.h"
#include "../../Library/BIT_MATH.h"
#include "../../Library/defines.h"

#include "TIMERS_config.h"
#include "TIMERS_interface.h"
#include "TIMERS_private.h"
#include "TIMERS_reg.h"
 
static	void (*TIMERS_pvCallBackFuncArr[8])(void) = {NULL}; /*Array of pointers to function*/

void TIMER0_voidInit(void){
	
	/*Waveform generation mode: CTC*/
	CLR_BIT(TCCR0,TCCR0_WGM00);
	SET_BIT(TCCR0,TCCR0_WGM01);
	
//	/*Waveform generation mode: Fast PWM*/
//	SET_BIT(TCCR0,TCCR0_WGM00);
//	SET_BIT(TCCR0,TCCR0_WGM01);
	
	/*Clear the PRESACALER bits*/
	TCCR0 &= PRESCALER_MASK;
	
	/*Select prescaler: division by 64*/
	TCCR0 |= DIVISION_BY_64;
	
//	/*in case of fast PWM - Set on top, clear on compare*/
//	CLR_BIT(TCCR0,TCCR0_COM00);
//	SET_BIT(TCCR0,TCCR0_COM01);
	
	/*Enable PIE of timer0, compare match event*/
	SET_BIT(TIMSK,TIMSK_OCIE0);
}

uint8 TIMERS_u8SetCallBack(TIMERS_Int_Scr_t Copy_TmrIntSource, void(*Copy_pvCallBackFunc) (void)){
	uint8 Local_u8ErrorState = OK;
	 if(Copy_pvCallBackFunc != NULL){
		 TIMERS_pvCallBackFuncArr[Copy_TmrIntSource] = Copy_pvCallBackFunc;
	 }
	 else
	 {
		 Local_u8ErrorState = NULL_PTR_ERR;
	 }
	return Local_u8ErrorState;
}

void TIMER0_voidSetComp(uint8 Copy_u8Val){
	OCR0 = Copy_u8Val;
}

void TIMER1_voidInit(void){
	
	
	
}

void Timer1_voidSetTimerVal(uint16 Copy_u16Val){
	TCNT1 = Copy_u16Val;
}

void TIMER1_voidSetComp(uint16 Copy_u8Val){
	OCR1A = Copy_u8Val;
}


void __vector_10 (void) __attribute__((signal));
void __vector_10 (void) {
	if(TIMERS_pvCallBackFuncArr[TIMER0_COMP] != NULL){
		TIMERS_pvCallBackFuncArr[TIMER0_COMP]();  
	}
}