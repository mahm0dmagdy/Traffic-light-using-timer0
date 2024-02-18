/*
 * TIMERS_config.h
 *
 * Created: 9/30/2023 11:30:15 AM
 *  Author: mahmo
 */ 


#ifndef TIMERS_CONFIG_H_
#define TIMERS_CONFIG_H_

/*@details Configure Timer Mode --> Options: 1- NORMAL
							    			  2- CTC
								     		  3- PWM
								    		  4- FASTPWM
												   */
#define TIMER_MODE   CTC


/*@details Configure timer PRESCALER --> Options: 1- DIVISION_BY_1
										  2- DIVISION_BY_8
										  3- DIVISION_BY_64
										  4- DIVISION_BY_256 
										  5- DIVISION_BY_1024	   */
#define PRESCALER    DIVISION_BY_64


#endif /* TIMERS_CONFIG_H_ */