#include <stdio.h>	// printf,etc.
#include <errno.h>	// errno
#include <stdlib.h>	//exit
#include <math.h>	// abs
#include <signal.h>	// for Ctrl+C
//#include <unistd.h>	// usleep
#include <time.h>	// nanosleep
#include <wiringPi.h>	// a must

// use wiringPi pinout
#define MOTOR_LEFT 1
#define MOTOR_RIGHT 2
#define MOTOR_UP 3
#define MOTOR_DOWN 4

void runControl(int pin_motor, unsigned int seconds)
{
	digitalWrite(pin_motor, HIGH);
	if ( seconds )
		sleep(seconds);
	digitalWrite(pin_motor, LOW);
}

int main(int argc, const char* argv[])
{
	int result = 0;
	int nextColor;
	
	result = wiringPiSetup();
	if (result < 0)
	{
		printf("wiringPi setup failed, are you root?\n");
		exit(1);
	}
	
	pinMode(MOTOR_LEFT, OUTPUT);
	pinMode(MOTOR_UP, OUTPUT);
	pinMode(MOTOR_DOWN, OUTPUT);
	pinMode(MOTOR_RIGHT, OUTPUT);
	
	
	runControl(MOTOR_UP, 3);	// forward 3 seconds
	sleep(1);
	runControl(MOTOR_DOWN, 1);	// back 1 seconds
	sleep(1);
	runControl(MOTOR_UP, 3);	// forward 3 seconds
	
	printf("End.\n");
	
	return 0;
}
