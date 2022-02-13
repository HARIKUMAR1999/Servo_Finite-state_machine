#include "stm32l476xx.h"
#include "uart.h"

void timer_Init(void){

	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;					//Enabling the GPIO pin for taking input from the signal genrator

			GPIOA->MODER &= ~3;										//Setting the gpio pin for input
			GPIOA->MODER |= 2 ;
			GPIOA->MODER &= ~(3<<2);										//Setting the gpio pin for input
			GPIOA->MODER |= (2<<2) ;

			GPIOA->AFR[0]|=0x1;										//Setting the alternate function register as well be taking input from the pin for the timer
			GPIOA->AFR[0]|=(0x1<<4);
		RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN;					//Enabling Clock for the timer
		RCC->APB1ENR1 |= RCC_APB1ENR1_TIM3EN;
		TIM2->PSC=15;
		TIM2->EGR |= TIM_EGR_UG;
		TIM3->PSC=15999;
		TIM3->EGR |= TIM_EGR_UG;
		TIM2->ARR=19999;//Turning back on the output enable  for functioning of the timer//Setting the Prescalar value as 15 so that timer will be running on 1 Mhz clock






		TIM2->CCMR1|=0b000<<4;
		TIM2->CCMR1|=(0b000<<12);
		TIM2->CCMR1|=(0b110<<12);
		TIM2->CCMR1|=0b110<<4;

		TIM2->CCER |=1;
		TIM2->CCER |=(0b1<<4);
		TIM2->EGR |= TIM_EGR_UG;


		TIM2->CR1 |= TIM_CR1_CEN;	//Staring the input capture mode for the timer
		TIM3->CR1 |= TIM_CR1_CEN;




}



