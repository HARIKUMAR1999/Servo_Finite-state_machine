#include "stm32l476xx.h"
#include "clock.h"
#include "timer.h"
#include "Servo_set.h"
#include "Recipe.h"
#include "User.h"
#include <string.h>
#include "MFS.h"

servo_motor motor1;
servo_motor motor2;

char Servo1_Input, Servo2_Input;
uint8_t buffer[100];
uint16_t n;
void userr(char a, char b) {

	//Processing User Input



	Servo1_Input= a;
	Servo2_Input = b;
	if (Servo1_Input == 'p'||Servo1_Input == 'P') {
					motor1.servo_pause = 1;
				} else if (Servo1_Input == 'c'||Servo1_Input == 'C') {
					motor1.servo_pause = 0;
				} else if (Servo1_Input == 'b'||Servo1_Input == 'B') {
					motor1.servo_recipe_reset = 1;
				} else if (Servo1_Input == 'l'||Servo1_Input == 'L') {
					motor1.servo_special = 1;
				} else if (Servo1_Input == 'r'||Servo1_Input == 'R') {
					motor1.servo_special = 2;
				} else if (Servo1_Input == 'n'||Servo1_Input == 'N') {

				}

				if (Servo2_Input == 'p'||Servo2_Input == 'P') {
					motor2.servo_pause = 1;
				} else if (Servo2_Input == 'c'||Servo2_Input == 'C') {
					motor2.servo_pause = 0;
				} else if (Servo2_Input == 'b'||Servo2_Input == 'B') {
					motor2.servo_recipe_reset = 1;
				} else if (Servo2_Input == 'l'||Servo2_Input == 'L') {
					motor2.servo_special = 1;
				} else if (Servo2_Input == 'r'||Servo2_Input == 'R') {
					motor2.servo_special = 2;
				} else if (Servo2_Input == 'n'||Servo2_Input == 'N') {

				}


}

int main(void) {
	clock_init();											//Initializing Clock
	MFS_init();

	USART2_Init(115200);
	timer_Init();
	uint32_t now, past = 0, time;
		motor1.servo_pause = 1;
		motor1.servo_number = 1;
		motor1.servo_special = 0;
		motor1.servo_recipe_reset = 0;
		motor2.servo_pause = 1;
		motor2.servo_number = 2;
		motor2.servo_special = 0;
		motor2.servo_recipe_reset = 0;
		n = sprintf((char *)buffer, "\n\r Welcome to Project 2");
		USART_Write(USART2, buffer, n);





	while (1) {
		now = TIM3->CNT;
		user_data();							//Checking for User Input
		Exec_Recipe(motor1, motor2);			//Executing Recipe on motor 1 and motor 2

		motor1.servo_recipe_reset = 0;
		motor1.servo_special = 0;
		motor2.servo_recipe_reset = 0;
		motor2.servo_special = 0;

		time = now - past;
	    if(time<100)
		while (time <= 100) {					//Checking time lapse of 100 ms
			now=TIM3->CNT;
			time = now - past;

		}
				past = now;


	}
}

