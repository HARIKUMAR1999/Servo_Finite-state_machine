#ifndef INC_SERVO_SET_H_
#define INC_SERVO_SET_H_


void servo_set(int b,int d);

typedef struct {
	int servo_number;
	int servo_recipe_reset;
	int servo_pause;
	int servo_special;

}servo_motor;




#endif
