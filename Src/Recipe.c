#include "Servo_set.h"
#include "stm32l476xx.h"
#include "MFS.h"

//Defining custom made opcodes

#define MOV (0x20)
#define LOOP (0x80)
#define WAIT (0x40)
#define END_LOOP (0xA0)
#define RECIPE_END (0)
#define CUSTOM (0xE0)

//defining Recipes

unsigned char recipe1[] = { MOV | 0, MOV | 1,LOOP|3,MOV | 5, MOV | 3,END_LOOP,LOOP|3,MOV | 5, MOV | 3,END_LOOP,WAIT|31,WAIT|31,WAIT|31,MOV | 4,MOV | 5, RECIPE_END };
unsigned char recipe2[] = { MOV | 5, MOV | 4, MOV | 3, MOV | 2, MOV | 1,CUSTOM, MOV | 0, RECIPE_END };

int Recipe_index1 = 0, loopie1 = 0, loop_index1, Recipe_index2 = 0, loopie2 = 0,
		loop_index2,param1=0,param2=0,inst1=0,inst2=0;
int MOV_SERVO1,MOV_SERVO2,WAIT_SERVO1=0,WAIT_SERVO2=0;
int flaggg=0;
void Exec_Recipe(servo_motor motor1,servo_motor motor2) {

	MOV_SERVO1=9;
	MOV_SERVO2=9;
MFS_set_led(3,0);

if (motor1.servo_recipe_reset == 1) {
			Recipe_index1 = 0;

		}
if (motor2.servo_recipe_reset == 1) {
			Recipe_index2 = 0;

		}

	if (motor1.servo_number == 1&&Recipe_index1!=-1) {
		if (((inst1==MOV)&&(param1<0||param1>5))||((inst1==WAIT)&&(param1<0||param1>31))){
			MFS_set_led(3,1);
			MFS_set_led(1,0);
		}


		else if (motor1.servo_pause == 0) {
			MFS_set_led(1,1);

			inst1 = recipe1[Recipe_index1] & 0xE0;
			param1 = recipe1[Recipe_index1]
						& 0x1F;
			if (inst1 == MOV&&param1>=0&&param1<=5) {


				MOV_SERVO1=param1;
				Recipe_index1++;
			} else if (inst1 == LOOP) {
				if(flaggg==1){
					MFS_set_led(4,1);
				}
				else{
				flaggg=1;
				loopie1 = param1 - 1;
				loop_index1 = Recipe_index1;
				Recipe_index1++;
				}

			} else if (inst1 == END_LOOP) {
				flaggg=0;
				if (loopie1 > 0) {
					Recipe_index1 = loop_index1;
					loopie1--;
				}
				Recipe_index1++;

			} else if (inst1 == WAIT) {

				WAIT_SERVO1++;
				if(WAIT_SERVO1==param1/3){
					WAIT_SERVO1=0;
					Recipe_index1++;
				}

			} else if (inst1 == RECIPE_END) {
				MFS_set_led(1,0);
				Recipe_index1 = -1;
			}
			else if(inst1==CUSTOM){
				Recipe_index1=Recipe_index1/2;

			}


		} else if (motor1.servo_pause == 1) {
			MFS_set_led(1,0);
			if (motor1.servo_special == 1&&param1>0&&param1<5) {

				MOV_SERVO1=param1+1;
				param1=param1+1;
			} else if (motor1.servo_special == 2&&param1>0&&param1<5) {

				MOV_SERVO1=param1-1;
				param1=param1-1;
			}
		}

	}
		if (motor2.servo_number == 2&&Recipe_index2!=-1) {


		if (motor2.servo_pause == 0) {
			MFS_set_led(2,1);
			 inst2 = recipe2[Recipe_index2] & 0xE0;
			param2 = recipe2[Recipe_index2]
						& 0x1F;
			if (inst2 == MOV) {

				MOV_SERVO2=param2;
				Recipe_index2++;
			} else if (inst2 == LOOP) {
				loopie2 = param2 - 1;
				loop_index2 = Recipe_index2;
				Recipe_index2++;

			} else if (inst2 == END_LOOP) {
				if (loopie2 > 0) {
					Recipe_index2 = loop_index2;
					loopie2--;
				}
				Recipe_index2++;

			} else if (inst2 == WAIT) {

				WAIT_SERVO2++;
								if(WAIT_SERVO2==param2/3){
									WAIT_SERVO2=0;
									Recipe_index2++;
								}

			} else if (inst2 == RECIPE_END) {
				MFS_set_led(2,0);
				Recipe_index2 = -1;
			}
			else if(inst2==CUSTOM){
				Recipe_index2=Recipe_index2/2;
			}

		} else if (motor2.servo_pause == 1) {
			MFS_set_led(2,0);
			if (motor2.servo_special == 1&&param2>0&&param2<5) {
				MOV_SERVO2=param2+1;
				param2=param2+1;
			} else if (motor2.servo_special == 2&&param2>0&&param2<5) {

				MOV_SERVO2=param2-1;
				param2=param2-1;
			}
		}

	}

		//Running the servos to desired state
	servo_set(MOV_SERVO1,MOV_SERVO2);
}



