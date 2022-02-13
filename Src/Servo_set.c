#include "stm32l476xx.h"
#include "uart.h"
#include "Servo_set.h"
uint8_t buffer[100];
uint16_t	n ;
void servo_set(int Servo1_state ,int Servo2_state){								//processing and setting servos to desired state
	if(Servo1_state!=9){
		if(Servo1_state==0)
		TIM2->CCR1=600;
		else if(Servo1_state==1)
			TIM2->CCR1=900;
		else if(Servo1_state==2)
					TIM2->CCR1=1200;
		else if(Servo1_state==3)
					TIM2->CCR1=1500;
		else if(Servo1_state==4)
					TIM2->CCR1=1800;
		else if(Servo1_state==5)
					TIM2->CCR1=2100;
		n = sprintf((char *)buffer, "\n\r servo 1 =  %d",Servo1_state);
			USART_Write(USART2, buffer, n);

	}
	if(Servo2_state!=9){
		if(Servo2_state==0)
				TIM2->CCR2=600;
				else if(Servo2_state==1)
					TIM2->CCR2=900;
				else if(Servo2_state==2)
							TIM2->CCR2=1200;
				else if(Servo2_state==3)
							TIM2->CCR2=1500;
				else if(Servo2_state==4)
							TIM2->CCR2=1800;
				else if(Servo2_state==5)
							TIM2->CCR2=2100;
		n = sprintf((char *)buffer, "\n\r servo 2 = %d",Servo2_state);
			USART_Write(USART2, buffer, n);
	}
	uint32_t now,past=0,time=0;
	now=TIM3->CNT;
	past=now;
	while(time<=300){
		now=TIM3->CNT;
		time=now-past;

}

}
