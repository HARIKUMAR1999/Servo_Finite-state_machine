#include "stm32l476xx.h"
#include "uart.h"
#include "Servo_set.h"
#include "main.h"
uint8_t buffer[100];
uint16_t n;
char Servo1_Input, Servo2_input;
int index = 0;

void user_data() {

	if (USART2->ISR & USART_ISR_RXNE) {
		if (index == 0) {
			Servo1_Input = USART2->RDR;
			n = sprintf((char*) buffer, "\n\r%c", Servo1_Input);
			USART_Write(USART2, buffer, n);

		} else if (index == 1) {
			Servo2_input = USART2->RDR;
			n = sprintf((char*) buffer, "%c", Servo2_input);
			USART_Write(USART2, buffer, n);
		}
		index++;

		if (USART2->RDR == 13) {

			index = 0;

			userr(Servo1_Input, Servo2_input);

		}
	}

}

